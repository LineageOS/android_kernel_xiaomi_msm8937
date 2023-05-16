#ifndef _XIAOMI_SDM439_BACKLIGHT_H
#define _XIAOMI_SDM439_BACKLIGHT_H

enum xiaomi_sdm439_backlight_hbm_mode {
	XIAOMI_SDM439_HBM_MODE_UN_SET,
	XIAOMI_SDM439_HBM_MODE_DEFAULT = 1,
	XIAOMI_SDM439_HBM_MODE_LEVEL1,	//CURRENT = XIAOMI_SDM439_HBM_MODE_DEFAULT*112.5%
	XIAOMI_SDM439_HBM_MODE_LEVEL2,	//CURRENT = XIAOMI_SDM439_HBM_MODE_DEFAULT*125%
	XIAOMI_SDM439_HBM_MODE_LEVEL_MAX
};

enum xiaomi_sdm439_backlight_ic_types {
	XIAOMI_SDM439_BACKLIGHT_IC_UNKNOWN,
	XIAOMI_SDM439_BACKLIGHT_IC_LM3697,
	XIAOMI_SDM439_BACKLIGHT_IC_KTD3136,
};

#if IS_ENABLED(CONFIG_MACH_XIAOMI_SDM439)
extern enum xiaomi_sdm439_backlight_ic_types xiaomi_sdm439_backlight_ic_type_get(void);
#else
static inline enum xiaomi_sdm439_backlight_ic_types xiaomi_sdm439_backlight_ic_type_get(void)
{
	return XIAOMI_SDM439_BACKLIGHT_IC_UNKNOWN;
}
#endif

#endif
