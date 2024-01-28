/*
 * LEDs driver for GPIOs
 *
 * Copyright (C) 2007 8D Technologies inc.
 * Raphael Assenat <raph@8d.com>
 * Copyright (C) 2008 Freescale Semiconductor, Inc.
 * Copyright (C) 2018 XiaoMi, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/leds.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/slab.h>

#include <linux/delay.h>
#include <linux/hrtimer.h>
#include <linux/init.h>
#include <linux/pinctrl/consumer.h>
#include <linux/pm_qos.h>
#include <xiaomi-msm8937/mach.h>

#define DUTY_CLCLE 50
#define ADJUST_NUM 15
#define JUSTTIMES 6
#define JUST_DELAY 6

#define HRTIME_JUST_DELAY 9000

#ifndef USE_HRTIMER_SIMULATION
static s64 dealt;
#else
static s64 adjust_dealt;
#endif

static DEFINE_SPINLOCK(infrared_lock);
struct pm_qos_request infrared_qos_req;

struct gpio_ir_tx_packet {
	struct completion done;
	struct hrtimer    timer;
	struct gpio_desc *gpiod_nr;
	bool              high_active;
	u32               pulse;
	u32               space;
	unsigned int     *buffer;
	unsigned int      length;
	unsigned int      next;
	bool              on;
	bool               abort;
};

struct gpio_led_data {
	struct led_classdev cdev;
	struct gpio_desc *gpiod;
	u8 can_sleep;
	u8 blinking;
	gpio_blink_set_t platform_gpio_blink_set;
};

struct mutex ir_lock;

#if defined (WT_USE_FAN54015)
extern int fan54015_getcharge_stat(void);
#endif

static inline struct gpio_led_data *
			cdev_to_gpio_led_data(struct led_classdev *led_cdev)
{
	return container_of(led_cdev, struct gpio_led_data, cdev);
}

static void gpio_led_set(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	struct gpio_led_data *led_dat = cdev_to_gpio_led_data(led_cdev);
	int level;

	pr_debug("infr has been start\n");

	if (value == LED_OFF)
		level = 0;
	else
		level = 1;

	if (led_dat->blinking) {
		led_dat->platform_gpio_blink_set(led_dat->gpiod, level,
						 NULL, NULL);
		led_dat->blinking = 0;
	} else {
		if (led_dat->can_sleep)
			gpiod_set_value_cansleep(led_dat->gpiod, level);
		else
			gpiod_set_value(led_dat->gpiod, level);
	}

	pr_debug("infr has been end\n");
}

static int gpio_led_set_blocking(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	gpio_led_set(led_cdev, value);
	return 0;
}

static int gpio_blink_set(struct led_classdev *led_cdev,
	unsigned long *delay_on, unsigned long *delay_off)
{
	struct gpio_led_data *led_dat = cdev_to_gpio_led_data(led_cdev);

	led_dat->blinking = 1;
	return led_dat->platform_gpio_blink_set(led_dat->gpiod, GPIO_LED_BLINK,
						delay_on, delay_off);
}

static void gpio_ir_tx_set(struct gpio_ir_tx_packet *gpkt, bool on)
{
	if (gpkt->high_active)
		gpiod_set_value(gpkt->gpiod_nr, on);
	else
		gpiod_set_value(gpkt->gpiod_nr, !on);
}

#if defined(USE_HRTIMER_SIMULATION)
static s64 hrtime_adjust(struct gpio_ir_tx_packet *gpkt)
{
	s64 now;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&infrared_lock, flags);

	now = ktime_to_ns(ktime_get());
	for (i = 0; i < ADJUST_NUM; i++) {
		gpio_ir_tx_set(gpkt, false);
	}
	spin_unlock_irqrestore(&infrared_lock, flags);

	return (ktime_to_ns(ktime_get())-now)/ADJUST_NUM;
}

static enum hrtimer_restart gpio_ir_tx_timer(struct hrtimer *timer)
{
	s64 delay_ns = 0, dealt_t = 0;
	ktime_t start = ktime_get();

	struct gpio_ir_tx_packet *gpkt = container_of(timer, struct gpio_ir_tx_packet, timer);
	enum hrtimer_restart restart = HRTIMER_RESTART;

	if (!gpkt->abort && gpkt->next < gpkt->length) {
		if (gpkt->next & 0x01) { /* space */
			gpio_ir_tx_set(gpkt, false);

			delay_ns = gpkt->buffer[gpkt->next++] * NSEC_PER_USEC;
		} else if (!gpkt->pulse || !gpkt->space) {
			gpio_ir_tx_set(gpkt, true);


			delay_ns = gpkt->buffer[gpkt->next++] * NSEC_PER_USEC;
		} else { /* pulse with soft carrier */


#if 1
			unsigned int usecs;

			usecs = gpkt->on ? gpkt->pulse : gpkt->space;
			usecs = min(usecs, gpkt->buffer[gpkt->next]);

			gpio_ir_tx_set(gpkt, gpkt->on);



			delay_ns = usecs * NSEC_PER_USEC;

			gpkt->buffer[gpkt->next] -= usecs;
			gpkt->on = !gpkt->on;

			if (!gpkt->buffer[gpkt->next])
				gpkt->next++;
#endif
		}
	} else {
		restart = HRTIMER_NORESTART;
		gpio_ir_tx_set(gpkt, false);
		complete(&gpkt->done);
	}

	dealt_t = ktime_to_ns(ktime_sub(ktime_get(), start)) + adjust_dealt;

	if (delay_ns >= dealt_t)
		delay_ns -= dealt_t;

	hrtimer_forward_now(&gpkt->timer, ns_to_ktime(delay_ns));

	return restart;
}

