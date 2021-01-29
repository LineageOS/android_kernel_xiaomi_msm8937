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

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sysctl.h>

struct xiaomi_dt2w_proc_node {
	char *dir;
	char *file;
};
#define NUM_PATHS 2
struct xiaomi_dt2w_proc_node xiaomi_dt2w_proc_node[NUM_PATHS];

bool xiaomi_dt2w_enable = true;
EXPORT_SYMBOL(xiaomi_dt2w_enable);

static int sysctl_dt2w_min_val = 0;
static int sysctl_dt2w_max_val = 1;
static struct ctl_table_header *dt2w_sysctl_header;

static struct ctl_table dt2w_child_table[] = {
    {
        .procname       = "dt2w",
        .maxlen         = sizeof(int),
        .mode           = 0666,
        .data           = &xiaomi_dt2w_enable,
        .proc_handler   = &proc_dointvec_minmax,
        .extra1         = &sysctl_dt2w_min_val,
        .extra2         = &sysctl_dt2w_max_val,
    },
    {}
};

static struct ctl_table dt2w_parent_table[] = {
    {
        .procname       = "dev",
        .mode           = 0555,
        .child          = dt2w_child_table,
    },
    {}
};

static inline int xiaomi_dt2w_proc_init(char *control_node_path) {

	int ret, i = 0;
	struct proc_dir_entry *proc_directory_tmp = NULL;
	struct proc_dir_entry *proc_symlink_tmp = NULL;

	pr_info("%s: control_node_path parameter is %s", __func__, control_node_path);

	if (true) {
		xiaomi_dt2w_proc_node[0].dir="gesture";
		xiaomi_dt2w_proc_node[0].file="onoff";
		xiaomi_dt2w_proc_node[1].dir="touchpanel";
		xiaomi_dt2w_proc_node[1].file="enable_dt2w";

		pr_info("%s: Starting dynamic symlinking...\n", __func__);

		for(i=0; i<NUM_PATHS; i++) {
			char *proc_path = "/proc/";

			strcat(proc_path, xiaomi_dt2w_proc_node[i].dir);
			strcat(proc_path, "/");
			strcat(proc_path, xiaomi_dt2w_proc_node[i].file);

			if(IS_ERR(filp_open(proc_path, O_RDONLY, 0440))) {
				pr_info("%s: File at path %s doesn't exist, adding...\n", __func__, proc_path);
			} else {
				pr_err("%s: File at path %s already exists, skipping...\n", __func__, proc_path);
				ret = -EEXIST;
				continue;
			}

			pr_info("%s: Creating proc directory %s...\n", __func__, xiaomi_dt2w_proc_node[i].dir);
			proc_directory_tmp = NULL;
			proc_directory_tmp = proc_mkdir(xiaomi_dt2w_proc_node[i].dir, NULL);
			if (proc_directory_tmp == NULL) {
				pr_err("%s: Couldn't create %s dir in procfs\n", __func__, xiaomi_dt2w_proc_node[i].dir);
				continue;
			}

			pr_info("%s: Linking of %s to /proc/%s/%s...\n", __func__, control_node_path, xiaomi_dt2w_proc_node[i].dir, xiaomi_dt2w_proc_node[i].file);
			proc_symlink_tmp = NULL;
			proc_symlink_tmp = proc_symlink(xiaomi_dt2w_proc_node[i].file, proc_directory_tmp, control_node_path);
			if (proc_symlink_tmp == NULL) {
				pr_err("%s: Symlink of %s to /proc/%s/%s failed\n", __func__, control_node_path, xiaomi_dt2w_proc_node[i].dir, xiaomi_dt2w_proc_node[i].file);
				ret = -EPERM;
			} else {
				pr_info("%s: Symlink of %s to /proc/%s/%s done.\n", __func__, control_node_path, xiaomi_dt2w_proc_node[i].dir, xiaomi_dt2w_proc_node[i].file);
			}
		}

		pr_info("%s: Dynamic symlinking done.\n", __func__);
	}

	return ret;
}

int xiaomi_dt2w_probe(void) {

	int ret;

	pr_info("%s: Start registering sysctl dev.dt2w control node...\n", __func__);
	dt2w_sysctl_header = register_sysctl_table(dt2w_parent_table);
	if (!dt2w_sysctl_header) {
		pr_err("%s: Registeration of sysctl dev.dt2w control node failed\n", __func__);
		ret = -EPERM;
	} else {
		pr_info("%s: Registeration of sysctl dev.dt2w control node succeeded, now creating proc symlinks...\n", __func__);
		/* TODO: Dynamicially generate the below path */
		ret = xiaomi_dt2w_proc_init("/proc/sys/dev/dt2w");
	}

	pr_info("%s: Probe done! Initial status = %s\n", __func__, xiaomi_dt2w_enable ? "Enabled" : "Disabled");
	return ret;
}

static int __init xiaomi_dt2w_init(void) {
	return xiaomi_dt2w_probe();
}
module_init(xiaomi_dt2w_init);

MODULE_AUTHOR("Jebaitedneko <jebaitedneko@gmail.com");
MODULE_DESCRIPTION("Xiaomi Shared DT2W Driver");
MODULE_LICENSE("GPL v2");