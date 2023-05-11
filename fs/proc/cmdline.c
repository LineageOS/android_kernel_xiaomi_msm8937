// SPDX-License-Identifier: GPL-2.0
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/setup.h>
#ifdef CONFIG_PROC_CMDLINE_APPEND_ANDROID_FSTAB_SUFFIX
#include <linux/of.h>
#endif

#ifdef CONFIG_INITRAMFS_IGNORE_SKIP_FLAG
#define INITRAMFS_STR_FIND "skip_initramf"
#define INITRAMFS_STR_REPLACE "want_initramf"
#define INITRAMFS_STR_LEN (sizeof(INITRAMFS_STR_FIND) - 1)
#endif

static char proc_command_line[COMMAND_LINE_SIZE];

static void proc_command_line_init(void) {
	char *offset_addr;
#ifdef CONFIG_PROC_CMDLINE_APPEND_ANDROID_FSTAB_SUFFIX
	const char *android_fstab_suffix;
#endif

	strcpy(proc_command_line, saved_command_line);

#ifdef CONFIG_INITRAMFS_IGNORE_SKIP_FLAG
	offset_addr = strstr(proc_command_line, INITRAMFS_STR_FIND);
	if (offset_addr)
		memcpy(offset_addr, INITRAMFS_STR_REPLACE, INITRAMFS_STR_LEN);
#endif

#ifdef CONFIG_PROC_CMDLINE_APPEND_ANDROID_FSTAB_SUFFIX
	if (of_property_read_string(of_find_node_by_path("/"), "android,fstab_suffix", &android_fstab_suffix) == 0)
		snprintf(proc_command_line, COMMAND_LINE_SIZE, "%s androidboot.fstab_suffix=%s", proc_command_line, android_fstab_suffix);
#endif
}

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_puts(m, proc_command_line);
	seq_putc(m, '\n');
	return 0;
}

static int __init proc_cmdline_init(void)
{
	proc_command_line_init();

	proc_create_single("cmdline", 0, NULL, cmdline_proc_show);
	return 0;
}
fs_initcall(proc_cmdline_init);
