#include <xiaomi-msm8937/touchscreen.h>

/*
#include <xiaomi-msm8937/touchscreen.h>

	if (xiaomi_msm8937_touchscreen_is_probed)
		return -ENODEV;

	xiaomi_msm8937_touchscreen_is_probed = true;
*/
bool xiaomi_msm8937_touchscreen_is_probed = false;
EXPORT_SYMBOL(xiaomi_msm8937_touchscreen_is_probed);
