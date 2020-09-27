/*
 * Gas_Gauge driver for CW2015/2013
 * Copyright (C) 2012, CellWise
 * Copyright (C) 2018 XiaoMi, Inc.
 *
 * Authors: ChenGang <ben.chen@cellwise-semi.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.And this driver depends on
 * I2C and uses IIC bus for communication with the host.
 *
 */
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/workqueue.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define SIZE_BATINFO 64

#define REG_VERSION             	0x0
#define REG_VCELL               	0x2
#define REG_SOC                 	0x4
#define REG_RRT_ALERT           	0x6
#define REG_CONFIG              	0x8
#define REG_MODE                	0xA
#define REG_BATINFO             	0x10

#define MODE_SLEEP_MASK         	(0x3<<6)
#define MODE_SLEEP              	(0x3<<6)
#define MODE_NORMAL             	(0x0<<6)
#define MODE_QUICK_START        	(0x3<<4)
#define MODE_RESTART            	(0xf<<0)

#define CONFIG_UPDATE_FLG       	(0x1<<1)
#define ATHD                    	(0x0<<3)

#define BATTERY_UP_MAX_CHANGE   	420
#define BATTERY_DOWN_CHANGE   	60
#define BATTERY_DOWN_MIN_CHANGE_RUN 	30
#define BATTERY_DOWN_MIN_CHANGE_SLEEP 	1800
#define BATTERY_DOWN_MAX_CHANGE_RUN_AC_ONLINE 	1800

#define USB_CHARGER_MODE        	1
#define AC_CHARGER_MODE         	2
int cw_capacity;

struct cw_battery {
	struct i2c_client *client;
	struct workqueue_struct *battery_workqueue;
	struct delayed_work battery_delay_work;
	struct power_supply *rk_bat;
	struct power_supply	*batt_psy;
	long sleep_time_capacity_change;
	long run_time_capacity_change;
	long sleep_time_charge_start;
	long run_time_charge_start;
	int charger_mode;
	int capacity;
	int voltage;
	int status;
	int time_to_empty;
	int bat_change;
	u8 *cw_bat_config_info;
};

static int cw_read(struct i2c_client *client, u8 reg, u8 buf[])
{
	return i2c_smbus_read_i2c_block_data(client, reg, 1, buf);
}

static int cw_write(struct i2c_client *client, u8 reg, u8 const buf[])
{
	return i2c_smbus_write_i2c_block_data(client, reg, 1, &buf[0]);
}

static int cw_read_word(struct i2c_client *client, u8 reg, u8 buf[])
{
	return i2c_smbus_read_i2c_block_data(client, reg, 2, buf);
}

static int cw_update_config_info(struct cw_battery *cw_bat)
{
	int ret;
	u8 reg_val;
	int i;
	u8 reset_val;

	pr_debug("func: %s-------\n", __func__);

	/* make sure no in sleep mode */
	ret = cw_read(cw_bat->client, REG_MODE, &reg_val);
	if (ret < 0)
		return ret;

	reset_val = reg_val;
	if ((reg_val & MODE_SLEEP_MASK) == MODE_SLEEP) {
		dev_err(&cw_bat->client->dev, "Error, device in sleep mode, cannot update battery info\n");
		return -EPERM;
	}

	/* update new battery info */
	for (i = 0; i < SIZE_BATINFO; i++) {
		pr_debug("cw_bat->cw_bat_config_info[%d] = 0x%x\n", i, \
					cw_bat->cw_bat_config_info[i]);
		ret = cw_write(cw_bat->client, REG_BATINFO + i, &cw_bat->cw_bat_config_info[i]);

		if (ret < 0)
			return ret;
	}

	/* readback & check */
	for (i = 0; i < SIZE_BATINFO; i++) {
		ret = cw_read(cw_bat->client, REG_BATINFO + i, &reg_val);
		if (reg_val != cw_bat->cw_bat_config_info[i])
			return -EPERM;
	}

	/* set cw2015/cw2013 to use new battery info */
	ret = cw_read(cw_bat->client, REG_CONFIG, &reg_val);
	if (ret < 0)
		return ret;

	reg_val |= CONFIG_UPDATE_FLG;   /* set UPDATE_FLAG */
	reg_val &= 0x07;                /* clear ATHD */
	reg_val |= ATHD;                /* set ATHD */
	ret = cw_write(cw_bat->client, REG_CONFIG, &reg_val);
	if (ret < 0)
		return ret;

	/* check 2015/cw2013 for ATHD & update_flag */
	ret = cw_read(cw_bat->client, REG_CONFIG, &reg_val);
	if (ret < 0)
		return ret;

	if (!(reg_val & CONFIG_UPDATE_FLG)) {

		pr_debug("update flag for new battery info have not set..\n");
		reg_val = MODE_SLEEP;
		ret = cw_write(cw_bat->client, REG_MODE, &reg_val);
		pr_debug("report battery capacity error");
		return -EPERM;

	}

	if ((reg_val & 0xf8) != ATHD) {
		pr_debug("the new ATHD have not set..\n");
	}

	/* reset */
	reset_val &= ~(MODE_RESTART);
	reg_val = reset_val | MODE_RESTART;
	ret = cw_write(cw_bat->client, REG_MODE, &reg_val);
	if (ret < 0)
		return ret;

	msleep(10);
	ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
	if (ret < 0)
		return ret;

	return 0;
}

