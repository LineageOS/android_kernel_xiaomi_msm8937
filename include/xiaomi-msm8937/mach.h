#ifndef _XIAOMI_MSM8937_MACH_H
#define _XIAOMI_MSM8937_MACH_H

enum xiaomi_msm8937_mach_family_types {
	XIAOMI_MSM8937_MACH_FAMILY_UNKNOWN = 0,

	XIAOMI_MSM8937_MACH_FAMILY_ULYSSE,
	XIAOMI_MSM8937_MACH_FAMILY_WINGTECH,

	XIAOMI_MSM8937_MACH_FAMILY_MAX,
};

enum xiaomi_msm8937_mach_types {
	XIAOMI_MSM8937_MACH_UNKNOWN = 0,

	XIAOMI_MSM8937_MACH_LAND,
	XIAOMI_MSM8937_MACH_PRADA,
	XIAOMI_MSM8937_MACH_RIVA,
	XIAOMI_MSM8937_MACH_ROLEX,
	XIAOMI_MSM8937_MACH_SANTONI,
	XIAOMI_MSM8937_MACH_TIARE,
	XIAOMI_MSM8937_MACH_UGG,
	XIAOMI_MSM8937_MACH_UGGLITE,

	XIAOMI_MSM8937_MACH_MAX,
};

#if IS_ENABLED(CONFIG_MACH_XIAOMI_MSM8937)
extern int xiaomi_msm8937_mach_get_family(void);
extern int xiaomi_msm8937_mach_get(void);
#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
extern char *xiaomi_msm8937_mach_get_wingtech_board_id(void);
#endif
#else
static inline int xiaomi_msm8937_mach_get_family(void) { return XIAOMI_MSM8937_MACH_FAMILY_UNKNOWN; }
static inline int xiaomi_msm8937_mach_get(void) { return XIAOMI_MSM8937_MACH_UNKNOWN; }
#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
static inline char *xiaomi_msm8937_mach_get_wingtech_board_id(void) { return "Unknown"; }
#endif
#endif

#endif
