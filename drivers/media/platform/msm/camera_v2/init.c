#include <linux/module.h>
#include <linux/printk.h>
#if IS_ENABLED(CONFIG_MACH_XIAOMI_MSM8937)
#include <xiaomi-msm8937/mach.h>
#endif

/*
extern bool msmb_camera_enable;

	if (!msmb_camera_enable)
		return -ENODEV;
*/

bool msmb_camera_enable = false;

static int __init msmb_camera_init(void)
{
	msmb_camera_enable = true;

#if IS_ENABLED(CONFIG_MSMB_CAMERA_LEGACY)
#if IS_ENABLED(CONFIG_MACH_XIAOMI_MSM8937)
	if (xiaomi_msm8937_mach_get())
		msmb_camera_enable = false;
#endif
#endif

#if IS_ENABLED(CONFIG_MSMB_CAMERA_LEGACY_M)
#if IS_ENABLED(CONFIG_MACH_XIAOMI_LAND) || IS_ENABLED(CONFIG_MACH_XIAOMI_PRADA)
	if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_LAND ||
		xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_PRADA)
		msmb_camera_enable = false;
#endif
#endif

	if (msmb_camera_enable)
		pr_info("Enable MSMB Camera Stack.\n");

	return 0;
}

module_init(msmb_camera_init);
