/*
 * Xiaomi Shared DT2W Driver
 *
 * Copyright (C)  2021 Jebaitedneko <jebaitedneko@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>

bool xiaomi_dt2w_enable = true;
EXPORT_SYMBOL(xiaomi_dt2w_enable);

static ssize_t xiaomi_dt2w_onoff_show(struct device *dev, struct device_attribute *attr, char *buf) {
	const char c = xiaomi_dt2w_enable ? '1' : '0';
	return sprintf(buf, "%c\n", c);
}

static ssize_t xiaomi_dt2w_onoff_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
	int i;
	if (sscanf(buf, "%u", &i) == 1 && i < 2) {
		xiaomi_dt2w_enable = (i == 1);
		return count;
	}
	else {
		pr_info("%s: onoff write error\n", __func__);
		return -EINVAL;
	}
}

static DEVICE_ATTR(onoff, S_IWUSR | S_IRUSR, xiaomi_dt2w_onoff_show, xiaomi_dt2w_onoff_store);

static struct attribute *xiaomi_dt2w_attrs[] = { &dev_attr_onoff.attr, NULL };

static const struct attribute_group xiaomi_dt2w_attr_group = { .attrs = xiaomi_dt2w_attrs, };

static int xiaomi_dt2w_proc_init(struct kernfs_node *sysfs_node_parent) {
	int len, ret = 0;
	char *buf;
	char *double_tap_sysfs_node;
	struct proc_dir_entry *proc_entry_tp = NULL;
	struct proc_dir_entry *proc_symlink_tmp = NULL;

	buf = kzalloc(PATH_MAX, GFP_KERNEL);
	if (buf) {
		len = kernfs_path(sysfs_node_parent, buf, PATH_MAX);
		if (unlikely(len >= PATH_MAX)) {
			pr_info("%s: Buffer too long: %d\n", __func__, len);
			ret = -ERANGE;
			goto exit;
		}
	}

	proc_entry_tp = proc_mkdir("gesture", NULL);
	if (proc_entry_tp == NULL) {
		pr_info("%s: Couldn't create touchpanel dir in procfs\n", __func__);
		ret = -ENOMEM;
		goto exit;
	}

	double_tap_sysfs_node = kzalloc(PATH_MAX, GFP_KERNEL);
	if (double_tap_sysfs_node)
		#if (defined CONFIG_MACH_XIAOMI_LAND) || (defined CONFIG_MACH_XIAOMI_SANTONI)
		sprintf(double_tap_sysfs_node, "/sys/android_touch/doubletap2wake");
		#else
		sprintf(double_tap_sysfs_node, "/sys%s/%s", buf, "onoff");
		#endif
	proc_symlink_tmp = proc_symlink("onoff", proc_entry_tp, double_tap_sysfs_node);
	if (proc_symlink_tmp == NULL) {
		ret = -ENOMEM;
		pr_info("%s: Couldn't create double_tap_enable symlink\n", __func__);
	}

exit:
	kfree(buf);
	kfree(double_tap_sysfs_node);
	return ret;
}

int __maybe_unused dt2w_probe(struct i2c_client *client) {
	int ret;
	ret = sysfs_create_group(&client->dev.kobj, &xiaomi_dt2w_attr_group);
	if (ret) {
		pr_info("%s: Failure %d creating sysfs group\n", __func__, ret);
		sysfs_remove_group(&client->dev.kobj, &xiaomi_dt2w_attr_group);
	}
	xiaomi_dt2w_proc_init(client->dev.kobj.sd);
	return ret;
}
EXPORT_SYMBOL(dt2w_probe);

static int __init xiaomi_onoff_init(void) {
	pr_info("%s: Init done!\n", __func__);
	return 0;
}
module_init(xiaomi_onoff_init);

static void __exit xiaomi_onoff_exit(void) {
	pr_info("%s: Exit done!\n", __func__);
}
module_exit(xiaomi_onoff_exit);

MODULE_AUTHOR("Jebaitedneko <jebaitedneko@gmail.com");
MODULE_DESCRIPTION("Xiaomi Shared DT2W Driverr");
MODULE_LICENSE("GPL v2");
