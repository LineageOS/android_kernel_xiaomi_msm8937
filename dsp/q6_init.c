/*
Copyright (c) 2017, The Linux Foundation. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 and
only version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*
*/

#include <linux/export.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include "q6_init.h"

bool msm_enable_legacy_adsp_hacks = false;
EXPORT_SYMBOL(msm_enable_legacy_adsp_hacks);

static int __init audio_q6_init(void)
{
	msm_enable_legacy_adsp_hacks = of_property_read_bool(of_find_node_by_path("/"), "qcom,enable-legacy-adsp-hacks");

	adsp_err_init();
#ifdef MODULE
	audio_cal_init();
#endif
	rtac_init();
	adm_init();
	afe_init();
	q6asm_init();
	q6lsm_init();
	voice_init();
	core_init();
	msm_audio_ion_init();
	audio_slimslave_init();
	avtimer_init();
	return 0;
}

static void __exit audio_q6_exit(void)
{
	avtimer_exit();
	audio_slimslave_exit();
	msm_audio_ion_exit();
	core_exit();
	voice_exit();
	q6lsm_exit();
	q6asm_exit();
	afe_exit();
	adm_exit();
	rtac_exit();
#ifdef MODULE
	audio_cal_exit();
#endif
	adsp_err_exit();
}

module_init(audio_q6_init);
module_exit(audio_q6_exit);
MODULE_DESCRIPTION("Q6 module");
MODULE_LICENSE("GPL v2");
