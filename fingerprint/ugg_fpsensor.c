#include <linux/export.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-msm8937/ugg_fpsensor.h>

enum xiaomi_ugg_fpsensor_variants xiaomi_ugg_fpsensor_variant = XIAOMI_UGG_FPSENSOR_UNKNOWN;
EXPORT_SYMBOL(xiaomi_ugg_fpsensor_variant);

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