static int cw_check_ic(struct cw_battery *cw_bat)
{
	int ret = 1 ;
	u8 reg_val = 0;

	ret = cw_read(cw_bat->client, REG_MODE/*REG_VERSION*/, &reg_val);

	if (ret < 0) {
		if (ret == -107) {
				return -107;
		} else {
			return ret;
		}
	}
	if ((reg_val == 0xC0) || (reg_val == 0x00)) {
		ret = 0;
	}

	return ret;
}

static int cw_init(struct cw_battery *cw_bat)
{
	int ret;
	int i;
	u8 reg_val = MODE_SLEEP;
	if ((reg_val & MODE_SLEEP_MASK) == MODE_SLEEP) {
		reg_val = MODE_NORMAL;
		ret = cw_write(cw_bat->client, REG_MODE, &reg_val);
		if (ret < 0)
			return ret;
	}

	ret = cw_read(cw_bat->client, REG_CONFIG, &reg_val);
	if (ret < 0)
			return ret;

	if ((reg_val & 0xf8) != ATHD) {
		pr_debug("the new ATHD have not set\n");
		reg_val &= 0x07;    /* clear ATHD */
		reg_val |= ATHD;    /* set ATHD */
		ret = cw_write(cw_bat->client, REG_CONFIG, &reg_val);
		if (ret < 0)
			return ret;
	}

	ret = cw_read(cw_bat->client, REG_CONFIG, &reg_val);
	if (ret < 0)
		return ret;

	if (!(reg_val & CONFIG_UPDATE_FLG)) {
		pr_debug("update flag for new battery info have not set\n");
		ret = cw_update_config_info(cw_bat);
		if (ret < 0)
			return ret;
	} else {
		for (i = 0; i < SIZE_BATINFO; i++) {
			ret = cw_read(cw_bat->client, (REG_BATINFO + i), &reg_val);
			if (ret < 0)
				return ret;

			if (cw_bat->cw_bat_config_info[i] != reg_val)
				break;
		}

		if (i != SIZE_BATINFO) {
			pr_debug("update flag for new battery info have not set\n");
			ret = cw_update_config_info(cw_bat);
			if (ret < 0)
				return ret;
		}
	}

	for (i = 0; i < 30; i++) {
		msleep(100);
		ret = cw_read(cw_bat->client, REG_SOC, &reg_val);
		if (ret < 0)
			return ret;
		else if (reg_val <= 0x64)
			break;

		if (i > 25)
			dev_err(&cw_bat->client->dev, "cw2015/cw2013 input unvalid power error\n");

	}
	if (i >= 30) {
		reg_val = MODE_SLEEP;
		ret = cw_write(cw_bat->client, REG_MODE, &reg_val);
		pr_debug("report battery capacity error");
		return -EPERM;
	}
	return 0;
}

static void cw_update_time_member_charge_start(struct cw_battery *cw_bat)
{
	struct timespec ts;
	int new_run_time;
	int new_sleep_time;

	ktime_get_ts(&ts);
	new_run_time = ts.tv_sec;

	get_monotonic_boottime(&ts);
	new_sleep_time = ts.tv_sec - new_run_time;

	cw_bat->run_time_charge_start = new_run_time;
	cw_bat->sleep_time_charge_start = new_sleep_time;
}

