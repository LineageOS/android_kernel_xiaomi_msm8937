/*
 *
 * FocalTech fts TouchScreen driver.
 *
 * Copyright (c) 2010-2017, Focaltech Ltd. All rights reserved.
 * Copyright (C) 2018 XiaoMi, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "../focaltech_core.h"
#include "../focaltech_flash.h"
#include <linux/timer.h>

#define FTS_GET_UPGRADE_TIME                    0


#define FTS_DEBUG_UPGRADE(fmt, args...) do {\
									printk(KERN_ERR "[FTS][UPGRADE]:##############################################################################\n");\
									printk(KERN_ERR "[FTS][UPGRADE]: "fmt"\n", ##args);\
									printk(KERN_ERR "[FTS][UPGRADE]:##############################################################################\n");\
									} while(0)\

#if (FTS_UPGRADE_STRESS_TEST)
static int ft5435_fts_ctpm_auto_upgrade_pingpong(struct i2c_client *client)
{
	u8 uc_tp_fm_ver;
	int i_ret = 0;
	u8 uc_upgrade_times = 0;

	FTS_FUNC_ENTER();

	FTS_INFO("[UPGRADE]: pingpong test mode, need upgrade!!");
	do {
		uc_upgrade_times++;

		i_ret = ft5435_fts_ctpm_fw_upgrade(client);

		if (i_ret == 0) {
			ft5435_ft5435_fts_i2c_read_reg(client, FTS_REG_FW_VER, &uc_tp_fm_ver);
			FTS_DEBUG("[UPGRADE]: upgrade to new version 0x%x", uc_tp_fm_ver);
		} else /* upgrade fail */ {
			FTS_INFO("[UPGRADE]: upgrade fail, reset now!!");
			ft5435_fts_ctpm_rom_or_pram_reset(client);
		}
	}
	while ((i_ret != 0) && (uc_upgrade_times < 2));

	FTS_FUNC_EXIT();
	return i_ret;
}

void fts_ctpm_display_upgrade_time(bool start_time)
{
#if FTS_GET_UPGRADE_TIME
	static struct timeval tpend;
	static struct timeval tpstart;
	static int timeuse;

	if (start_time) {
		do_gettimeofday(&tpstart);
	} else {
		do_gettimeofday(&tpend);
		timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+ tpend.tv_usec-tpstart.tv_usec;
		timeuse/=1000000;
		FTS_DEBUG( "[UPGRADE]: upgrade success : Use time: %d Seconds!!", timeuse);
	}
#endif
}

int ft5435_fts_ctpm_auto_upgrade(struct i2c_client *client)
{
	int i_ret = 0;
	static int uc_ErrorTimes = 0;
	static int uc_UpgradeTimes = 0;


	device_init_wakeup(&client->dev, 1);
	pm_stay_awake(&client->dev);

	ft5435_g_fw_file = CTPM_FW;
	ft5435_g_fw_len = ft5435_fts_getsize(FW_SIZE);
	FTS_DEBUG("[UPGRADE]FW FILE:CTPM_FW, SIZE:%x", ft5435_g_fw_len);

	do {
		uc_UpgradeTimes++;

		FTS_DEBUG_UPGRADE("start to upgrade %d times !!", uc_UpgradeTimes);

		fts_ctpm_display_upgrade_time(true);

		i_ret = ft5435_fts_ctpm_auto_upgrade_pingpong(client);
		if (i_ret == 0) {
			fts_ctpm_display_upgrade_time(false);
		} else {
			uc_ErrorTimes++;
		}

		FTS_DEBUG_UPGRADE("upgrade %d times, error %d times!!", uc_UpgradeTimes, uc_ErrorTimes);
	}
	while (uc_UpgradeTimes < (FTS_UPGRADE_TEST_NUMBER));

	pm_relax(&client->dev);
	device_init_wakeup(&client->dev, 0);

	return 0;
}
#endif

