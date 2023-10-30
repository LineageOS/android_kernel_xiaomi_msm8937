#include <linux/device.h>
#include <linux/module.h>
#include <linux/sysctl.h>
#if IS_ENABLED(CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE)
#include <linux/input/doubletap2wake.h>
#endif
#include <xiaomi-msm8937/mach.h>
#include <xiaomi-msm8937/touchscreen.h>

struct xiaomi_msm8937_touchscreen_operations_t *xiaomi_msm8937_touchscreen_operations;

static bool use_software_dt2w = false;
static int xiaomi_msm8937_touchscreen_enable_dt2w_val = -1;
static int xiaomi_msm8937_touchscreen_disable_keys_val = -1;

int xiaomi_msm8937_touchscreen_register_operations(struct xiaomi_msm8937_touchscreen_operations_t *ts_ops)
{
	if (IS_ERR_OR_NULL(ts_ops))
		return -EINVAL;

	if (!dev_get_drvdata(ts_ops->dev))
		return -EINVAL;

	xiaomi_msm8937_touchscreen_operations = ts_ops;

	/* Set initial state to false */
	if (!IS_ERR_OR_NULL(xiaomi_msm8937_touchscreen_operations->enable_dt2w))
		xiaomi_msm8937_touchscreen_operations->enable_dt2w(xiaomi_msm8937_touchscreen_operations->dev, false);
	if (!IS_ERR_OR_NULL(xiaomi_msm8937_touchscreen_operations->disable_keys))
		xiaomi_msm8937_touchscreen_operations->disable_keys(xiaomi_msm8937_touchscreen_operations->dev, false);

	return 0;
}
EXPORT_SYMBOL(xiaomi_msm8937_touchscreen_register_operations);

static int xiaomi_msm8937_touchscreen_toggle_enable_dt2w(struct ctl_table *table,
					int write, void __user *buffer, size_t *lenp, loff_t *ppos)
{
	int *valp = table->data;
	int old_val = *valp;
	int rc;

	if (IS_ERR_OR_NULL(xiaomi_msm8937_touchscreen_operations) ||
		IS_ERR_OR_NULL(xiaomi_msm8937_touchscreen_operations->enable_dt2w))
		return -EFAULT;

	rc = proc_dointvec(table, write, buffer, lenp, ppos);

	if (rc == 0 && write && *valp != old_val) {
		switch (*valp) {
			case 0:
#if IS_ENABLED(CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE)
				if (use_software_dt2w)
					dt2w_switch = 0;
				else
#endif
				rc = xiaomi_msm8937_touchscreen_operations->enable_dt2w(xiaomi_msm8937_touchscreen_operations->dev, false);
				break;
			case 1:
#if IS_ENABLED(CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE)
				if (use_software_dt2w)
					dt2w_switch = 1;
				else
#endif
				rc = xiaomi_msm8937_touchscreen_operations->enable_dt2w(xiaomi_msm8937_touchscreen_operations->dev, true);
				break;
			default:
				rc = -EINVAL;
				break;
		}
	}

	/* Restore the old value in case of error */
	if (rc)
		*valp = old_val;

	return rc;
}

static int xiaomi_msm8937_touchscreen_toggle_disable_keys(struct ctl_table *table,
					int write, void __user *buffer, size_t *lenp, loff_t *ppos)
{
	int *valp = table->data;
	int old_val = *valp;
	int rc;

	if (IS_ERR_OR_NULL(xiaomi_msm8937_touchscreen_operations) ||
		IS_ERR_OR_NULL(xiaomi_msm8937_touchscreen_operations->disable_keys))
		return -EFAULT;

	rc = proc_dointvec(table, write, buffer, lenp, ppos);

	if (rc == 0 && write && *valp != old_val) {
		switch (*valp) {
			case 0:
				rc = xiaomi_msm8937_touchscreen_operations->disable_keys(xiaomi_msm8937_touchscreen_operations->dev, false);
				break;
			case 1:
				rc = xiaomi_msm8937_touchscreen_operations->disable_keys(xiaomi_msm8937_touchscreen_operations->dev, true);
				break;
			default:
				rc = -EINVAL;
				break;
		}
	}

	/* Restore the old value in case of error */
	if (rc)
		*valp = old_val;

	return rc;
}

/* file(s) in /proc/sys/dev/xiaomi_msm8937_touchscreen */
static struct ctl_table xiaomi_msm8937_touchscreen_files[] = {
	{
		.procname	= "enable_dt2w",
		.data		= &xiaomi_msm8937_touchscreen_enable_dt2w_val,
		.maxlen		= sizeof(int),
		.mode		= 0666,
		.proc_handler	= xiaomi_msm8937_touchscreen_toggle_enable_dt2w,
	},
	{
		.procname	= "disable_keys",
		.data		= &xiaomi_msm8937_touchscreen_disable_keys_val,
		.maxlen		= sizeof(int),
		.mode		= 0666,
		.proc_handler	= xiaomi_msm8937_touchscreen_toggle_disable_keys,
	},
	{ }
};

/* dir in /proc/sys/dev */
static struct ctl_table xiaomi_msm8937_touchscreen_dir[] = {
	{
		.procname	= "xiaomi_msm8937_touchscreen",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= xiaomi_msm8937_touchscreen_files,
	},
	{ }
};

/* /proc/sys/dev itself, in case that is not there yet */
static struct ctl_table xiaomi_msm8937_touchscreen_root_dir[] = {
	{
		.procname	= "dev",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= xiaomi_msm8937_touchscreen_dir,
	},
	{ }
};

static struct ctl_table_header *xiaomi_msm8937_touchscreen_sysctl_header;

static int __init xiaomi_msm8937_touchscreen_sysctl_init(void)
{
	if (!xiaomi_msm8937_mach_get())
		return -ENODEV;

#if IS_ENABLED(CONFIG_MACH_XIAOMI_LAND) || IS_ENABLED(CONFIG_MACH_XIAOMI_SANTONI)
	if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_LAND ||
		xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_SANTONI) {
		use_software_dt2w = true;
	}
#endif

	xiaomi_msm8937_touchscreen_sysctl_header = register_sysctl_table(xiaomi_msm8937_touchscreen_root_dir);
	if (!xiaomi_msm8937_touchscreen_sysctl_header)
		return -ENOMEM;

	return 0;
}
module_init(xiaomi_msm8937_touchscreen_sysctl_init);
