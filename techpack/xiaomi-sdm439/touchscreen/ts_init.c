#include <linux/export.h>
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