static int gpio_ir_tx_transmit_with_timer(struct gpio_ir_tx_packet *gpkt)
{
	int rc = 0, hrtimer = 0, i = 0;

	init_completion(&gpkt->done);

	adjust_dealt = hrtime_adjust(gpkt);
	if (adjust_dealt > HRTIME_JUST_DELAY) {
		for (i = 0; i < JUSTTIMES; i++) {
			adjust_dealt = hrtime_adjust(gpkt);
		}
		pr_err("infrared time_adjust fail!! adjust_dealt=%lld\n", adjust_dealt);
		if (adjust_dealt > HRTIME_JUST_DELAY)
			adjust_dealt = HRTIME_JUST_DELAY;
	}

	hrtimer_init(&gpkt->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL_PINNED);
	gpkt->timer.function = gpio_ir_tx_timer;




	hrtimer = hrtimer_is_hres_active(&gpkt->timer);

	if (!hrtimer) {
		pr_err("unable to use High-Resolution timer\n");
	}

	hrtimer_start(&gpkt->timer, ns_to_ktime(0), HRTIMER_MODE_REL_PINNED);

	rc = wait_for_completion_interruptible(&gpkt->done);
	if (rc != 0) { /* signal exit immediately */
		gpkt->abort = true;
		wait_for_completion(&gpkt->done);
	}

	return gpkt->next ? : -ERESTARTSYS;
}

#else
static s64 time_adjust(struct gpio_ir_tx_packet *gpkt)
{
	s64 now;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&infrared_lock, flags);

	now = ktime_to_us(ktime_get());
	for (i = 0; i < ADJUST_NUM; i++) {
		gpio_ir_tx_set(gpkt, false);
	}
	spin_unlock_irqrestore(&infrared_lock, flags);

	return (ktime_to_us(ktime_get())-now)/ADJUST_NUM;
}

