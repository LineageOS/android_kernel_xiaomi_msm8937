/* Copyright (C) 2018 XiaoMi, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/platform_device.h>
#include <linux/printk.h>
#include "msm_sd.h"
#include "msm_eeprom.h"

#define CONFIG_KERNEL_CUSTOM_L6200
#define CONFIG_KERNEL_CUSTOM_L6210

#define BUFFER_NUM 359
#define CAMERA_VENDOR_EEPROM_COUNT_MAX 6

enum __camera_vendor_module_id {
	MID_NULL = 0,
	MID_SUNNY,
	MID_TRULY,
	MID_A_KERR,
	MID_LITEARRAY,
	MID_DARLING,
	MID_QTECH,
	MID_OFILM,
	MID_HUAQUAN,
	MID_KINGCOM = MID_HUAQUAN,
	MID_BOOYI,
	MID_LAIMU,
	MID_D3 = 0x0d,
	MID_D6 = 0x0e,
	MID_WDSEN,
	MID_SUNRISE,
	MID_PRIMAX = 0x17,
	MID_MAX
};
typedef enum __camera_vendor_module_id camera_vendor_module_id;

struct vendor_eeprom {
	char eeprom_name[128];
	uint8_t module_id;
};
static struct vendor_eeprom s_vendor_eeprom[CAMERA_VENDOR_EEPROM_COUNT_MAX];

#ifdef CONFIG_KERNEL_CUSTOM_L6200
static camera_vendor_module_id
s5k5e8_oef0501_ofilm_get_otp_vendor_module_id(struct msm_eeprom_ctrl_t *e_ctrl)
{
	uint32_t MODULE_INFO_OFFSET;
	uint8_t mid = 0;
	uint8_t tempflag;
	uint8_t *buffer = e_ctrl->cal_data.mapdata;
	bool rc = false;

	printk("enter %s\n", __func__);
	tempflag = buffer[BUFFER_NUM + 103];
	printk("hjl %s tempflag=%d\n", __func__, tempflag);
	if (tempflag) {
		if (buffer[BUFFER_NUM + 1]) {
			MODULE_INFO_OFFSET = BUFFER_NUM + 3;
		} else if (buffer[BUFFER_NUM + 35]) {
			MODULE_INFO_OFFSET = BUFFER_NUM + 37;
		} else if (buffer[BUFFER_NUM + 69]) {
			MODULE_INFO_OFFSET = BUFFER_NUM + 71;
		} else {
			pr_err("hjl %s %d invalid flag1 ,flag2 and flag3 of "
				   "module\n",
				   __func__, __LINE__);
		}
	} else {
		if (buffer[BUFFER_NUM + 1]) {
			MODULE_INFO_OFFSET = BUFFER_NUM + 3;
		} else if (buffer[BUFFER_NUM + 27]) {
			MODULE_INFO_OFFSET = BUFFER_NUM + 29;
		} else if (buffer[BUFFER_NUM + 53]) {
			MODULE_INFO_OFFSET = BUFFER_NUM + 55;
		} else {
			pr_err("hjl %s %d invalid flag1 ,flag2 and flag3 of "
				   "module\n",
				   __func__, __LINE__);
		}
	}

	mid = buffer[MODULE_INFO_OFFSET];

	pr_err("hjl %s mid_vendor=0x%x\n", __func__, mid);
	rc = (mid == MID_OFILM) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	return mid;
}
static camera_vendor_module_id
s5k5e8_f5e8ybf_qtech_get_otp_vendor_module_id(struct msm_eeprom_ctrl_t *e_ctrl)
{
	uint32_t MODULE_INFO_OFFSET;
	uint8_t mid = 0;

	uint8_t *buffer = e_ctrl->cal_data.mapdata;
	bool rc = false;

	printk("enter %s\n", __func__);

	if (buffer[BUFFER_NUM + 1]) {
		MODULE_INFO_OFFSET = BUFFER_NUM + 3;
	} else if (buffer[BUFFER_NUM + 27]) {
		MODULE_INFO_OFFSET = BUFFER_NUM + 29;

	} else {
		pr_err("hjl %s %d invalid flag1 and flag2 of module\n",
			   __func__, __LINE__);
	}

	mid = buffer[MODULE_INFO_OFFSET];

	pr_err("hjl %s mid_vendor=0x%x\n", __func__, mid);
	rc = (mid == MID_QTECH) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	return mid;
}
#endif

#ifdef CONFIG_KERNEL_CUSTOM_L6210
static camera_vendor_module_id
s5k3p8sp_d16s01n_sunny_d6s_get_otp_vendro_module_id(
	struct msm_eeprom_ctrl_t *e_ctrl)
{
	uint8_t MODULE_INFO_OFFSET = 0x01;
	uint8_t LENS_INFO_OFFSET = 0x08;
	uint8_t MID_FLAG_OFFSET = 0x00;
	uint8_t mid = 0;
	uint8_t flag = 0;
	uint8_t lensid = 0;
	uint8_t *buffer = e_ctrl->cal_data.mapdata;
	bool rc = false;

	lensid = buffer[LENS_INFO_OFFSET];
	mid = buffer[MODULE_INFO_OFFSET];
	flag = buffer[MID_FLAG_OFFSET];

	pr_err("hjl %s mid=0x%x, flag=0x%x ,lensid = 0x%x \n", __func__, mid,
		   flag, lensid);
	rc = (mid == MID_SUNNY && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	rc = (lensid == 0x0e && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	pr_err("hjl %s mid=0x%x, flag=0x%x ,lensid = 0x%x \n", __func__, mid,
		   flag, lensid);
	return mid;
}
static camera_vendor_module_id
ov16885_ojf0541_ofilm_d6s_get_otp_vendor_module_id(
	struct msm_eeprom_ctrl_t *e_ctrl)
{
	uint8_t MODULE_INFO_OFFSET = 0x01;
	uint8_t SENSOR_INFO_OFFSET = 0x0C;
	uint8_t MID_FLAG_OFFSET = 0x00;
	uint8_t mid = 0;
	uint8_t flag = 0;
	uint8_t sensorid = 0;
	uint8_t *buffer = e_ctrl->cal_data.mapdata;
	bool rc = false;

	sensorid = buffer[SENSOR_INFO_OFFSET];
	mid = buffer[MODULE_INFO_OFFSET];
	flag = buffer[MID_FLAG_OFFSET];

	printk("hjl %s mid=0x%x, flag=0x%x ,sensorid = 0x%x \n", __func__, mid,
		   flag, sensorid);
	rc = (mid == MID_OFILM && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	rc = (sensorid == 0x14 && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	pr_err("hjl %s mid=0x%x, flag=0x%x ,sensorid = 0x%x \n", __func__, mid,
		   flag, sensorid);
	return mid;
}
#endif

#if (defined CONFIG_KERNEL_CUSTOM_L6200) || (defined CONFIG_KERNEL_CUSTOM_L6210)
static camera_vendor_module_id
s5k3l8_ohp0502_ofilm_get_otp_vendor_module_id(struct msm_eeprom_ctrl_t *e_ctrl)
{
	uint8_t MODULE_INFO_OFFSET = 0x07;
	uint8_t LENS_INFO_OFFSET = 0x08;
	uint8_t MID_FLAG_OFFSET = 0x00;
	uint8_t mid = 0;
	uint8_t flag = 0;
	uint8_t lensid = 0;
	uint8_t *buffer = e_ctrl->cal_data.mapdata;
	bool rc = false;

	lensid = buffer[LENS_INFO_OFFSET];
	mid = buffer[MODULE_INFO_OFFSET];
	flag = buffer[MID_FLAG_OFFSET];

	printk("Lct %s mid=0x%x, flag=0x%x ,lensid = 0x%x \n", __func__, mid,
		   flag, lensid);
	rc = (mid == MID_OFILM && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	rc = (lensid == 0x13 && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	pr_err("Lct %s mid=0x%x, flag=0x%x ,lensid = 0x%x \n", __func__, mid,
		   flag, lensid);
	return mid;
}
static camera_vendor_module_id ov13855_f13855bd_qtech_get_otp_vendor_module_id(
	struct msm_eeprom_ctrl_t *e_ctrl)
{
	uint8_t MODULE_INFO_OFFSET = 0x07;
	uint8_t LENS_INFO_OFFSET = 0x08;
	uint8_t MID_FLAG_OFFSET = 0x00;
	uint8_t mid = 0;
	uint8_t flag = 0;
	uint8_t lensid = 0;
	uint8_t *buffer = e_ctrl->cal_data.mapdata;
	bool rc = false;

	lensid = buffer[LENS_INFO_OFFSET];
	mid = buffer[MODULE_INFO_OFFSET];
	flag = buffer[MID_FLAG_OFFSET];

	printk("Lct %s mid=0x%x, flag=0x%x, lensid = 0x%x\n", __func__, mid,
		   flag, lensid);
	rc = (mid == MID_QTECH && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	rc = (lensid == 0x10 && flag == 0x01) ? true : false;
	if (rc == false)
		mid = MID_NULL;
	pr_err("Lct %s mid=0x%x, flag=0x%x, lensid = 0x%x \n", __func__, mid,
		   flag, lensid);
	return mid;
}
#endif

static uint8_t get_otp_vendor_module_id(struct msm_eeprom_ctrl_t *e_ctrl,
					const char *eeprom_name)
{
	camera_vendor_module_id module_id = MID_NULL;

#ifdef CONFIG_KERNEL_CUSTOM_L6200
	printk("hjl enter D6 front camera\n");
	if (strcmp(eeprom_name, "s5k5e8_oef0501_ofilm") == 0) {
		module_id =
			s5k5e8_oef0501_ofilm_get_otp_vendor_module_id(e_ctrl);
	} else if (strcmp(eeprom_name, "s5k5e8_f5e8ybf_qtech") == 0) {
		module_id =
			s5k5e8_f5e8ybf_qtech_get_otp_vendor_module_id(e_ctrl);
	}

#endif

#ifdef CONFIG_KERNEL_CUSTOM_L6210
	printk("hjl enter D6s front camera\n");
	if (strcmp(eeprom_name, "s5k3p8sp_d16s01n_sunny_d6s") == 0) {
		module_id =
			s5k3p8sp_d16s01n_sunny_d6s_get_otp_vendro_module_id(e_ctrl);
	} else if (strcmp(eeprom_name, "ov16885_ojf0541_ofilm_d6s") == 0) {
		module_id =
			ov16885_ojf0541_ofilm_d6s_get_otp_vendor_module_id(e_ctrl);
	}
#endif

#if (defined CONFIG_KERNEL_CUSTOM_L6200) || (defined CONFIG_KERNEL_CUSTOM_L6210)
	printk("hjl enter D6 and D6's back camera\n");
	if (strcmp(eeprom_name, "s5k3l8_ohp0502_ofilm") == 0) {
		module_id =
			s5k3l8_ohp0502_ofilm_get_otp_vendor_module_id(e_ctrl);
	} else if (strcmp(eeprom_name, "ov13855_f13855bd_qtech") == 0) {
		module_id =
			ov13855_f13855bd_qtech_get_otp_vendor_module_id(e_ctrl);
	}

#endif
	printk("hjl %s %d eeprom_name=%s, module_id=0x%x\n", __func__, __LINE__,
		   eeprom_name, module_id);
	if (module_id >= MID_MAX)
		module_id = MID_NULL;

	return ((uint8_t)module_id);
}

void xiaomi_ulysse_set_s_vendor_eeprom(
	struct platform_device *pdev, struct msm_eeprom_ctrl_t *e_ctrl,
	struct msm_eeprom_board_info *eb_info)
{
	if (eb_info->eeprom_name != NULL) {
		s_vendor_eeprom[pdev->id].module_id =
			get_otp_vendor_module_id(e_ctrl, eb_info->eeprom_name);
		strcpy(s_vendor_eeprom[pdev->id].eeprom_name,
			   eb_info->eeprom_name);
	}
}

int xiaomi_ulysse_match_sensor_eeprom(
	struct msm_camera_sensor_slave_info *slave_info)
{
	int i = 0;

	printk("hjl reading to enter L6200\n");
	printk("slave_info->eeprom_name=%s, s_vendor_eeprom=%s\n",
		   slave_info->eeprom_name, s_vendor_eeprom[i].eeprom_name);

#ifdef CONFIG_KERNEL_CUSTOM_L6200
	printk("lct entered CONFIG_KERNEL_CUSTOM_L6200!\n");
	if (s_vendor_eeprom[i].eeprom_name != NULL) {
		for (i = 0; i < CAMERA_VENDOR_EEPROM_COUNT_MAX; i++) {
			if (strcmp(slave_info->eeprom_name,
				   s_vendor_eeprom[i].eeprom_name) == 0) {

				printk("lct slave_info->sensor_name =%s, "
					   "module_id=%d\n",
					   slave_info->sensor_name,
					   s_vendor_eeprom[i].module_id);
				if (((strcmp(slave_info->sensor_name,
						 "s5k5e8_oef0501_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_OFILM)) ||
					((strcmp(slave_info->sensor_name,
						 "s5k5e8_f5e8ybf_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_QTECH)) ||
					((strcmp(slave_info->sensor_name,
						 "s5k3l8_ohp0502_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_OFILM)) ||
					((strcmp(slave_info->sensor_name,
						 "ov13855_f13855bd_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_QTECH))) {
					printk("lct module found!probe "
						   "continue!\n");
					return 0;
				}
			}
		}
	}
#endif

#ifdef CONFIG_KERNEL_CUSTOM_L6210
	printk("lct enter CONFIG_KERNEL_CUSTOM_L6210!\n");
	if (s_vendor_eeprom[i].eeprom_name != NULL) {
		for (i = 0; i < CAMERA_VENDOR_EEPROM_COUNT_MAX; i++) {
			printk(
				"slave_info->eeprom_name=%s, s_vendor_eeprom=%s\n",
				slave_info->eeprom_name,
				s_vendor_eeprom[i].eeprom_name);
			printk("slave_info->sensor_name=%s\n",
				   slave_info->sensor_name);
			if (strcmp(slave_info->eeprom_name,
				   s_vendor_eeprom[i].eeprom_name) == 0) {

				printk("lct slave_info->sensor_name =%s, "
					   "module_id=%d\n",
					   slave_info->sensor_name,
					   s_vendor_eeprom[i].module_id);
				if (((strcmp(slave_info->sensor_name,
						 "s5k3p8sp_d16s01n_d6s") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_SUNNY)) ||
					((strcmp(slave_info->sensor_name,
						 "ov16885_ojf0541_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_OFILM)) ||
					((strcmp(slave_info->sensor_name,
						 "s5k3l8_ohp0502_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_OFILM)) ||
					((strcmp(slave_info->sensor_name,
						 "ov13855_f13855bd_d6") == 0) &&
					 (s_vendor_eeprom[i].module_id ==
					  MID_QTECH))) {
					printk("lct module found!probe "
						   "continue!\n");
					return 0;
				}
			}
		}
	}
#endif

	if (i >= CAMERA_VENDOR_EEPROM_COUNT_MAX) {
		pr_err("lct module not found!probe break failed!\n");
		return -EFAULT;
	}

	return 0;
}
