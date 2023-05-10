/*
 * xiaomi_sdm439_read_eeprom_info_for_gc5035() - read map data into buffer
 * @e_ctrl:	eeprom control struct
 * @block:	block to be read
 *
 * This function iterates through blocks stored in block->map, reads each
 * region and concatenate them into the pre-allocated block->mapdata
 */
static int xiaomi_sdm439_read_eeprom_info_for_gc5035(struct msm_eeprom_ctrl_t *e_ctrl,
	struct msm_eeprom_memory_block_t *block)
{
	int rc = 0;
	int j;
	struct msm_eeprom_board_info *eb_info;
	uint8_t info_data[0x04] = {0};

	struct eeprom_map_t write_buf[25] = {
		/* reading init */
		{0x1, 0xfc, 1, 0x01, 1, 0},
		{0x1, 0xf4, 1, 0x40, 1, 0},
		{0x1, 0xf5, 1, 0xe9, 1, 0},
		{0x1, 0xf6, 1, 0x14, 1, 0},
		{0x1, 0xf8, 1, 0x49, 1, 0},
		{0x1, 0xf9, 1, 0x82, 1, 0},
		{0x1, 0xfa, 1, 0x10, 1, 0},
		{0x1, 0xfc, 1, 0x81, 1, 0},
		{0x1, 0xfe, 1, 0x00, 1, 0},
		{0x1, 0x36, 1, 0x01, 1, 0},
		{0x1, 0xd3, 1, 0x87, 1, 0},
		{0x1, 0x36, 1, 0x00, 1, 0},
		{0x1, 0xf7, 1, 0x01, 1, 0},
		{0x1, 0xfc, 1, 0x8f, 1, 0},
		{0x1, 0xfc, 1, 0x8f, 1, 0},
		{0x1, 0xfc, 1, 0x8e, 1, 0},
		{0x1, 0xfe, 1, 0x02, 1, 0},
		{0x1, 0x55, 1, 0x80, 1, 0},
		{0x1, 0x65, 1, 0x7e, 1, 0},
		{0x1, 0x66, 1, 0x03, 1, 0},
		/*page31 info&WB 30 */
		{0x1, 0x67, 1, 0xc0, 1, 0},
		{0x1, 0xf3, 1, 0x00, 1, 0},
		// page 31
		{0x1, 0xe0, 1, 0x1f, 1, 0},
		{0x1, 0x67, 1, 0xf0, 1, 0},
		{0x1, 0xf3, 1, 0x10, 1, 1},
	};

	if (!e_ctrl) {
		pr_err("%s e_ctrl is NULL", __func__);
		return -EINVAL;
	}

	eb_info = e_ctrl->eboard_info;

	// if not gc5035, exit
	if (eb_info->i2c_slaveaddr != 0x6e) {
		return 0;
	}

	// write some config to gc5035
	for (j = 0; j < 25; j++) {
		if (write_buf[j].valid_size) {
			e_ctrl->i2c_client.addr_type = 1;
			rc = e_ctrl->i2c_client.i2c_func_tbl->i2c_write(
				&(e_ctrl->i2c_client), write_buf[j].addr,
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
	e_ctrl->i2c_client.addr_type = 1;
	rc = e_ctrl->i2c_client.i2c_func_tbl->i2c_read_seq(
		&(e_ctrl->i2c_client), 0xC2,
		info_data, 0x04);
	if (rc < 0) {
		pr_err("%s: read failed\n", __func__);
		return rc;
	}

	//gc5035 module ID value for compatibility of pine
	//#define QTECH_GC5035_MID 0x06
	//#define OFILM_GC5035_MID 0x07
	//#define HOLITECH_GC5035_MID 0x08
	if (info_data[3] == 0x06)
		rc = strncmp(eb_info->eeprom_name, "pine_gc5035_qtech", strlen("pine_gc5035_qtech"));
	else if (info_data[3] == 0x07)
		rc = strncmp(eb_info->eeprom_name, "pine_gc5035_ofilm", strlen("pine_gc5035_ofilm"));
	else if (info_data[3] == 0x08)
		rc = strncmp(eb_info->eeprom_name, "pine_gc5035_holitech", strlen("pine_gc5035_holitech"));

	CDBG("lph info_data[3] %d, eeprom_name %s", info_data[3], eb_info->eeprom_name);

	// strncmp return value maybe greater than 0
	if (rc > 0)
		rc = 0 - rc;
	// if actual modele used matches the current eeprom node,
	// return 0 and continue execution
	return rc;
}
