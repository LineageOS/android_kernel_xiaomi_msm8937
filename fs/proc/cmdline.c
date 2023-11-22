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

#ifdef CONFIG_PROC_CMDLINE_OVERRIDE_ANDROID_BOOT_DEVICES
#define ANDROID_BOOT_DEVICES_STR_FIND "androidboot.boot_devices=soc/"
#define ANDROID_BOOT_DEVICES_STR_LEN (sizeof(ANDROID_BOOT_DEVICES_STR_FIND) - 1)

#define LK_BOOTDEVICE_VALUE_LEN 13 // 7824900.sdhci
static char saved_lk_bootdevice[LK_BOOTDEVICE_VALUE_LEN + 1];
static int __init lk_bootdevice_setup(char *str) {
	strlcpy(saved_lk_bootdevice, str, sizeof(saved_lk_bootdevice));
	return 1;
}
__setup("androidboot.bootdevice=", lk_bootdevice_setup);
#endif

static char proc_command_line[COMMAND_LINE_SIZE];

static void proc_command_line_init(void) {
	char *offset_addr, *offset_addr2;
	size_t value_len;
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

#ifdef CONFIG_PROC_CMDLINE_OVERRIDE_ANDROID_BOOT_DEVICES
	offset_addr = strstr(proc_command_line, ANDROID_BOOT_DEVICES_STR_FIND);
	if (offset_addr && saved_lk_bootdevice[0]) {
		offset_addr += ANDROID_BOOT_DEVICES_STR_LEN;
		offset_addr2 = strstr(offset_addr, " ");
		if (!offset_addr2)
			offset_addr2 = offset_addr + strlen(offset_addr);
		value_len = offset_addr2 - offset_addr;
		memset(offset_addr, ' ', value_len);
		memcpy(offset_addr, &saved_lk_bootdevice,
			value_len < LK_BOOTDEVICE_VALUE_LEN ? value_len : LK_BOOTDEVICE_VALUE_LEN);
	}
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
