/*
 * Copyright (C) 2015 MediaTek Inc.
 * Copyright (C) 2021 XiaoMi, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#ifndef __HQ_SYSFS_HEAD__
#define __HQ_SYSFS_HEAD__
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/kfifo.h>

#include <linux/firmware.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/of.h>
#ifdef CONFIG_OF
#include <linux/of_fdt.h>
#endif
#include <linux/atomic.h>

enum xiaomi_sdm439_hardware_id{
	XIAOMI_SDM439_HWID_NONE = 0x00,
	XIAOMI_SDM439_HWID_DDR = 0x10,
	XIAOMI_SDM439_HWID_EMMC,
	XIAOMI_SDM439_HWID_NAND,

	XIAOMI_SDM439_HWID_LCM = 0x20,
	XIAOMI_SDM439_HWID_SUB_LCM,
	XIAOMI_SDM439_HWID_BIAS_IC,
	XIAOMI_SDM439_HWID_CTP,

	XIAOMI_SDM439_HWID_MAIN_CAM = 0x30,
	XIAOMI_SDM439_HWID_MAIN_CAM_2,
	XIAOMI_SDM439_HWID_SUB_CAM,
	XIAOMI_SDM439_HWID_SUB_CAM_2,
	XIAOMI_SDM439_HWID_MAIN_LENS,
	XIAOMI_SDM439_HWID_MAIN_LENS_2,
	XIAOMI_SDM439_HWID_SUB_LENS,
	XIAOMI_SDM439_HWID_SUB_LENS_2,
	XIAOMI_SDM439_HWID_MAIN_OTP,
	XIAOMI_SDM439_HWID_MAIN_OTP_2,
	XIAOMI_SDM439_HWID_SUB_OTP,
	XIAOMI_SDM439_HWID_SUB_OTP_2,
	XIAOMI_SDM439_HWID_FLASHLIGHT,
	XIAOMI_SDM439_HWID_FLaSHLIGHT_2,

	XIAOMI_SDM439_HWID_GSENSOR = 0x70,
	XIAOMI_SDM439_HWID_ALSPS,
	XIAOMI_SDM439_HWID_GYRO,
	XIAOMI_SDM439_HWID_MSENSOR,
	XIAOMI_SDM439_HWID_IRDA,
	XIAOMI_SDM439_HWID_BAROMETER,
	XIAOMI_SDM439_HWID_PEDOMETER,
	XIAOMI_SDM439_HWID_HUMIDITY,

	XIAOMI_SDM439_HWID_PCBA = 0x80,

	XIAOMI_SDM439_HWID_BATERY = 0xA0,
	XIAOMI_SDM439_HWID_FUEL_GAUGE_IC,

	XIAOMI_SDM439_HWID_NFC = 0xC0,
	XIAOMI_SDM439_HWID_FP,
	XIAOMI_SDM439_HWID_TEE,

	XIAOMI_SDM439_HWID_USB_TYPE_C = 0xE0,


	XIAOMI_SDM439_HWID_SUMMARY = 0xF0,
	XIAOMI_SDM439_HWID_VER,
	XIAOMI_SDM439_HWID_END
};

int xiaomi_sdm439_hq_regiser_hw_info(enum xiaomi_sdm439_hardware_id id, char *device_name);
int xiaomi_sdm439_hq_deregister_hw_info(enum xiaomi_sdm439_hardware_id id, char *device_name);
int xiaomi_sdm439_register_kboj_under_hqsysfs(struct kobject *kobj, struct kobj_type *ktype, const char *fmt, ...);

#endif
