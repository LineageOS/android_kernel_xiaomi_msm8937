// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2017, 2019-2020 The Linux Foundation. All rights reserved.
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
	spk_params_init();
	q6asm_init();
	q6lsm_init();
	voice_init();
	core_init();
	msm_audio_ion_init();
	audio_slimslave_init();
	avtimer_init();
	msm_mdf_init();
	voice_mhi_init();
	digital_cdc_rsc_mgr_init();
	return 0;
}

static void __exit audio_q6_exit(void)
{
	digital_cdc_rsc_mgr_exit();
	msm_mdf_exit();
	avtimer_exit();
	audio_slimslave_exit();
	msm_audio_ion_exit();
	core_exit();
	voice_exit();
	q6lsm_exit();
	q6asm_exit();
	afe_exit();
	spk_params_exit();
	adm_exit();
	rtac_exit();
#ifdef MODULE
	audio_cal_exit();
#endif
	adsp_err_exit();
	voice_mhi_exit();
}

module_init(audio_q6_init);
module_exit(audio_q6_exit);
MODULE_DESCRIPTION("Q6 module");
MODULE_LICENSE("GPL v2");
