// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#include <linux/kernel.h>
#include "board-dt.h"
#include <asm/mach/map.h>
#include <asm/mach/arch.h>

static const char *msm8920_dt_match[] __initconst = {
	"qcom,msm8920",
	NULL
};

static void __init msm8920_init(void)
{
	board_dt_populate(NULL);
}

DT_MACHINE_START(MSM8920_DT,
	"Qualcomm Technologies, Inc. MSM 8920 (Flattened Device Tree)")
	.init_machine = msm8920_init,
	.dt_compat = msm8920_dt_match,
MACHINE_END
