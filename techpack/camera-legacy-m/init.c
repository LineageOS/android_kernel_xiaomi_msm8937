#include <linux/module.h>
#include <linux/printk.h>
#if IS_ENABLED(CONFIG_MACH_XIAOMI_MSM8937)
#include <xiaomi-msm8937/mach.h>
#endif

/*
extern bool camera_legacy_m_enable;

	if (!camera_legacy_m_enable)
		return -ENODEV;
*/

bool camera_legacy_m_enable = false;

static int __init camera_legacy_m_init(void)
{
#if IS_ENABLED(CONFIG_MACH_XIAOMI_LAND) || IS_ENABLED(CONFIG_MACH_XIAOMI_PRADA)
	if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_LAND ||
		xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_PRADA)
		camera_legacy_m_enable = true;
#endif

	if (camera_legacy_m_enable)
		pr_info("Enable Legacy (Marshmallow) Camera Stack.\n");

	return 0;
}

module_init(camera_legacy_m_init);
