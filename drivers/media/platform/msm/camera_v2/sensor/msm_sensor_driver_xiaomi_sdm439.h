#include <xiaomi-sdm439/hqsysfs.h>

static void msm_sensor_driver_probe_xiaomi_sdm439_hqsysfs_register(struct msm_sensor_ctrl_t *s_ctrl)
{
	uint32_t i = 0;

	static char olive_olivewood_rear_camera_str_buff[6][2][20] = {
		{"olive_imx486_ofilm", "sony_imx486_i"},
		{"olive_imx486_sunny", "sony_imx486_ii"},
		{"olive_imx363_qtech", "sony_imx363_i"},
		{"olive_s5k2l7_sunny", "samsung_s5k2l7_ii"},
		{"olive_ov13b10_qtech", "omnivision_13b10_i"},
		{"olive_ov13b10_ofilm", "omnivision_13b10_ii"},
	};
	static char olive_olivewood_front_camera_str_buff[3][2][20] = {
		{"olive_ov8856_qtech", "omnivision_8856_ii"},
		{"olive_ov8856_sunny", "omnivision_8856_i"},
		{"olive_s5k4h7_sunny", "samsung_s5k4h7_iii"},
	};
	static char olive_olivewood_rear_aux_camera_str_buff[5][2][30] = {
		{"olive_ov02a10_ofilm", "omnivision_02a10_i"},
		{"olive_gc2375_sunny", "galaxycore_2375_ii"},
		{"olivewood_gc02m1_sunny", "galaxycore_02m1_iii"},
		{"olive_gc02m1_sunny", "galaxycore_02m1_iii"},
		{"olive_gc02m1b_sunny", "galaxycore_02m1_iiii"},
	};

	static char olivelite_rear_camera_str_buff[6][2][20] = {
		{"olive_imx486_ofilm", "sony_imx486_i"},
		{"olive_imx486_sunny", "sony_imx486_ii"},
		{"olive_imx363_qtech", "sony_imx363_i"},
		{"olive_s5k2l7_sunny", "samsung_s5k2l7_ii"},
		{"olive_ov13b10_qtech", "omnivision_13b10_i"},
		{"olive_ov13b10_ofilm", "omnivision_13b10_ii"},
	};
	static char olivelite_front_camera_str_buff[3][2][20] = {
		{"olive_ov8856_qtech", "omnivision_8856_ii"},
		{"olive_ov8856_sunny", "omnivision_8856_i"},
		{"olive_s5k4h7_sunny", "samsung_s5k4h7_iii"},
	};

	if (xiaomi_sdm439_mach_get() == XIAOMI_SDM439_MACH_OLIVE || xiaomi_sdm439_mach_get() == XIAOMI_SDM439_MACH_OLIVEWOOD) {
		if (0 == s_ctrl->id) {
			for (i = 0; i < 6; i++)	{
				if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
					olive_olivewood_rear_camera_str_buff[i][0],
					strlen(s_ctrl->sensordata->eeprom_name)) == 0) {
					xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, olive_olivewood_rear_camera_str_buff[i][1]);
					break;
				}
			}
		} else if (1 == s_ctrl->id) {
			for (i = 0; i < 3; i++)	{
				if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
					olive_olivewood_front_camera_str_buff[i][0],
					strlen(s_ctrl->sensordata->eeprom_name)) == 0) {
					xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_SUB_CAM, olive_olivewood_front_camera_str_buff[i][1]);
					break;
				}
			}
		} else if (2 == s_ctrl->id) {
			for (i = 0; i < 5; i++)	{
				if (strncmp((char *)(s_ctrl->sensordata->sensor_name),
					olive_olivewood_rear_aux_camera_str_buff[i][0],
					strlen(s_ctrl->sensordata->sensor_name)) == 0) {
					xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM_2, olive_olivewood_rear_aux_camera_str_buff[i][1]);
					break;
				}
			}
		}
	} else if (xiaomi_sdm439_mach_get() == XIAOMI_SDM439_MACH_OLIVELITE) {
		if (0 == s_ctrl->id) {
			for (i = 0; i < 6; i++)	{
				if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
					olivelite_rear_camera_str_buff[i][0],
					strlen(s_ctrl->sensordata->eeprom_name)) == 0) {
					xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, olivelite_rear_camera_str_buff[i][1]);
					break;
				}
			}
		} else if (1 == s_ctrl->id) {
			for (i = 0; i < 3; i++)	{
				if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
					olivelite_front_camera_str_buff[i][0],
					strlen(s_ctrl->sensordata->eeprom_name)) == 0) {
					xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_SUB_CAM, olivelite_front_camera_str_buff[i][1]);
					break;
				}
			}
		}
	} else if (xiaomi_sdm439_mach_get() == XIAOMI_SDM439_MACH_PINE) {
		if (0 == s_ctrl->id) {
			if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_ov13855_qtech",
				strlen("pine_ov13855_qtech")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, "omnivision_13855_i");
			} else if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_ov13855_ofilm",
				strlen("pine_ov13855_ofilm")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, "omnivision_13855_ii");
			} else if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_imx486_qtech",
				strlen("pine_imx486_qtech")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, "sony_imx486_i");
			} else if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_imx486_holitech",
				strlen("pine_imx486_holitech")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, "sony_imx486_holitech_ii");
			} else if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_imx486_ofilm",
				strlen("pine_imx486_ofilm")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, "sony_imx486_ofilm_ii");
			}
			//xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_MAIN_CAM, (char *)(s_ctrl->sensordata->eeprom_name));
		} else if (1 == s_ctrl->id) {
			if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_gc5035_qtech",
				strlen("pine_gc5035_qtech")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_SUB_CAM, "galaxycore_5035_i");
			} else if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_gc5035_ofilm",
				strlen("pine_gc5035_ofilm")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_SUB_CAM, "galaxycore_5035_ii");
			} else if (strncmp((char *)(s_ctrl->sensordata->eeprom_name),
				"pine_gc5035_holitech",
				strlen("pine_gc5035_holitech")) == 0) {
				xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_SUB_CAM, "galaxycore_5035_iii");
			}
			//xiaomi_sdm439_hq_regiser_hw_info(XIAOMI_SDM439_HWID_SUB_CAM, (char *)(s_ctrl->sensordata->eeprom_name));
		}
	}
}