static void cw_update_time_member_capacity_change(struct cw_battery *cw_bat)
{
	struct timespec ts;
	int new_run_time;
	int new_sleep_time;

	ktime_get_ts(&ts);
	new_run_time = ts.tv_sec;

	get_monotonic_boottime(&ts);
	new_sleep_time = ts.tv_sec - new_run_time;

	cw_bat->run_time_capacity_change = new_run_time;
	cw_bat->sleep_time_capacity_change = new_sleep_time;
}

static int cw_get_capacity(struct cw_battery *cw_bat)
{
	u8 reg_val;
	u8 reset_val;
	int ret;
	int cw_capacity;
	int charge_time;
	int allow_change;
	int allow_capacity;
	long new_run_time;
	long new_sleep_time;
	long capacity_or_aconline_time;
	static int if_quickstart;
	static int jump_flag;
	static int reset_loop;
	struct timespec ts;

	ret = cw_read(cw_bat->client, REG_SOC, &reg_val);
	if (ret < 0)
		return ret;
	cw_capacity = reg_val;

	if (cw_capacity < 0 || cw_capacity > 100) {
		dev_err(&cw_bat->client->dev,
			"get cw_capacity error; cw_capacity = %d\n",
			cw_capacity);
		reset_loop++;

		if (reset_loop > 5) {
			reset_val = MODE_SLEEP;
			ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
			if (ret < 0)
				return ret;
			reset_val = MODE_NORMAL;
			msleep(10);
			ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
			if (ret < 0)
				return ret;
			dev_info(&cw_bat->client->dev,
				 "report battery capacity error");
			ret = cw_update_config_info(cw_bat);
			if (ret)
				return ret;
			reset_loop = 0;
		}

		return cw_capacity;
	} else {
		reset_loop = 0;
	}

	ktime_get_ts(&ts);
	new_run_time = ts.tv_sec;

	get_monotonic_boottime(&ts);
	new_sleep_time = ts.tv_sec - new_run_time;

	/* modify battery level swing */
	if ((cw_bat->charger_mode > 0 &&
	     cw_capacity <= (cw_bat->capacity - 1) &&
	     cw_capacity > (cw_bat->capacity - 9)) ||
	    (cw_bat->charger_mode == 0 &&
	     cw_capacity == (cw_bat->capacity + 1))) {
		if (!(cw_capacity == 0 && cw_bat->capacity <= 2))
			cw_capacity = cw_bat->capacity;
	}

	/* avoid no charge full */
	if (cw_bat->charger_mode > 0 &&
	    cw_capacity >= 95 &&
	    cw_capacity <= cw_bat->capacity) {
		capacity_or_aconline_time =
		    (cw_bat->sleep_time_capacity_change >
		     cw_bat->sleep_time_charge_start) ? cw_bat->
		    sleep_time_capacity_change : cw_bat->
		    sleep_time_charge_start;
		capacity_or_aconline_time +=
		    (cw_bat->run_time_capacity_change >
		     cw_bat->run_time_charge_start) ? cw_bat->
		    run_time_capacity_change : cw_bat->run_time_charge_start;
		allow_change =
		    (new_sleep_time + new_run_time -
		     capacity_or_aconline_time) / BATTERY_UP_MAX_CHANGE;
		if (allow_change > 0) {
			allow_capacity = cw_bat->capacity + allow_change;
			cw_capacity =
			    (allow_capacity <= 100) ? allow_capacity : 100;
			jump_flag = 1;
		} else if (cw_capacity <= cw_bat->capacity) {
			cw_capacity = cw_bat->capacity;
		}
	}
	/* avoid battery level jump to CW_BAT */
	else if (cw_bat->charger_mode == 0 &&
		 cw_capacity <= cw_bat->capacity &&
		 cw_capacity >= 90 && jump_flag == 1) {
		capacity_or_aconline_time =
		    (cw_bat->sleep_time_capacity_change >
		     cw_bat->sleep_time_charge_start) ? cw_bat->
		    sleep_time_capacity_change : cw_bat->
		    sleep_time_charge_start;
		capacity_or_aconline_time +=
		    (cw_bat->run_time_capacity_change >
		     cw_bat->run_time_charge_start) ? cw_bat->
		    run_time_capacity_change : cw_bat->run_time_charge_start;
		allow_change =
		    (new_sleep_time + new_run_time -
		     capacity_or_aconline_time) / BATTERY_DOWN_CHANGE;
		if (allow_change > 0) {
			allow_capacity = cw_bat->capacity - allow_change;
			if (cw_capacity >= allow_capacity) {
				jump_flag = 0;
			} else {
				cw_capacity =
				    (allow_capacity <=
				     100) ? allow_capacity : 100;
			}
		} else if (cw_capacity <= cw_bat->capacity) {
			cw_capacity = cw_bat->capacity;
		}
	}

	/* avoid battery level jump to 0% at a moment from more than 2% */
	if (cw_capacity == 0 && cw_bat->capacity > 1) {
		allow_change =
		    ((new_run_time -
		      cw_bat->run_time_capacity_change) /
		     BATTERY_DOWN_MIN_CHANGE_RUN);
		allow_change +=
		    ((new_sleep_time -
		      cw_bat->sleep_time_capacity_change) /
		     BATTERY_DOWN_MIN_CHANGE_SLEEP);

		allow_capacity = cw_bat->capacity - allow_change;
		cw_capacity =
		    (allow_capacity >=
		     cw_capacity) ? allow_capacity : cw_capacity;
		dev_info(&cw_bat->client->dev, "report GGIC POR happened");
		reset_val = MODE_SLEEP;
		ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
		if (ret < 0)
			return ret;
		reset_val = MODE_NORMAL;
		msleep(10);
		ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
		if (ret < 0)
			return ret;
		dev_info(&cw_bat->client->dev, "report battery capacity error");
		ret = cw_update_config_info(cw_bat);
		if (ret)
			return ret;
		dev_info(&cw_bat->client->dev,
			 "report battery capacity jump 0 ");
	}
#if 1
	if (cw_bat->charger_mode > 0 && cw_capacity == 0) {
		charge_time =
		    new_sleep_time + new_run_time -
		    cw_bat->sleep_time_charge_start -
		    cw_bat->run_time_charge_start;
		if (charge_time > BATTERY_DOWN_MAX_CHANGE_RUN_AC_ONLINE &&
		    if_quickstart == 0) {
			reset_val = MODE_SLEEP;
			ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
			if (ret < 0)
				return ret;
			reset_val = MODE_NORMAL;
			msleep(10);
			ret = cw_write(cw_bat->client, REG_MODE, &reset_val);
			if (ret < 0)
				return ret;
			dev_info(&cw_bat->client->dev,
				 "report battery capacity error");
			ret = cw_update_config_info(cw_bat);
			if (ret)
				return ret;
			dev_info(&cw_bat->client->dev,
				 "report battery capacity still 0 if in changing");
			if_quickstart = 1;
		}
	} else if (if_quickstart == 1 && cw_bat->charger_mode == 0) {
		if_quickstart = 0;
	}
#endif
	return cw_capacity;
}