static long pwm_ir_tx_work(void *arg)
{
	struct gpio_ir_tx_packet *gpkt = arg;
	unsigned long flags;

	/* disable irq for acurracy timing */
	spin_lock_irqsave(&infrared_lock, flags);
	for (; gpkt->next < gpkt->length; gpkt->next++) {


		if (gpkt->next & 0x01) { /* space */
				gpio_ir_tx_set(gpkt, false);
				if (gpkt->buffer[gpkt->next] >= dealt)
					udelay(gpkt->buffer[gpkt->next] - dealt);
		} else if (!gpkt->pulse || !gpkt->space) {
				gpio_ir_tx_set(gpkt, true);
				if (gpkt->buffer[gpkt->next] >= dealt)
					udelay(gpkt->buffer[gpkt->next] - dealt);
		} else { /* pulse with soft carrier */
			while (gpkt->buffer[gpkt->next]) {
				unsigned int usecs;
				usecs = gpkt->on ? gpkt->pulse : gpkt->space;
				usecs = min(usecs, gpkt->buffer[gpkt->next]);

				gpio_ir_tx_set(gpkt, gpkt->on);

				if (usecs >= dealt)
					udelay(usecs - dealt);

				gpkt->buffer[gpkt->next] -= usecs;
				gpkt->on = !gpkt->on;
			}
		}
	}

	gpio_ir_tx_set(gpkt, false);

	spin_unlock_irqrestore(&infrared_lock, flags);

	return gpkt->next ? : -ERESTARTSYS;
}

static int gpio_ir_tx_transmit_with_delay(struct gpio_ir_tx_packet *gpkt)
{


	int cpu, rc = -ENODEV;
	int try_again = JUSTTIMES;

	dealt = time_adjust(gpkt);

	while (try_again && (dealt > JUST_DELAY)) {
		try_again--;
		dealt = time_adjust(gpkt);
		pr_debug("jeft time_adjust again!! dealt=%lld\n", dealt);
	}

	if (dealt > JUST_DELAY)
		goto out;





	for_each_online_cpu(cpu)
	{

		if (cpu != 0) {
			rc = work_on_cpu(cpu, pwm_ir_tx_work, gpkt);
			break;
		}
	}

	if (rc == -ENODEV) {
		pr_warn("pwm-ir: can't ron on the auxilliary cpu\n");

	}

	return rc;

out:
	pr_err("jeft cpu too low infrared send fail dealt =%lld\n", dealt);
	return rc;
}
#endif
static ssize_t transmit_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", led_cdev->brightness);
}

static ssize_t transmit_store(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	int *temp_buf = (int *)buf;
	int rc = 0;
	u32 carrier, period;

	struct gpio_ir_tx_packet gpkt = {};
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct gpio_led_data *led_dat =
		container_of(led_cdev, struct gpio_led_data, cdev);


	mutex_lock(&ir_lock);

	carrier = temp_buf[0];
	period = NSEC_PER_MSEC / carrier;

	gpkt.pulse = period * DUTY_CLCLE / 100;
	gpkt.space = period - gpkt.pulse;

	gpkt.gpiod_nr	 = led_dat->gpiod;
	gpkt.high_active = 1/*gdata->tx_high_active*/;
	gpkt.buffer 	 = (unsigned int *)&temp_buf[1];
	gpkt.length 	 = ((int)count/4 - 1);

	pm_qos_update_request(&infrared_qos_req, 1);
#if defined(USE_HRTIMER_SIMULATION)
	rc = gpio_ir_tx_transmit_with_timer(&gpkt);
#else
	if (gpkt.high_active) {
		gpiod_direction_output(gpkt.gpiod_nr, 0);
	}
	rc = gpio_ir_tx_transmit_with_delay(&gpkt);
#endif
	pm_qos_update_request(&infrared_qos_req, PM_QOS_DEFAULT_VALUE);


	mutex_unlock(&ir_lock);

	return rc;
}
static DEVICE_ATTR(transmit, 0664, transmit_show, transmit_store);

