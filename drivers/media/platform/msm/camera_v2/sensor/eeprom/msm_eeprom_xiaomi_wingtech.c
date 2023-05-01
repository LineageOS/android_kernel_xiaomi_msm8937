/* Copyright (C) 2019 XiaoMi, Inc.
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

#include <linux/kobject.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-msm8937/mach.h>
#include "msm_sd.h"
#include "msm_eeprom.h"
#include "../msm_sensor.h"

extern int ov13850_eeprom_sensor_writereg(struct msm_eeprom_ctrl_t *s_ctrl,
					  uint32_t reg_addr, uint32_t reg_value,
					  uint32_t delay);

#undef CDBG
#define CDBG(fmt, args...) pr_debug(fmt, ##args)

#if IS_ENABLED(CONFIG_MACH_XIAOMI_TIARE)
#define HI556_USE_OTP 1
#ifdef HI556_USE_OTP
extern int hi556_insensor_read_otp_info(struct msm_eeprom_ctrl_t *e_ctrl);
#endif
#endif

static char fusionid_back_d1[64] = {0};
static char fusionid_front_d1[64] = {0};
static char fusionid_back[64] = {0};
static char fusionid_front[64] = {0};

static int module_id = -1;
static int main_module_id = -1;
static int sub_module_id = -1;

static struct kobject kobj_back;
static struct kobject kobj_front;

static ssize_t kobj_fusion_id_show_back(struct kobject *kobject,
					struct attribute *attr, char *buf)
{
	CDBG("back_attrname:%s", attr->name);
	return sprintf(buf, "%s", fusionid_back);
}

static struct sysfs_ops obj_camera_sysops_back = {
	.show = kobj_fusion_id_show_back,
	.store = NULL,
};

static struct attribute camera_attr_back = {
	.name = "fusion_id_back",
	.mode = S_IRWXUGO,
};

static struct attribute *def_attrs_back[] = {
	&camera_attr_back,
	NULL,
};

static struct kobj_type ktype_back = {
	.release = NULL,
	.sysfs_ops = &obj_camera_sysops_back,
	.default_attrs = def_attrs_back,
};

static ssize_t kobj_fusion_id_show_front(struct kobject *kobject,
					 struct attribute *attr, char *buf)
{
	CDBG("front_attrname:%s", attr->name);
	return sprintf(buf, "%s", fusionid_front);
}

static struct sysfs_ops obj_camera_sysops_front = {
	.show = kobj_fusion_id_show_front,
	.store = NULL,
};

static struct attribute camera_attr_front = {
	.name = "fusion_id_front",
	.mode = S_IRWXUGO,
};

static struct attribute *def_attrs_front[] = {
	&camera_attr_front,
	NULL,
};

static struct kobj_type ktype_front = {
	.release = NULL,
	.sysfs_ops = &obj_camera_sysops_front,
	.default_attrs = def_attrs_front,
};

static uint16_t fusion_read_id_s5k3l8(struct msm_sensor_ctrl_t *s_ctrl)
{
	uint16_t value1, value3, value5;

	struct msm_camera_i2c_client *sensor_i2c_client;
	sensor_i2c_client = s_ctrl->sensor_i2c_client;

	memset(fusionid_back, 0, sizeof(fusionid_back));
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0100,
						   0x0100, 2);
	mdelay(10);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0a02,
						   0x0000, 2);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0a00,
						   0x0100, 2);
	mdelay(10);
	sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client, 0x0a24,
						  &value1, 2);
	CDBG(" s5k3l8 fusion_sensor_readreg value1 =%d\n", value1);
	sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client, 0x0a26,
						  &value3, 2);
	CDBG(" s5k3l8 fusion_sensor_readreg value3 =%d\n", value3);
	sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client, 0x0a28,
						  &value5, 1);
	CDBG(" s5k3l8 fusion_sensor_readreg value5 =%d\n", value5);
	sprintf(fusionid_back, "%d%d%d", value1, value3, value5);
	CDBG(" s5k3l8 fusion_sensor_readreg fusionid=%s\n", fusionid_back);
	return 0;
}

static uint16_t fusion_read_id_ov5675(struct msm_sensor_ctrl_t *s_ctrl)
{
	uint16_t data[15] = {0};
	uint16_t *p = NULL;
	uint8_t i;
	struct msm_camera_i2c_client *sensor_i2c_client;
	sensor_i2c_client = s_ctrl->sensor_i2c_client;

	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0100,
						   0x01, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x5001,
						   0x02, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d84,
						   0xC0, 1);

	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d88,
						   0x70, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d89,
						   0x00, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d8a,
						   0x70, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d8b,
						   0x0f, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d81,
						   0x01, 1);
	mdelay(10);

	p = data;

	memset(fusionid_front, 0, sizeof(fusionid_front));
	for (i = 0; i < 15; i++) {
		sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client,
							  0x7000 + i, p + i, 1);
		CDBG("data[%d]=%x\n", i, data[i]);
		sprintf(fusionid_front + strlen(fusionid_front), "%u", data[i]);
	}
	CDBG("fusionid_front=%s\n", fusionid_front);
	return 0;
}

static uint16_t fusion_read_id_s5k5e8(struct msm_sensor_ctrl_t *s_ctrl)
{
	uint16_t data[8] = {0};
	uint16_t *p = NULL;
	uint8_t i;
	struct msm_camera_i2c_client *sensor_i2c_client;
	sensor_i2c_client = s_ctrl->sensor_i2c_client;

	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0a00,
						   0x04 & 0x00ff, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0a02,
						   0x00 & 0x00ff, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0a00,
						   0x01 & 0x00ff, 1);
	mdelay(10);
	p = data;

	memset(fusionid_front, 0, sizeof(fusionid_front));
	for (i = 0; i < 8; i++) {
		sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client,
							  0x0a04 + i, p + i, 1);
		CDBG("data[%d]=%x\n", i, data[i]);
		sprintf(fusionid_front + strlen(fusionid_front), "%u", data[i]);
	}
	CDBG("fusionid_front=%s\n", fusionid_front);

	return 0;
}

static uint16_t fusion_read_id_ov13855(struct msm_sensor_ctrl_t *s_ctrl)
{
	uint16_t data[16] = {0};
	uint16_t *p = NULL;
	uint16_t temp1 = 0x0;
	uint8_t i;
	struct msm_camera_i2c_client *sensor_i2c_client;
	sensor_i2c_client = s_ctrl->sensor_i2c_client;

	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x0100,
						   0x01, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client, 0x5000,
						  &temp1, 1);

	sensor_i2c_client->i2c_func_tbl->i2c_write(
		sensor_i2c_client, 0x5000, (0x00 & 0x10) | (temp1 & (~0x10)), 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d84,
						   0xC0, 1);

	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d88,
						   0x70, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d89,
						   0x00, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d8a,
						   0x70, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d8b,
						   0x0f, 1);
	sensor_i2c_client->i2c_func_tbl->i2c_write(sensor_i2c_client, 0x3d81,
						   0x01, 1);
	mdelay(10);

	p = data;

	memset(fusionid_back, 0, sizeof(fusionid_back));
	for (i = 0; i < 15; i++) {
		sensor_i2c_client->i2c_func_tbl->i2c_read(sensor_i2c_client,
							  0x7000 + i, p + i, 1);
		CDBG("data[%d]=%x\n", i, data[i]);
		sprintf(fusionid_back + strlen(fusionid_back), "%u", data[i]);
	}
	CDBG("fusionid_back=%s\n", fusionid_back);
	return 0;
}

static uint16_t fusion_read_id_D1_back(uint8_t *data)
{
	uint16_t i;
	uint8_t *fusion_id = data;
	memset(fusionid_back_d1, 0, sizeof(fusionid_back_d1));
	for (i = 0; i < 16; i++) {
		sprintf(fusionid_back_d1 + strlen(fusionid_back_d1), "%u",
			fusion_id[i]);
	}
	CDBG("fusionid_back: %s\n", fusionid_back_d1);
	return 0;
}

static uint16_t fusion_read_id_D1_front(uint8_t *data)
{
	uint16_t i;
	uint8_t *fusion_id = data;
	memset(fusionid_front_d1, 0, sizeof(fusionid_front_d1));
	for (i = 0; i < 16; i++) {
		sprintf(fusionid_front_d1 + strlen(fusionid_front_d1), "%u",
			fusion_id[i]);
	}
	CDBG("fusionid_front: %s\n", fusionid_front_d1);
	return 0;
}

int xiaomi_wingtech_eeprom_match_id(
	struct msm_eeprom_ctrl_t *e_ctrl, struct msm_eeprom_board_info *eb_info)
{
#ifdef HI556_USE_OTP
	int rc = 0;
#endif

	if (!strcmp(eb_info->eeprom_name, "s5k3l8_ofilm")) {
		CDBG("match id for s5k3l8_ofilm\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k3l8_ofilm module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for s5k3l8_ofilm success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for s5k3l8_ofilm failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k3l8_ofilm_riva")) {
		CDBG("match id for s5k3l8_ofilm_riva\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k3l8_ofilm_riva module_id=%d\n",
			   module_id);
		if (module_id == 7) {
			CDBG("match id for s5k3l8_ofilm_riva success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for s5k3l8_ofilm_riva failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k3l8_sunny")) {
		CDBG("match id for s5k3l8_sunny\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k3l8_sunny module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for s5k3l8_sunny success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for s5k3l8_sunny failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ov13855_qtech")) {
		CDBG("match id for ov13855_qtech\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for ov13855_qtech module_id=%d\n", module_id);
		if (module_id == 11) {
			CDBG("match id for ov13855_qtech success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for ov13855_qtech failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ov13855_sunny")) {
		CDBG("match id for ov13855_sunny\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for ov13855_sunny module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for ov13855_sunny success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for ov13855_sunny failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ov13850")) {

		printk("match id for ov13850 AWB:[mapdata[8]:0x%x, "
			   "mapdata[9]:0x%x; mapdata[0]:0x%x, mapdata[1]:0x%x] "
			   "AF:[mapdata[16]:0x%x mapdata[24]:0x%x] "
			   "LSC:[mapdata[32]:0x%x mapdata[221]:0x%x]\n",
			   e_ctrl->cal_data.mapdata[8],
			   e_ctrl->cal_data.mapdata[9] & 0x1f,
			   e_ctrl->cal_data.mapdata[0],
			   e_ctrl->cal_data.mapdata[1] & 0x1f,
			   e_ctrl->cal_data.mapdata[16],
			   e_ctrl->cal_data.mapdata[24],
			   e_ctrl->cal_data.mapdata[32],
			   e_ctrl->cal_data.mapdata[221]);
		if (e_ctrl->cal_data.mapdata[8] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for ov13850 module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for ov13850 success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for ov13850 failed\n", __func__);
			goto power_down;
		}
		if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_RIVA ||
			xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_ROLEX)
			ov13850_eeprom_sensor_writereg(e_ctrl, 0x0100, 0x00, 1);
	} else if (!strcmp(eb_info->eeprom_name, "s5k3l2")) {
		CDBG("match id for s5k3l2\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k3l2 module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for s5k3l2 success\n");
			main_module_id = module_id;
		} else {
			pr_err("%s match id for s5k3l2 failed\n", __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ov5675_ofilm")) {
		CDBG("match id for ov5675_ofilm\n");
		if (e_ctrl->cal_data.mapdata[16] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[17] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[8] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for ov5675_ofilm module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for ov5670_ofilm success\n");
			sub_module_id = module_id;
		} else {
			pr_err("%s match id for ov5670_ofilm failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ovt_ov5675_i")) {
		CDBG("match id for ovt_ov5675_i\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;

		} else if (e_ctrl->cal_data.mapdata[80] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[81] & 0x1f;

		} else {
			module_id = -1;
		}
		printk("match id for ovt_ov5675_i module_id=%d\n", module_id);
		if (module_id == 6) {
			CDBG("match id for ovt_ov5675_i success\n");
			sub_module_id = module_id;
			fusion_read_id_D1_front(&e_ctrl->cal_data.mapdata[16]);
			strcpy(fusionid_front,
				   fusionid_front_d1 + strlen(fusionid_front_d1));
		} else {
			pr_err("%s match id for ovt_ov5675_i failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ovt_ov5675_ii")) {
		CDBG("match id for ovt_ov5675_ii\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;

		} else if (e_ctrl->cal_data.mapdata[80] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[81] & 0x1f;

		} else {
			module_id = -1;
		}
		printk("match id for ovt_ov5675_ii module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for ovt_ov5675_ii success\n");
			sub_module_id = module_id;
			fusion_read_id_D1_front(&e_ctrl->cal_data.mapdata[16]);
			strcpy(fusionid_front,
				   fusionid_front_d1 + strlen(fusionid_front_d1));
		} else {
			pr_err("%s match id for ovt_ov5675_ii failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k5e8_sunny")) {
		CDBG("match id for s5k5e8_sunny\n");
		if (e_ctrl->cal_data.mapdata[16] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[17] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[8] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k5e8_sunny module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for s5k5e8_sunny success\n");
			sub_module_id = module_id;
		} else {
			pr_err("%s match id for s5k5e8_sunny failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k5e8_ofilm_riva")) {
		CDBG("match id for s5k5e8_ofilm_riva\n");
		if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_TIARE) {
			if (e_ctrl->cal_data.mapdata[52] == 0x55) {
				module_id = e_ctrl->cal_data.mapdata[54] & 0x1f;
			} else if (e_ctrl->cal_data.mapdata[26] == 0x55) {
				module_id = e_ctrl->cal_data.mapdata[28] & 0x1f;
			} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
				module_id = e_ctrl->cal_data.mapdata[2] & 0x1f;
			} else {
				module_id = -1;
			}
		} else {
			if (e_ctrl->cal_data.mapdata[16] == 0x55) {
				module_id = e_ctrl->cal_data.mapdata[17] & 0x1f;
			} else if (e_ctrl->cal_data.mapdata[8] == 0x55) {
				module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
			} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
				module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
			} else {
				module_id = -1;
			}
		}
		printk("match id for s5k5e8_ofilm_riva module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for s5k5e8_ofilm_riva success\n");
			sub_module_id = module_id;
		} else {
			pr_err("%s match id for s5k5e8_ofilm_riva failed\n", __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ov5675")) {
		CDBG("match id for ov5675\n");
		if (e_ctrl->cal_data.mapdata[16] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[17] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[8] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for ov5675 module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for ov5675 success\n");
			sub_module_id = module_id;
		} else {
			pr_err("%s match id for ov5670 failed\n", __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k5e8_qtech_riva")) {
		CDBG("match id for s5k5e8_qtech_riva\n");
		if (e_ctrl->cal_data.mapdata[16] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[17] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[8] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k5e8_qtech_riva module_id=%d\n",
			   module_id);
		if (module_id == 11) {
			CDBG("match id for s5k5e8_qtech_riva success\n");
			sub_module_id = module_id;
		} else {
			pr_err("%s match id for s5k5e8_qtech_riva failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k5e8_ofilm")) {
		CDBG("match id for s5k5e8_ofilm\n");
		if (e_ctrl->cal_data.mapdata[16] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[17] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[8] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[9] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k5e8_ofilm module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for s5k5e8_ofilm success\n");
			sub_module_id = module_id;
		} else {
			pr_err("%s match id for s5k5e8_ofilm failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "ovt_ov12a10_i")) {
		CDBG("match id for ovt_ov12a10_i\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for ovt_ov12a10_i module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for ovt_ov12a10_i success\n");
			main_module_id = module_id;
			fusion_read_id_D1_back(&e_ctrl->cal_data.mapdata[16]);
			strcpy(fusionid_back,
				   fusionid_back_d1 + strlen(fusionid_back_d1));
		} else {
			pr_err("%s match id for ovt_ov12a10_i failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "sony_imx486_ii")) {
		CDBG("match id for sony_imx486_ii\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for sony_imx486_ii module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for sony_imx486_ii success\n");
			main_module_id = module_id;
			fusion_read_id_D1_back(&e_ctrl->cal_data.mapdata[16]);
			strcpy(fusionid_back,
				   fusionid_back_d1 + strlen(fusionid_back_d1));
		} else {
			pr_err("%s match id for sony_imx486_ii failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "s5k4h7_ofilm")) {
		CDBG("match id for s5k4h7_ofilm\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for s5k4h7_ofilm module_id=%d\n", module_id);
		if (module_id == 7) {
			CDBG("match id for s5k4h7_ofilm success\n");
			main_module_id = module_id;
			fusion_read_id_D1_back(&e_ctrl->cal_data.mapdata[16]);
			strcpy(fusionid_back, fusionid_back_d1);
		} else {
			pr_err("%s match id for s5k4h7_ofilm failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "gc8034_sunny")) {
		CDBG("match id for gc8034_sunny\n");
		if (e_ctrl->cal_data.mapdata[0] == 0x01) {
			module_id = e_ctrl->cal_data.mapdata[1] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for gc8034_sunny module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for gc8034_sunny success\n");
			main_module_id = module_id;
			fusion_read_id_D1_back(&e_ctrl->cal_data.mapdata[16]);
			strcpy(fusionid_back, fusionid_back_d1);
		} else {
			pr_err("%s match id for gc8034_sunny failed\n",
				   __func__);
			goto power_down;
		}
	} else if (!strcmp(eb_info->eeprom_name, "hi556_sunny")) {
		CDBG("match id for hi556_sunny\n");
#ifdef HI556_USE_OTP
		rc = hi556_insensor_read_otp_info(e_ctrl);
		if (rc < 0) {
			pr_err("%s hi556_insensor_read_otp_info failed!\n",
				   __func__);
			goto power_down;
		}
#endif
		if (e_ctrl->cal_data.mapdata[52] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[54] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[26] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[28] & 0x1f;
		} else if (e_ctrl->cal_data.mapdata[0] == 0x55) {
			module_id = e_ctrl->cal_data.mapdata[2] & 0x1f;
		} else {
			module_id = -1;
		}
		printk("match id for hi556_sunny module_id=%d\n", module_id);
		if (module_id == 1) {
			CDBG("match id for hi556_sunny success\n");
			sub_module_id = module_id;
			fusion_read_id_D1_front(
				&e_ctrl->cal_data.mapdata[5388]);
			strcpy(fusionid_front, fusionid_front_d1);
		} else {
			pr_err("%s match id for hi556_sunny failed\n",
				   __func__);
			goto power_down;
		}
	} else {
		pr_err("%s eeprom name match failed\n", __func__);
		goto power_down;
	}
	CDBG("%s eeprom module id: main_module_id=%d  sub_module_id=%d\n",
		 __func__, main_module_id, sub_module_id);

	return 0;
power_down:
	return -EINVAL;
}

int xiaomi_wingtech_sensor_match_id(
	struct msm_camera_sensor_slave_info *slave_info)
{
	int rc = 0;

	if (!strcmp(slave_info->sensor_name, "s5k3l8_ofilm")) {
		if (main_module_id != 7) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k3l8_ofilm_riva")) {
		if (main_module_id != 7) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k4h7_ofilm")) {
		if (main_module_id != 7) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k3l8_sunny")) {
		if (main_module_id != 1) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ov13855_sunny")) {
		if (main_module_id != 1) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ov13855_qtech")) {
		if (main_module_id != 11) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ov13850_q13v06k")) {
		if (main_module_id != 1) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k3l2")) {
		if (main_module_id != 7) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ov5675_ofilm")) {
		if (sub_module_id != 7) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ovt_ov5675_i")) {
		if (sub_module_id != 6) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ovt_ov5675_ii")) {
		if (sub_module_id != 7) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "sony_imx486_ii")) {
		if (main_module_id != 1) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k5e8_sunny")) {
		if (sub_module_id != 1) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ov5675")) {
		if (sub_module_id != 1) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k5e8_ofilm")) {
		if (sub_module_id != 7) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k5e8_qtech_riva")) {
		if (sub_module_id != 11) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "s5k5e8_ofilm_riva")) {
		if (sub_module_id != 7) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "ovt_ov12a10_i")) {
		if (main_module_id != 7) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "gc8034_sunny")) {
		if (main_module_id != 1) {
			pr_err("failed: main_module_id %d, sensor is not %s",
				   main_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else if (!strcmp(slave_info->sensor_name, "hi556_sunny")) {
		if (sub_module_id != 1) {
			pr_err("failed: sub_module_id %d, sensor is not %s",
				   sub_module_id, slave_info->sensor_name);
			rc = -EINVAL;
			goto free_slave_info;
		}
	} else {
		pr_err("sensor name is %s, is nothing to do",
			   slave_info->sensor_name);
		rc = -EINVAL;
		goto free_slave_info;
	}

	pr_err("%s:%d camera sensor probe %s", __func__, __LINE__,
		   slave_info->sensor_name);

free_slave_info:
	return rc;
}

void xiaomi_wingtech_sensor_read_fusion_id(
	struct msm_camera_sensor_slave_info *slave_info,
	struct msm_sensor_ctrl_t *s_ctrl)
{
	if (xiaomi_msm8937_mach_get() == XIAOMI_MSM8937_MACH_SANTONI) {
		if (!strcmp(slave_info->sensor_name, "ov13855_sunny")) {
			fusion_read_id_ov13855(s_ctrl);
		} else if (!strcmp(slave_info->sensor_name, "s5k3l8_ofilm")) {
			fusion_read_id_s5k3l8(s_ctrl);
		} else if (!strcmp(slave_info->sensor_name, "ov5675_ofilm")) {
			fusion_read_id_ov5675(s_ctrl);
		} else if (!strcmp(slave_info->sensor_name, "s5k5e8_sunny")) {
			fusion_read_id_s5k5e8(s_ctrl);
		} else {
			printk("read fusion id fail\n");
		}
		return;
	}

	if (!strcmp(slave_info->sensor_name, "ov13855_qtech")) {
		fusion_read_id_ov13855(s_ctrl);
	} else if (!strcmp(slave_info->sensor_name, "s5k3l8_ofilm_riva")) {
		fusion_read_id_s5k3l8(s_ctrl);
	} else if (!strcmp(slave_info->sensor_name, "ov5675_ofilm")) {
		fusion_read_id_ov5675(s_ctrl);
	} else if ((!strcmp(slave_info->sensor_name, "s5k5e8_qtech_riva")) ||
		   (!strcmp(slave_info->sensor_name, "s5k5e8_ofilm_riva"))) {
		fusion_read_id_s5k5e8(s_ctrl);
	} else {
		printk("read fusion id fail\n");
	}
	return;
}

extern bool msmb_camera_enable;

static int __init msm_eeprom_xiaomi_wingtech_init()
{
	if (!msmb_camera_enable)
		return -ENODEV;
	kobject_init_and_add(&kobj_back, &ktype_back, NULL,
				 "camera_fusion_id_back");
	kobject_init_and_add(&kobj_front, &ktype_front, NULL,
				 "camera_fusion_id_front");
	return 0;
}
module_init(msm_eeprom_xiaomi_wingtech_init);