static int cw_get_vol(struct cw_battery *cw_bat)
{
	int ret;
	u8 reg_val[2];
	u16 value16, value16_1, value16_2, value16_3;
	int voltage;

	ret = cw_read_word(cw_bat->client, REG_VCELL, reg_val);
	if (ret < 0)
		return ret;
	value16 = (reg_val[0] * 256) + reg_val[1];

	ret = cw_read_word(cw_bat->client, REG_VCELL, reg_val);
	if (ret < 0)
		return ret;
	value16_1 = (reg_val[0] << 8) + reg_val[1];

	ret = cw_read_word(cw_bat->client, REG_VCELL, reg_val);
	if (ret < 0)
		return ret;
	value16_2 = (reg_val[0] << 8) + reg_val[1];


	if (value16 > value16_1) {
		value16_3 = value16;
		value16 = value16_1;
		value16_1 = value16_3;
	}

	if (value16_1 > value16_2) {
		value16_3 = value16_1;
		value16_1 = value16_2;
		value16_2 = value16_3;
	}

	if (value16 > value16_1) {
		value16_3 = value16;
		value16 = value16_1;
		value16_1 = value16_3;
	}

	voltage = value16_1 * 312 / 1024;
	voltage = voltage * 1000;

	pr_debug("get cw_voltage : cw_voltage = %d\n", voltage);

	return voltage;
}