static int create_gpio_led(const struct gpio_led *template,
	struct gpio_led_data *led_dat, struct device *parent,
	gpio_blink_set_t blink_set)
{
	int ret, state;
#if defined (WT_USE_FAN54015)
	int chg_status;
#endif

	led_dat->gpiod = template->gpiod;
	if (!led_dat->gpiod) {
		/*
		 * This is the legacy code path for platform code that
		 * still uses GPIO numbers. Ultimately we would like to get
		 * rid of this block completely.
		 */
		unsigned long flags = GPIOF_OUT_INIT_LOW;

		/* skip leds that aren't available */
		if (!gpio_is_valid(template->gpio)) {
			dev_info(parent, "Skipping unavailable LED gpio %d (%s)\n",
					template->gpio, template->name);
			return 0;
		}

		if (template->active_low)
			flags |= GPIOF_ACTIVE_LOW;

		ret = devm_gpio_request_one(parent, template->gpio, flags,
					    template->name);
		if (ret < 0)
			return ret;

		led_dat->gpiod = gpio_to_desc(template->gpio);
		if (!led_dat->gpiod)
			return -EINVAL;
	}

	led_dat->cdev.name = template->name;
	led_dat->cdev.default_trigger = template->default_trigger;
	led_dat->can_sleep = gpiod_cansleep(led_dat->gpiod);
	if (!led_dat->can_sleep)
		led_dat->cdev.brightness_set = gpio_led_set;
	else
		led_dat->cdev.brightness_set_blocking = gpio_led_set_blocking;
	led_dat->blinking = 0;
	if (blink_set) {
		led_dat->platform_gpio_blink_set = blink_set;
		led_dat->cdev.blink_set = gpio_blink_set;
	}
	if (template->default_state == LEDS_GPIO_DEFSTATE_KEEP) {
		state = gpiod_get_value_cansleep(led_dat->gpiod);
		if (state < 0)
			return state;
	} else {
		state = (template->default_state == LEDS_GPIO_DEFSTATE_ON);
	}
	led_dat->cdev.brightness = state ? LED_FULL : LED_OFF;
	if (!template->retain_state_suspended)
		led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;
	if (template->panic_indicator)
		led_dat->cdev.flags |= LED_PANIC_INDICATOR;

#if defined (WT_USE_FAN54015)
	chg_status = fan54015_getcharge_stat();
	if (!strcmp(template->name, "red")) {
		if ((chg_status & 0x1) != 0x1) {
			ret = gpio_direction_output(led_dat->gpio, led_dat->active_low ^ state);
			if (ret < 0)
				return ret;
		}
	}
#else
	ret = gpiod_direction_output(led_dat->gpiod, state);
	if (ret < 0)
		return ret;
#endif

	ret = devm_led_classdev_register(parent, &led_dat->cdev);
	if (ret < 0)
		return ret;

	if (strcmp(led_dat->cdev.name, "infrared") == 0) {
		device_create_file(led_dat->cdev.dev, &dev_attr_transmit);
	}

	return 0;
}

struct gpio_leds_priv {
	int num_leds;
	struct gpio_led_data leds[];
};

static inline int sizeof_gpio_leds_priv(int num_leds)
{
	return sizeof(struct gpio_leds_priv) +
		(sizeof(struct gpio_led_data) * num_leds);
}

