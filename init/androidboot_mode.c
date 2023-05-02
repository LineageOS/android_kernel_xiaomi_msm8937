#include <linux/export.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/androidboot_mode.h>

static enum androidboot_modes androidboot_mode = ANDROIDBOOT_MODE_NORMAL;

static int __init androidboot_mode_setup(char *str)
{
	if (!strcmp(str, "recovery"))
		androidboot_mode = ANDROIDBOOT_MODE_RECOVERY;
	else if (!strcmp(str, "charger"))
		androidboot_mode = ANDROIDBOOT_MODE_CHARGER;
	else
		androidboot_mode = ANDROIDBOOT_MODE_NORMAL;

	return 0;
}
__setup("androidboot.mode=", androidboot_mode_setup);

enum androidboot_modes androidboot_mode_get(void)
{
	return androidboot_mode;
}
EXPORT_SYMBOL(androidboot_mode_get);
