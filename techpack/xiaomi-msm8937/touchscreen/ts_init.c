#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-msm8937/mach.h>
#include <xiaomi-msm8937/touchscreen.h>

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_ULYSSE)
#define MDSS_MAX_PANEL_LEN 256
extern char mdss_mdp_panel[MDSS_MAX_PANEL_LEN];
#endif

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
	if (!xiaomi_msm8937_mach_get())
		return -ENODEV;

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_ULYSSE)
	if (xiaomi_msm8937_mach_get_family() == XIAOMI_MSM8937_MACH_FAMILY_ULYSSE) {
		pr_info("%s: Mach family is ULYSSE, Initialize touchscreen driver depending on display panel name.\n", __func__);
		if (strstr(mdss_mdp_panel, "mdss_dsi_sc_ili9881c_720p_video")) {
			pr_info("%s: Initialize FocalTech Touchscreen driver, for ili9881c display panel only.\n", __func__);
#if IS_ENABLED(CONFIG_TOUCHSCREEN_FTS_MI8937)
			xiaomi_msm8937_touchscreen_fts_ts_init();
#endif
		}
		pr_info("%s: Initialize Goodix Touchscreen driver, for all display panels.\n", __func__);
#if IS_ENABLED(CONFIG_TOUCHSCREEN_GT9XX_MI8937)
		xiaomi_msm8937_touchscreen_gtp_init();
#endif
		return 0;
	}
#endif

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
