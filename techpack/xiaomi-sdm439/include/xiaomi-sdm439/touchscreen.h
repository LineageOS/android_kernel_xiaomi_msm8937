#ifndef _XIAOMI_SDM439_TOUCHSCREEN_H
#define _XIAOMI_SDM439_TOUCHSCREEN_H

enum xiaomi_sdm439_touchscreen_types {
    XIAOMI_SDM439_TOUCHSCREEN_UNKNOWN,
    XIAOMI_SDM439_TOUCHSCREEN_GT1511Q,
    XIAOMI_SDM439_TOUCHSCREEN_FT5446,
    XIAOMI_SDM439_TOUCHSCREEN_ITK9881H,
    XIAOMI_SDM439_TOUCHSCREEN_NT36525B,
    XIAOMI_SDM439_TOUCHSCREEN_FT8006S,
};

extern enum xiaomi_sdm439_touchscreen_types xiaomi_sdm439_touchscreen_type;

#if IS_ENABLED(CONFIG_TOUCHSCREEN_SYSCTL_MI439)
#include <linux/device.h>

struct xiaomi_sdm439_touchscreen_operations_t {
	int (*enable_dt2w)(bool enable);
};

extern int xiaomi_sdm439_touchscreen_register_operations(struct xiaomi_sdm439_touchscreen_operations_t *ts_ops);
extern bool xiaomi_sdm439_touchscreen_get_dt2w_state(void);
#endif

#endif