static int cw_get_time_to_empty(struct cw_battery *cw_bat)
{
	int ret;
	u8 reg_val;
	u16 value16;

	ret = cw_read(cw_bat->client, REG_RRT_ALERT, &reg_val);
	if (ret < 0)
		return ret;

	value16 = reg_val;

	ret = cw_read(cw_bat->client, REG_RRT_ALERT + 1, &reg_val);
	if (ret < 0)
		return ret;

	value16 = ((value16 << 8) + reg_val) & 0x1fff;
	return value16;
}

static void rk_bat_update_capacity(struct cw_battery *cw_bat)
{


	cw_capacity = cw_get_capacity(cw_bat);
	if ((cw_capacity >= 0) && (cw_capacity <= 100) && (cw_bat->capacity != cw_capacity)) {
		cw_bat->capacity = cw_capacity;
		cw_bat->bat_change = 1;
		cw_update_time_member_capacity_change(cw_bat);

		if (cw_bat->capacity == 0)
			pr_debug("report battery capacity 0 and will shutdown if no changing");
	}
}


static void rk_bat_update_vol(struct cw_battery *cw_bat)
{
	int ret;
	ret = cw_get_vol(cw_bat);
	if ((ret >= 0) && (cw_bat->voltage != ret)) {
		cw_bat->voltage = ret;
		cw_bat->bat_change = 1;
	}
}



extern int power_supply_get_battery_charge_state(struct power_supply *psy);
static struct power_supply *charge_psy;
static u8 is_charger_plug;


static void rk_bat_update_status(struct cw_battery *cw_bat)
{
	int status;
	union power_supply_propval ret = {0,};




	if (!charge_psy) {
		charge_psy = power_supply_get_by_name("usb");
	} else{
		is_charger_plug = (u8)power_supply_get_battery_charge_state(charge_psy);
	}

	pr_debug("Chaman for test is_charger_plug %d\n", is_charger_plug);
	if (is_charger_plug == 0)
		cw_bat->charger_mode =  POWER_SUPPLY_TYPE_UNKNOWN;
	else
		cw_bat->charger_mode = USB_CHARGER_MODE;

	if (cw_bat->batt_psy == NULL)
		cw_bat->batt_psy = power_supply_get_by_name("battery");
	if (cw_bat->batt_psy) {
		/* if battery has been registered, use the status property */
		power_supply_get_property(cw_bat->batt_psy,
					POWER_SUPPLY_PROP_STATUS, &ret);
		status = ret.intval;
	} else{
		/* Default to false if the battery power supply is not registered. */
		pr_debug("battery power supply is not registered\n");
		status = POWER_SUPPLY_STATUS_UNKNOWN;
	}

	if (cw_bat->status != status) {
		cw_bat->status = status;
		cw_bat->bat_change = 1;
	}
}

static void rk_bat_update_time_to_empty(struct cw_battery *cw_bat)
{
	int ret;
	ret = cw_get_time_to_empty(cw_bat);
	if ((ret >= 0) && (cw_bat->time_to_empty != ret)) {
		cw_bat->time_to_empty = ret;
		cw_bat->bat_change = 1;
	}

}

static void cw_bat_work(struct work_struct *work)
{
	struct delayed_work *delay_work;
	struct cw_battery *cw_bat;


	delay_work = container_of(work, struct delayed_work, work);
	cw_bat = container_of(delay_work, struct cw_battery, battery_delay_work);

	rk_bat_update_status(cw_bat);
	rk_bat_update_capacity(cw_bat);
	rk_bat_update_vol(cw_bat);
	rk_bat_update_time_to_empty(cw_bat);

	if (cw_bat->bat_change) {
		power_supply_changed(cw_bat->rk_bat);
		cw_bat->bat_change = 0;
	}

	queue_delayed_work(cw_bat->battery_workqueue, &cw_bat->battery_delay_work, msecs_to_jiffies(10000));

	pr_debug("cw_bat->bat_change = %d, cw_bat->time_to_empty = %d, cw_bat->capacity = %d, cw_bat->voltage = %d\n", \
						cw_bat->bat_change, cw_bat->time_to_empty, cw_bat->capacity, cw_bat->voltage);
}

