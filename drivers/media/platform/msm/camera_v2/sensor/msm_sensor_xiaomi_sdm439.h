static int xiaomi_sdm439_read_otp_info_for_gc02m1(struct msm_sensor_ctrl_t *e_ctrl, const char *sensor_name)
{
	int rc = 0;
	int j;
	int rccode = 0;
	uint8_t info_data[0x04] = {0};

	struct eeprom_map_t write_buf[21] = {
		/* reading init */
			{1, 0xfe, 1, 0x00, 1, 0 },
			{1, 0xfc, 1, 0x01, 1, 0 },
			{1, 0xf4, 1, 0x41, 1, 0 },
			{1, 0xf5, 1, 0xc0, 1, 0 },
			{1, 0xf6, 1, 0x44, 1, 0 },
			{1, 0xf8, 1, 0x38, 1, 0 },
			{1, 0xf9, 1, 0x82, 1, 0 },
			{1, 0xfa, 1, 0x00, 1, 0 },
			{1, 0xfd, 1, 0x80, 1, 0 },
			{1, 0xfc, 1, 0x81, 1, 0 },
			{1, 0xf7, 1, 0x01, 1, 0 },
			{1, 0xfc, 1, 0x80, 1, 0 },
			{1, 0xfc, 1, 0x80, 1, 0 },
			{1, 0xfc, 1, 0x80, 1, 0 },
			{1, 0xfc, 1, 0x8e, 1, 0 },
			{1, 0xf3, 1, 0x30, 1, 0 },
			{1, 0xfe, 1, 0x02, 1, 0 },
			{1, 0x17, 1, 0x10, 1, 0 },
			{1, 0xf3, 1, 0x34, 1, 0 },
			{1, 0xf7, 1, 0x01, 1, 0 },
			{1, 0xfe, 1, 0x00, 1, 0 },
	};

	struct eeprom_map_t write_buf1[2] = {
		/* reading init */
			{1, 0xf7, 1, 0x00, 1, 0 },
			{1, 0xf9, 1, 0x83, 1, 0 },

	};

	if (!e_ctrl) {
		pr_err("%s e_ctrl is NULL", __func__);
		return -EINVAL;
	}

	if (!(strnstr(sensor_name, "gc02m1_sunny", strlen(sensor_name)) || strnstr(sensor_name, "gc02m1b_sunny", strlen(sensor_name)))) {
		CDBG("sensor_name %s", sensor_name);
		return 0;
	}

	// write some config to gc5035
	for (j = 0; j < 19; j++) {
		if (write_buf[j].valid_size) {
			e_ctrl->sensor_i2c_client->addr_type = 1;
			rc = e_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				e_ctrl->sensor_i2c_client, write_buf[j].addr,
				write_buf[j].data, write_buf[j].data_t);
				msleep(write_buf[j].delay);
			if (rc < 0) {
				pr_err("%s: page write failed\n", __func__);
				return rc;
			}
		}
	}

	// read module info
	//qcom,mem39  = <0x1E 0xC2 1 0x0 1 0>;
	e_ctrl->sensor_i2c_client->addr_type = 1;
	rc = e_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read_seq(
		e_ctrl->sensor_i2c_client, 0x19,
		info_data, 0x01);
	if (rc < 0) {
		pr_err("%s: read failed\n", __func__);
		return rc;
	}

	for (j = 19; j < 21; j++) {
		if (write_buf[j].valid_size) {
			e_ctrl->sensor_i2c_client->addr_type = 1;
			rc = e_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				e_ctrl->sensor_i2c_client, write_buf[j].addr,
				write_buf[j].data, write_buf[j].data_t);
				msleep(write_buf[j].delay);
			pr_err("lucifer write 0x%x:%d", write_buf[j].addr, write_buf[j].data);
			if (rc < 0) {
				pr_err("%s: page write failed\n", __func__);
				return rc;
			}
		}
	}

	if (0x04 == (info_data[0] & 0x04)) {
		if (!strncmp(sensor_name, "olive_gc02m1b_sunny", strlen("olive_gc02m1b_sunny"))) {
			rc = 0;
		} else {
			rc = -1;
		}
	} else {
		if (strnstr(sensor_name, "gc02m1_sunny", 30)) {
			rc = 0;
		} else {
			rc = -1;
		}
	}
	pr_err("lucifer info_data[0] 0x%x, sensor_name %s", info_data[0], sensor_name);
	// if actual modele used matches the current eeprom node,
	// return 0 and continue execution
	for (j = 0; j < 2; j++) {
		if (write_buf1[j].valid_size) {
			e_ctrl->sensor_i2c_client->addr_type = 1;
			rccode = e_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				e_ctrl->sensor_i2c_client, write_buf1[j].addr,
				write_buf1[j].data, write_buf1[j].data_t);
				msleep(write_buf1[j].delay);
			if (rccode < 0) {
				pr_err("%s: page write failed\n", __func__);
				return rccode;
			}
		}
	}
	return rc;
}

static int xiaomi_sdm439_read_otp_after_write_for_gc02m1(struct msm_sensor_ctrl_t *e_ctrl, const char *sensor_name)
{
	int rc = 0;
	int j = 0;
	struct eeprom_map_t write_buf1[9] = {
	   /* power dowm after write*/
			{1, 0xfe, 1, 0x00, 1, 0 },
			{1, 0x3e, 1, 0x00, 1, 0 },
			{1, 0xfc, 1, 0x88, 1, 0 },
			{1, 0xfe, 1, 0x10, 1, 0 },
			{1, 0xfe, 1, 0x00, 1, 0 },
			{1, 0xfc, 1, 0x8e, 1, 0 },
			{1, 0xfc, 1, 0x01, 1, 0 },
			{1, 0xf7, 1, 0x00, 1, 0 },
			{1, 0xf9, 1, 0x83, 1, 0 },

	};
	if (!e_ctrl) {
		pr_err("%s e_ctrl is NULL", __func__);
		return -EINVAL;
	}

	if (!(strnstr(sensor_name, "olive_gc02m1b_sunny", strlen("olive_gc02m1b_sunny")) || strnstr(sensor_name, "olive_gc02m1b_sunny", strlen("olive_gc02m1b_sunny"))
	|| strnstr(sensor_name, "olivewood_gc02m1b_sunny", strlen("olivewood_gc02m1b_sunny"))
		|| strnstr(sensor_name, "olivewood_gc02m1_sunny", strlen("olivewood_gc02m1_sunny")))) {
			return 0;
	}


	for (j = 0; j < 9; j++) {
		if (write_buf1[j].valid_size) {
			e_ctrl->sensor_i2c_client->addr_type = 1;
			rc = e_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				e_ctrl->sensor_i2c_client, write_buf1[j].addr,
				write_buf1[j].data, write_buf1[j].data_t);
				msleep(write_buf1[j].delay);
			if (rc < 0) {
				pr_err("%s: page write failed\n", __func__);
				return rc;
			}
		}
	}
	return rc;
}
