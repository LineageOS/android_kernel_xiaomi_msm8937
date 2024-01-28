#include <linux/device.h>
#include <linux/module.h>
#include <linux/sysctl.h>
#include <xiaomi-sdm439/mach.h>
#include <xiaomi-sdm439/touchscreen.h>

#define ADD_OLD_DT2W_SYSCTL

struct xiaomi_sdm439_touchscreen_operations_t *xiaomi_sdm439_touchscreen_operations;

static int xiaomi_sdm439_touchscreen_enable_dt2w_val = -1;

int xiaomi_sdm439_touchscreen_register_operations(struct xiaomi_sdm439_touchscreen_operations_t *ts_ops)
{
	if (IS_ERR_OR_NULL(ts_ops))
		return -EINVAL;

	xiaomi_sdm439_touchscreen_operations = ts_ops;

	/* Set initial state to false */
	if (!IS_ERR_OR_NULL(xiaomi_sdm439_touchscreen_operations->enable_dt2w))
		xiaomi_sdm439_touchscreen_operations->enable_dt2w(false);

	return 0;
}
EXPORT_SYMBOL(xiaomi_sdm439_touchscreen_register_operations);

bool xiaomi_sdm439_touchscreen_get_dt2w_state(void)
{
	return !!xiaomi_sdm439_touchscreen_enable_dt2w_val;
}
EXPORT_SYMBOL(xiaomi_sdm439_touchscreen_get_dt2w_state);

static int xiaomi_sdm439_touchscreen_toggle_enable_dt2w(struct ctl_table *table,
					int write, void __user *buffer, size_t *lenp, loff_t *ppos)
{
	int *valp = table->data;
	int old_val = *valp;
	int rc;

	if (IS_ERR_OR_NULL(xiaomi_sdm439_touchscreen_operations) ||
		IS_ERR_OR_NULL(xiaomi_sdm439_touchscreen_operations->enable_dt2w))
		return -EFAULT;

	rc = proc_dointvec(table, write, buffer, lenp, ppos);

	if (rc == 0 && write && *valp != old_val) {
		switch (*valp) {
			case 0:
				rc = xiaomi_sdm439_touchscreen_operations->enable_dt2w(false);
				break;
			case 1:
				rc = xiaomi_sdm439_touchscreen_operations->enable_dt2w(true);
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

/* file(s) in /proc/sys/dev/xiaomi_sdm439_touchscreen */
static struct ctl_table xiaomi_sdm439_touchscreen_files[] = {
	{
		.procname	= "enable_dt2w",
		.data		= &xiaomi_sdm439_touchscreen_enable_dt2w_val,
		.maxlen		= sizeof(int),
		.mode		= 0666,
		.proc_handler	= xiaomi_sdm439_touchscreen_toggle_enable_dt2w,
	},
	{ }
};

static struct ctl_table xiaomi_sdm439_touchscreen_dir[] = {
/* dir in /proc/sys/dev */
	{
		.procname	= "xiaomi_sdm439_touchscreen",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= xiaomi_sdm439_touchscreen_files,
	},
/* file(s) in /proc/sys/dev/ */
#ifdef ADD_OLD_DT2W_SYSCTL
	{
		.procname	= "dt2w",
		.data		= &xiaomi_sdm439_touchscreen_enable_dt2w_val,
		.maxlen		= sizeof(int),
		.mode		= 0666,
		.proc_handler	= xiaomi_sdm439_touchscreen_toggle_enable_dt2w,
	},
#endif
	{ }
};

/* /proc/sys/dev itself, in case that is not there yet */
static struct ctl_table xiaomi_sdm439_touchscreen_root_dir[] = {
	{
		.procname	= "dev",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= xiaomi_sdm439_touchscreen_dir,
	},
	{ }
};

static struct ctl_table_header *xiaomi_sdm439_touchscreen_sysctl_header;

static int __init xiaomi_sdm439_touchscreen_sysctl_init(void)
{
	if (!xiaomi_sdm439_mach_get())
		return -ENODEV;

	xiaomi_sdm439_touchscreen_sysctl_header = register_sysctl_table(xiaomi_sdm439_touchscreen_root_dir);
	if (!xiaomi_sdm439_touchscreen_sysctl_header)
		return -ENOMEM;

	return 0;
}
module_init(xiaomi_sdm439_touchscreen_sysctl_init);