static int rk_battery_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	int ret = 0;
	struct cw_battery *cw_bat;

	cw_bat = power_supply_get_drvdata(psy);
	switch (psp) {
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = cw_bat->capacity;
		break;

	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = cw_bat->voltage <= 0 ? 0 : 1;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = cw_bat->voltage;
		break;

	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		val->intval = cw_bat->time_to_empty;
		break;

	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LIPO;
		break;

	default:
		break;
	}
	return ret;
}

static enum power_supply_property rk_battery_properties[] = {
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
};

static const struct power_supply_desc cw2015_bat_desc = {
	.name		= "rk-bat",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= rk_battery_properties,
	.num_properties	= ARRAY_SIZE(rk_battery_properties),
	.get_property	= rk_battery_get_property,
};

#ifdef CONFIG_PM
static int cw_bat_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct cw_battery *cw_bat = i2c_get_clientdata(client);
	pr_debug("%s\n", __func__);
	cancel_delayed_work(&cw_bat->battery_delay_work);

		pr_debug("cw_bat->capacity:%d\n", cw_bat->capacity);
	return 0;
}

static int cw_bat_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct cw_battery *cw_bat = i2c_get_clientdata(client);
	pr_debug("%s\n", __func__);
	queue_delayed_work(cw_bat->battery_workqueue, &cw_bat->battery_delay_work, msecs_to_jiffies(1));
		pr_debug("cw_bat->capacity:%d\n", cw_bat->capacity);
		return 0;
}

static const struct dev_pm_ops cw_bat_pm_ops = {
		.suspend = cw_bat_suspend,
		.resume = cw_bat_resume,

};
#endif

extern int battery_type_id ;
static int cw_bat_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct cw_battery *cw_bat;
	struct power_supply_config psy_cfg = {0};
	int ret;
	int loop = 0;

