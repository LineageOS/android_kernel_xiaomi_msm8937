#ifndef _XIAOMI_MSM8937_TOUCHSCREEN_H
#define _XIAOMI_MSM8937_TOUCHSCREEN_H

extern bool xiaomi_msm8937_touchscreen_is_probed;

#if IS_ENABLED(CONFIG_TOUCHSCREEN_SYSCTL_MI8937)
#include <linux/device.h>

struct xiaomi_msm8937_touchscreen_operations_t {
	struct device *dev;
	int (*enable_dt2w)(struct device *dev, bool enable);
	int (*disable_keys)(struct device *dev, bool disable);
};

extern int xiaomi_msm8937_touchscreen_register_operations(struct xiaomi_msm8937_touchscreen_operations_t *ts_ops);
#endif

#endif
