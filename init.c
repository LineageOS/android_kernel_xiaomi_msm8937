#include <linux/module.h>
#include <linux/printk.h>
#if IS_ENABLED(CONFIG_MACH_XIAOMI_MSM8937)
#include <xiaomi-msm8937/mach.h>
#endif

/*
extern bool camera_legacy_enable;

	if (!camera_legacy_enable)
		return -ENODEV;
*/

bool camera_legacy_enable = false;

static int __init camera_legacy_init(void)
{
#if IS_ENABLED(CONFIG_MACH_XIAOMI_MSM8937)
	if (xiaomi_msm8937_mach_get())
		camera_legacy_enable = true;
#endif

#if IS_ENABLED(CONFIG_MSMB_CAMERA_LEGACY_M)
#if IS_ENABLED(CONFIG_MACH_XIAOMI_LAND) || IS_ENABLED(CONFIG_MACH_XIAOMI_PRADA)
	if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_LAND ||
		xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_PRADA)
		camera_legacy_enable = false;
#endif
#endif

	if (camera_legacy_enable)
		pr_info("Enable Legacy Camera Stack.\n");

	return 0;
}

module_init(camera_legacy_init);
