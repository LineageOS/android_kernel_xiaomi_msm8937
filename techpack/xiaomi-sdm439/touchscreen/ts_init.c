#if IS_ENABLED(CONFIG_PARSE_ANDROIDBOOT_MODE)
#include <linux/androidboot_mode.h>
#endif
#include <linux/export.h>
#include <linux/module.h>
#include <linux/types.h>
#include <xiaomi-sdm439/touchscreen.h>

/*
#include <xiaomi-sdm439/touchscreen.h>

	if (xiaomi_sdm439_touchscreen_type != XIAOMI_SDM439_TOUCHSCREEN_UNKNOWN)
		return -ENODEV;

	xiaomi_sdm439_touchscreen_type = XIAOMI_SDM439_TOUCHSCREEN_;
*/
enum xiaomi_sdm439_touchscreen_types xiaomi_sdm439_touchscreen_type = XIAOMI_SDM439_TOUCHSCREEN_UNKNOWN;
EXPORT_SYMBOL(xiaomi_sdm439_touchscreen_type);

static int __init xiaomi_sdm439_touchscreen_init(void)
{
	xiaomi_sdm439_touchscreen_type = XIAOMI_SDM439_TOUCHSCREEN_UNKNOWN;

#if IS_ENABLED(CONFIG_PARSE_ANDROIDBOOT_MODE)
	if (androidboot_mode_get() == ANDROIDBOOT_MODE_CHARGER)
		xiaomi_sdm439_touchscreen_type = XIAOMI_SDM439_TOUCHSCREEN_DISABLE;
#endif

	return 0;
}
module_init(xiaomi_sdm439_touchscreen_init);