static u8 config_info[SIZE_BATINFO] = {
	0x18, 0x03, 0x6A, 0x6B, 0x6D, 0x6A, 0x68, 0x65, 0x60, 0x63,
    0x60, 0x54, 0x5D, 0x59, 0x48, 0x40, 0x38, 0x31, 0x27, 0x24, 
	0x28, 0x31, 0x43, 0x4D, 0x28, 0x49, 0x0B, 0x85, 0x1C, 0x37,
	0x57, 0x6E, 0x79, 0x7A, 0x7A, 0x7A, 0x3D, 0x1A, 0x62, 0x3F,
	0x0A, 0x44, 0x34, 0x55, 0x82, 0x97, 0x9B, 0x13, 0x41, 0x81,
	0x94, 0xC2, 0x74, 0x9C, 0xBC, 0xCB, 0x2F, 0x7D, 0x72, 0xA5,
	0xB5, 0xC1, 0x95, 0x61
};
static u8 config_info_xinwangda[SIZE_BATINFO] = {
	0x18, 0x03, 0x6A, 0x6B, 0x6D, 0x6A, 0x68, 0x65, 0x60, 0x63,
    0x60, 0x54, 0x5D, 0x59, 0x48, 0x40, 0x38, 0x31, 0x27, 0x24, 
	0x28, 0x31, 0x43, 0x4D, 0x28, 0x49, 0x0B, 0x85, 0x1C, 0x37,
	0x57, 0x6E, 0x79, 0x7A, 0x7A, 0x7A, 0x3D, 0x1A, 0x62, 0x3F,
	0x0A, 0x44, 0x34, 0x55, 0x82, 0x97, 0x9B, 0x13, 0x41, 0x81,
	0x94, 0xC2, 0x74, 0x9C, 0xBC, 0xCB, 0x2F, 0x7D, 0x72, 0xA5,
	0xB5, 0xC1, 0x95, 0x61
};
static u8 config_info_feimaotui[SIZE_BATINFO] = {
	0x18, 0x07, 0x6D, 0x6C, 0x6B, 0x6A, 0x65, 0x65, 0x56, 0x78,
	0x63, 0x49, 0x67, 0x56, 0x47, 0x3E, 0x38, 0x2D, 0x2B, 0x24,
	0x2B, 0x31, 0x44, 0x4E, 0x17, 0x63, 0x0B, 0x85, 0x0D, 0x1A,
	0x52, 0x5D, 0x78, 0x74, 0x74, 0x78, 0x3E, 0x1B, 0x5E, 0x22,
	0x1C, 0x3F, 0x29, 0x53, 0x81, 0x97, 0x98, 0x23, 0x75, 0x7A,
	0x95, 0xC2, 0x7B, 0x99, 0xBA, 0xCB, 0x2F, 0x7D, 0x72, 0xA5,
 	0xB5, 0xC1, 0x58, 0x91
};

	pr_debug("\ncw2015/cw2013 driver v1.2 probe start, battery_type_id is %d\n", battery_type_id);

	cw_bat = kzalloc(sizeof(struct cw_battery), GFP_KERNEL);
	if (!cw_bat) {
		dev_err(&cw_bat->client->dev, "fail to allocate memory\n");
		return -ENOMEM;
	}

	if (battery_type_id == 1) {
		cw_bat->cw_bat_config_info  = config_info_feimaotui;
	} else if (battery_type_id == 2) {
		cw_bat->cw_bat_config_info  = config_info_xinwangda;
	} else {
		cw_bat->cw_bat_config_info  = config_info;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C not supported\n");
		return -ENODEV;
	}

	cw_bat->client = client;
	i2c_set_clientdata(client, cw_bat);
	ret = cw_check_ic(cw_bat);

	while ((loop++ < 5) && (ret != 0)) {
		pr_debug(" check ret is %d, loop is %d \n" , ret, loop);
		ret = cw_check_ic(cw_bat);
	}

	if (ret != 0) {
		pr_debug(" wc_check_ic fail ,return  ENODEV \n");
		return -ENODEV;
	}

	ret = cw_init(cw_bat);
	while ((loop++ < 2000) && (ret != 0)) {
		ret = cw_init(cw_bat);
	}

	if (ret) {
			return ret;
	}

	cw_bat->charger_mode = 0;
	cw_bat->capacity = 0;
	cw_bat->voltage = 0;
	cw_bat->status = 0;
	cw_bat->time_to_empty = 0;
	cw_bat->bat_change = 0;

	psy_cfg.drv_data = cw_bat;
	cw_bat->rk_bat = devm_power_supply_register(&client->dev,
				&cw2015_bat_desc, &psy_cfg);
	if (IS_ERR(cw_bat->rk_bat)) {
		dev_err(&cw_bat->client->dev,
			"power supply register rk_bat error\n");
		return -1;
	}

	cw_update_time_member_capacity_change(cw_bat);
	cw_update_time_member_charge_start(cw_bat);

	cw_bat->battery_workqueue = create_singlethread_workqueue("rk_battery");
	INIT_DELAYED_WORK(&cw_bat->battery_delay_work, cw_bat_work);

	queue_delayed_work(cw_bat->battery_workqueue, &cw_bat->battery_delay_work, msecs_to_jiffies(10));

	pr_debug("\ncw2015/cw2013 driver v1.2 probe sucess\n");
	return 0;
}

static int cw_bat_remove(struct i2c_client *client)
{
	struct cw_battery *cw_bat = i2c_get_clientdata(client);
	pr_debug("%s\n", __func__);
	cancel_delayed_work(&cw_bat->battery_delay_work);
	return 0;
}

static const struct i2c_device_id cw_id[] = {
	{ "cw201x", 0 },
};
MODULE_DEVICE_TABLE(i2c, cw_id);

static struct of_device_id cw2015_match_table[] = {
	{ .compatible = "cellwise,cw2015", },
	{ },
};
static struct i2c_driver cw_bat_driver = {
			.driver         = {
			.name   = "cw201x",

#ifdef CONFIG_PM
			.pm = &cw_bat_pm_ops,
#endif
			.of_match_table = cw2015_match_table,
	},
		.probe          = cw_bat_probe,
		.remove         = cw_bat_remove,
		.id_table   = cw_id,
};

static int __init cw_bat_init(void)
{
	return i2c_add_driver(&cw_bat_driver);
}

static void __exit cw_bat_exit(void)
{
	i2c_del_driver(&cw_bat_driver);
}

late_initcall(cw_bat_init);
module_exit(cw_bat_exit);

MODULE_AUTHOR("ben<ben.chen@cellwise-semi.com>");
MODULE_DESCRIPTION("cw2015/cw2013 battery driver");
MODULE_LICENSE("GPL");