static struct gpio_leds_priv *gpio_leds_create(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fwnode_handle *child;
	struct gpio_leds_priv *priv;
	int count, ret;
	count = device_get_child_node_count(dev);
	if (!count)
		return ERR_PTR(-ENODEV);

	priv = devm_kzalloc(dev, sizeof_gpio_leds_priv(count), GFP_KERNEL);
	if (!priv)
		return ERR_PTR(-ENOMEM);

	device_for_each_child_node(dev, child) {
		struct gpio_led_data *led_dat = &priv->leds[priv->num_leds];
		struct gpio_led led = {};
		const char *state = NULL;
		struct device_node *np = to_of_node(child);

		led.gpiod = devm_fwnode_get_gpiod_from_child(dev, NULL, child,
							     GPIOD_ASIS,
							     led.name);
		if (IS_ERR(led.gpiod)) {
			fwnode_handle_put(child);
			return ERR_CAST(led.gpiod);
		}

		ret = fwnode_property_read_string(child, "label", &led.name);
		if (ret && IS_ENABLED(CONFIG_OF) && np)
			led.name = np->name;
		if (!led.name) {
			fwnode_handle_put(child);
			return ERR_PTR(-EINVAL);
		}

		fwnode_property_read_string(child, "linux,default-trigger",
					    &led.default_trigger);

		if (!fwnode_property_read_string(child, "default-state",
						 &state)) {
			if (!strcmp(state, "keep"))
				led.default_state = LEDS_GPIO_DEFSTATE_KEEP;
			else if (!strcmp(state, "on"))
				led.default_state = LEDS_GPIO_DEFSTATE_ON;
			else
				led.default_state = LEDS_GPIO_DEFSTATE_OFF;
		}

		if (fwnode_property_present(child, "retain-state-suspended"))
			led.retain_state_suspended = 1;
		if (fwnode_property_present(child, "panic-indicator"))
			led.panic_indicator = 1;

		ret = create_gpio_led(&led, led_dat, dev, NULL);
		if (ret < 0) {
			fwnode_handle_put(child);
			return ERR_PTR(ret);
		}
		led_dat->cdev.dev->of_node = np;
		priv->num_leds++;
	}
	return priv;
}

static const struct of_device_id of_gpio_leds_match[] = {
	{ .compatible = "gpio-leds-ir-mi8937", },
	{},
};

static int gpio_led_probe(struct platform_device *pdev)
{
	struct gpio_led_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct gpio_leds_priv *priv;
	struct pinctrl *pinctrl;
	int i, ret = 0;

	if (!xiaomi_msm8937_mach_get())
		return -ENODEV;

	pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
	if (IS_ERR(pinctrl))
		dev_warn(&pdev->dev,
			"pins are not configured from the driver\n");

	if (pdata && pdata->num_leds) {
		priv = devm_kzalloc(&pdev->dev,
				sizeof_gpio_leds_priv(pdata->num_leds),
					GFP_KERNEL);
		if (!priv)
			return -ENOMEM;

		priv->num_leds = pdata->num_leds;
		for (i = 0; i < priv->num_leds; i++) {
			ret = create_gpio_led(&pdata->leds[i],
					      &priv->leds[i],
					      &pdev->dev, pdata->gpio_blink_set);
			if (ret < 0)
				return ret;
		}
	} else {
		priv = gpio_leds_create(pdev);
		if (IS_ERR(priv))
			return PTR_ERR(priv);
	}

	platform_set_drvdata(pdev, priv);
	pm_qos_add_request(&infrared_qos_req,
					PM_QOS_CPU_DMA_LATENCY, PM_QOS_DEFAULT_VALUE);
	mutex_init(&ir_lock);

	return 0;
}

static void gpio_led_shutdown(struct platform_device *pdev)
{
	struct gpio_leds_priv *priv = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < priv->num_leds; i++) {
		struct gpio_led_data *led = &priv->leds[i];

		gpio_led_set(&led->cdev, LED_OFF);
	}
}


static struct platform_driver gpio_led_driver = {
	.probe		= gpio_led_probe,
	.shutdown	= gpio_led_shutdown,
	.driver		= {
		.name	= "leds-gpio-ir-mi8937",
		.of_match_table = of_gpio_leds_match,
	},
};

module_platform_driver(gpio_led_driver);

MODULE_AUTHOR("Raphael Assenat <raph@8d.com>, Trent Piepho <tpiepho@freescale.com>");
MODULE_DESCRIPTION("GPIO LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-gpio");
