#include <linux/module.h>
#include <xiaomi-msm8937/touchscreen.h>

/*
#include <xiaomi-msm8937/touchscreen.h>

	if (xiaomi_msm8937_touchscreen_is_probed)
		return -ENODEV;

	xiaomi_msm8937_touchscreen_is_probed = true;
*/
bool xiaomi_msm8937_touchscreen_is_probed = false;
EXPORT_SYMBOL(xiaomi_msm8937_touchscreen_is_probed);

#if IS_ENABLED(CONFIG_TOUCHSCREEN_ATMEL308U_MI8937)
extern int xiaomi_msm8937_touchscreen_mxt_init(void);
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_FTS_MI8937)
extern int xiaomi_msm8937_touchscreen_fts_ts_init(void);
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_GT9XX_MI8937)
extern int xiaomi_msm8937_touchscreen_gtp_init(void);
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_IST30XX_MI8937)
extern int xiaomi_msm8937_touchscreen_ist30xx_init(void);
#endif

static int __init xiaomi_msm8937_touchscreen_init(void)
{
#if IS_ENABLED(CONFIG_TOUCHSCREEN_ATMEL308U_MI8937)
	xiaomi_msm8937_touchscreen_mxt_init();
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_FTS_MI8937)
	xiaomi_msm8937_touchscreen_fts_ts_init();
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_GT9XX_MI8937)
	xiaomi_msm8937_touchscreen_gtp_init();
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_IST30XX_MI8937)
	xiaomi_msm8937_touchscreen_ist30xx_init();
#endif

	return 0;
}
module_init(xiaomi_msm8937_touchscreen_init);
