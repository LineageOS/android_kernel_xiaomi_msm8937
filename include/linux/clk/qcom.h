/* SPDX-License-Identifier: GPL-2.0-only */
/*
<<<<<<< HEAD
 * Copyright (c) 2016, 2020-2021 The Linux Foundation. All rights reserved.
=======
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
>>>>>>> 0dc6e78a3fb3 (clk: msm: Add snapshot of clock framework files)
 */

#ifndef __LINUX_CLK_QCOM_H_
#define __LINUX_CLK_QCOM_H_

<<<<<<< HEAD
#include <linux/clk.h>
#include <linux/regulator/consumer.h>

=======
#if defined(CONFIG_COMMON_CLK_QCOM)
>>>>>>> 0dc6e78a3fb3 (clk: msm: Add snapshot of clock framework files)
enum branch_mem_flags {
	CLKFLAG_RETAIN_PERIPH,
	CLKFLAG_NORETAIN_PERIPH,
	CLKFLAG_RETAIN_MEM,
	CLKFLAG_NORETAIN_MEM,
	CLKFLAG_PERIPH_OFF_SET,
	CLKFLAG_PERIPH_OFF_CLEAR,
};
#elif defined(CONFIG_COMMON_CLK_MSM)
#include <linux/clk/msm-clk.h>
#endif /* CONFIG_COMMON_CLK_QCOM */

void qcom_clk_dump(struct clk *clk, struct regulator *regulator,
			bool calltrace);
void qcom_clk_bulk_dump(int num_clks, struct clk_bulk_data *clks,
			struct regulator *regulator, bool calltrace);

#endif  /* __LINUX_CLK_QCOM_H_ */
