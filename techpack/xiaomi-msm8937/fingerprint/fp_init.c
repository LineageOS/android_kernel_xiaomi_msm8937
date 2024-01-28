#include <linux/export.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-msm8937/mach.h>

#if IS_ENABLED(CONFIG_MACH_XIAOMI_UGG)
enum xiaomi_ugg_fpsensor_variants {
	XIAOMI_UGG_FPSENSOR_UNKNOWN = 0,
	XIAOMI_UGG_FPSENSOR_FPC,
	XIAOMI_UGG_FPSENSOR_GOODIX,
};

static enum xiaomi_ugg_fpsensor_variants xiaomi_ugg_fpsensor_variant = XIAOMI_UGG_FPSENSOR_UNKNOWN;

static int __init xiaomi_ugg_fpsensor_setup(char *str)
{
	if (strcmp(str, "fpc") == 0)
		xiaomi_ugg_fpsensor_variant = XIAOMI_UGG_FPSENSOR_FPC;
	else if (strcmp(str, "gdx") == 0)
		xiaomi_ugg_fpsensor_variant = XIAOMI_UGG_FPSENSOR_GOODIX;

	pr_info("%s: Xiaomi UGG fingerprint sensor variant: %s %d\n", __func__, str, xiaomi_ugg_fpsensor_variant);
	return 1;
}
__setup("androidboot.fpsensor=", xiaomi_ugg_fpsensor_setup);
#endif

#if IS_ENABLED(CONFIG_FINGERPRINT_FPC1020_UGG)
extern int xiaomi_msm8937_fingerprint_fpc_ugg_init(void);
#endif
#if IS_ENABLED(CONFIG_FINGERPRINT_GF3208_UGG)
extern int xiaomi_msm8937_fingerprint_gf3208_ugg_init(void);
#endif
#if IS_ENABLED(CONFIG_FINGERPRINT_FPC1020_SANTONI)
extern int xiaomi_msm8937_fingerprint_fpc_santoni_init(void);
#endif
#if IS_ENABLED(CONFIG_FINGERPRINT_GOODIX_GF3208_SANTONI)
extern int xiaomi_msm8937_fingerprint_goodix_santoni_init(void);
#endif

static int __init xiaomi_msm8937_fingerprint_init(void)
{
	if (!xiaomi_msm8937_mach_get())
		return -ENODEV;

#if IS_ENABLED(CONFIG_MACH_XIAOMI_UGG)
	if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_UGG) {
		switch (xiaomi_ugg_fpsensor_variant) {
			case XIAOMI_UGG_FPSENSOR_FPC:
#if IS_ENABLED(CONFIG_FINGERPRINT_FPC1020_UGG)
				xiaomi_msm8937_fingerprint_fpc_ugg_init();
#endif
				return 0;
			case XIAOMI_UGG_FPSENSOR_GOODIX:
#if IS_ENABLED(CONFIG_FINGERPRINT_GF3208_UGG)
				xiaomi_msm8937_fingerprint_gf3208_ugg_init();
#endif
				return 0;
			default:
#if IS_ENABLED(CONFIG_FINGERPRINT_FPC1020_UGG)
				xiaomi_msm8937_fingerprint_fpc_ugg_init();
#endif
#if IS_ENABLED(CONFIG_FINGERPRINT_GF3208_UGG)
				xiaomi_msm8937_fingerprint_gf3208_ugg_init();
#endif
				return 0;
		}
	}
#endif

#if IS_ENABLED(CONFIG_FINGERPRINT_FPC1020_SANTONI)
	xiaomi_msm8937_fingerprint_fpc_santoni_init();
#endif
#if IS_ENABLED(CONFIG_FINGERPRINT_GOODIX_GF3208_SANTONI)
	xiaomi_msm8937_fingerprint_goodix_santoni_init();
#endif

	return 0;
}
module_init(xiaomi_msm8937_fingerprint_init);
