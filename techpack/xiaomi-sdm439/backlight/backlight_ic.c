#include <linux/err.h>
#include <linux/export.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-sdm439/backlight.h>

#define MDSS_MAX_PANEL_LEN 256
extern char mdss_mdp_panel[MDSS_MAX_PANEL_LEN];
// Example value: 1:dsi:0:qcom,mdss_dsi_ili9881h_hdplus_video_c3i:bklic=01:wpoint=300320:1:none:cfg:single_dsi

static enum xiaomi_sdm439_backlight_ic_types xiaomi_sdm439_backlight_ic_type = XIAOMI_SDM439_BACKLIGHT_IC_UNKNOWN;

enum xiaomi_sdm439_backlight_ic_types xiaomi_sdm439_backlight_ic_type_get(void) {
	return xiaomi_sdm439_backlight_ic_type;
}
EXPORT_SYMBOL(xiaomi_sdm439_backlight_ic_type_get);

static int __init xiaomi_sdm439_backlight_ic_type_init(void) {
	int bkl_id;
	char *bkl_ptr = (char *)strnstr(mdss_mdp_panel, ":bklic=", strlen(mdss_mdp_panel));

	if (IS_ERR_OR_NULL(bkl_ptr)) {
		pr_err("%s: blk_ptr is invalid\n", __func__);
		return -EINVAL;
	}

	bkl_ptr += strlen(":bklic=");
	bkl_id = simple_strtol(bkl_ptr, NULL, 10);

	switch (bkl_id) {
		case 1:
			xiaomi_sdm439_backlight_ic_type = XIAOMI_SDM439_BACKLIGHT_IC_LM3697;
			pr_info("%s: Backlight IC type is LM3697\n", __func__);
			break;
		case 24:
			xiaomi_sdm439_backlight_ic_type = XIAOMI_SDM439_BACKLIGHT_IC_KTD3136;
			pr_info("%s: Backlight IC type is KTD3136\n", __func__);
			break;
		default:
			pr_err("%s: Unknown Backlight IC type %d\n", __func__, bkl_id);
			break;
	}

	return 0;
}
core_initcall(xiaomi_sdm439_backlight_ic_type_init);
