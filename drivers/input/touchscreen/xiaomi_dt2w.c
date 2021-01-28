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
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>

struct node {
	char *path;
};
#define NUM_PATHS 3
struct node node[NUM_PATHS];

bool xiaomi_dt2w_enable = true;
EXPORT_SYMBOL(xiaomi_dt2w_enable);

static inline ssize_t xiaomi_dt2w_onoff_show(struct device *dev, struct device_attribute *attr, char *buf) {
	const char c = xiaomi_dt2w_enable ? '1' : '0';
	return sprintf(buf, "%c\n", c);
}

static inline ssize_t xiaomi_dt2w_onoff_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
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

static inline int xiaomi_dt2w_proc_init(struct kernfs_node *sysfs_node_parent) {

	int len, ret, i, fallback = 0;
	char *buf, *double_tap_sysfs_node;
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
	if (double_tap_sysfs_node) {

		node[0].path="/proc/test/one";
		node[1].path="/proc/test/two";
		node[2].path="/proc/test/three";

		pr_info("%s: Starting dynamic symlinking...\n", __func__);

		for(i=0; i<NUM_PATHS; i++) {

			sprintf(double_tap_sysfs_node, node[i].path);

			if(IS_ERR(filp_open(double_tap_sysfs_node, O_RDONLY, 0440))) {
				pr_info("%s: File at path %s doesn't exist, skipping...\n", __func__, double_tap_sysfs_node);
				fallback++;
				continue;
			}

			pr_info("%s: Linking of %s to /proc/gesture/onoff...\n", __func__, double_tap_sysfs_node);

			proc_symlink_tmp = proc_symlink("onoff", proc_entry_tp, double_tap_sysfs_node);

			if (proc_symlink_tmp == NULL) {
				pr_info("%s: Symlink of %s to /proc/gesture/onoff failed\n", __func__, double_tap_sysfs_node);
				ret = -ENOMEM;
				goto exit;
			} else {
				pr_info("%s: Symlink of %s to /proc/gesture/onoff done.\n", __func__, double_tap_sysfs_node);
			}
		}

		if(fallback >= NUM_PATHS) {

			pr_info("%s: Fallback symlink mode starting...\n", __func__);

			sprintf(double_tap_sysfs_node, "/sys%s/%s", buf, "onoff");

			pr_info("%s: Linking of %s to /proc/gesture/onoff...\n", __func__, double_tap_sysfs_node);

			proc_symlink_tmp = proc_symlink("onoff", proc_entry_tp, double_tap_sysfs_node);

			if (proc_symlink_tmp == NULL) {
				pr_info("%s: Symlink of %s to /proc/gesture/onoff failed\n", __func__, double_tap_sysfs_node);
				ret = -ENOMEM;
				goto exit;
			} else {
				pr_info("%s: Fallback symlink of %s to /proc/gesture/onoff done\n", __func__, double_tap_sysfs_node);
			}
		}

		pr_info("%s: Dynamic symlinking done.\n", __func__);
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
late_initcall(xiaomi_onoff_init);

MODULE_AUTHOR("Jebaitedneko <jebaitedneko@gmail.com");
MODULE_DESCRIPTION("Xiaomi Shared DT2W Driver");
MODULE_LICENSE("GPL v2");
