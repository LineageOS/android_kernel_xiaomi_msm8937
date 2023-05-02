#ifndef _LINUX_ANDROIDBOOT_MODE_H
#define _LINUX_ANDROIDBOOT_MODE_H

enum androidboot_modes {
	ANDROIDBOOT_MODE_NORMAL,
	ANDROIDBOOT_MODE_CHARGER,
	ANDROIDBOOT_MODE_RECOVERY,
};

#if IS_ENABLED(CONFIG_PARSE_ANDROIDBOOT_MODE)
extern enum androidboot_modes androidboot_mode_get(void);
#else
static inline enum androidboot_modes androidboot_mode_get(void)
{
	return ANDROIDBOOT_MODE_NORMAL;
}
#endif

#endif
