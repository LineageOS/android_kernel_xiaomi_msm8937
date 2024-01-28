/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 */

#ifndef __AUDIO_EXT_CLK_UP_H_
#define __AUDIO_EXT_CLK_UP_H_

#ifdef CONFIG_COMMON_CLK_QCOM
int audio_ref_clk_platform_init(void);
void audio_ref_clk_platform_exit(void);
#else
static inline int audio_ref_clk_platform_init(void)
{
	return 0;
}

static inline void audio_ref_clk_platform_exit(void)
{
}

#endif /*CONFIG_COMMON_CLK_QCOM*/
#endif
