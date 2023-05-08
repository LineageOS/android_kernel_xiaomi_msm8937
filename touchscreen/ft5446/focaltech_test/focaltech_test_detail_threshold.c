/************************************************************************
* Copyright (C) 2012-2018, Focaltech Systems (R)，All Rights Reserved.
* Copyright (C) 2021 XiaoMi, Inc.
*
* File Name: focaltech_test_detail_threshold.c
*
* Author: Focaltech Driver Team
*
* Created: 2016-08-01
*
* Abstract: Set Detail Threshold for all IC
*
************************************************************************/

#include "focaltech_test.h"

int xiaomi_sdm439_ft5446_malloc_struct_DetailThreshold(void)
{
	FTS_TEST_FUNC_ENTER();

	/*malloc mcap detailthreshold*/
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node = (unsigned char (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(unsigned char));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc = (unsigned char (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(unsigned char));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rx_linearity_test_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rx_linearity_test_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.tx_linearity_test_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.tx_linearity_test_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.noise_test_coefficient = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.noise_test_coefficient)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max = (int (*)[RX_NUM_MAX])xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL == xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max)
		goto ERR;

	/*malloc incell detailthreshold*/
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node =  xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min = xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max = xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_min = xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_max = xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min = xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min)
		goto ERR;
	xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max = xiaomi_sdm439_ft5446_fts_malloc(NUM_MAX * sizeof(int));
	if (NULL ==  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max)
		goto ERR;

	FTS_TEST_FUNC_EXIT();

	return 0;

ERR:
	FTS_TEST_ERROR("xiaomi_sdm439_ft5446_fts_malloc memory failed in function.");
	return -ENOMEM;
}

void xiaomi_sdm439_ft5446_free_struct_DetailThreshold(void)
{

	/*free mcap detailthreshold*/
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node = NULL;
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc = NULL;
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rx_linearity_test_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rx_linearity_test_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.tx_linearity_test_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.tx_linearity_test_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_max);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_min);
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.noise_test_coefficient) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.noise_test_coefficient);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.noise_test_coefficient = NULL;
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max = NULL;
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min = NULL;
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max = NULL;
	}
	if (NULL != xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max) {
		fts_free(xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max);
		xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max = NULL;
	}

	/*free incell detailthreshold*/
	if (NULL !=  xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node = NULL;
	}
	if (NULL !=   xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min = NULL;
	}
	if (NULL !=   xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max = NULL;
	}
	if (NULL !=   xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_min) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_min);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_min = NULL;
	}
	if (NULL !=   xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_max) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_max);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_max = NULL;
	}
	if (NULL !=   xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min = NULL;
	}
	if (NULL !=   xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max) {
		fts_free (xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max);
		xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max = NULL;
	}
}
void xiaomi_sdm439_ft5446_OnInit_InvalidNode(char *strIniFile)
{

	char str[MAX_PATH] = {0}, strTemp[MAX_PATH] = {0};
	int i = 0, j = 0;
	FTS_TEST_FUNC_ENTER();

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			snprintf(strTemp, PAGE_SIZE, "InvalidNode[%d][%d]", (i + 1), (j + 1));

			xiaomi_sdm439_ft5446_GetPrivateProfileString("INVALID_NODE", strTemp, "1", str, strIniFile);
			if (xiaomi_sdm439_ft5446_fts_atoi(str) == 0) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node[i][j] = 0;
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = 0;
				FTS_TEST_DBG("node (%d, %d)", (i + 1),  (j + 1));

			} else if (xiaomi_sdm439_ft5446_fts_atoi(str) == 2) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node[i][j] = 2;
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = 2;
			} else {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node[i][j] = 1;
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.invalid_node[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = 1;
			}
		}
	}

	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			snprintf(strTemp, PAGE_SIZE, "InvalidNodeS[%d][%d]", (i + 1), (j + 1));
			xiaomi_sdm439_ft5446_GetPrivateProfileString("INVALID_NODES", strTemp, "1", str, strIniFile);
			if (xiaomi_sdm439_ft5446_fts_atoi(str) == 0) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc[i][j] = 0;
			} else if (xiaomi_sdm439_ft5446_fts_atoi(str) == 2) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc[i][j] = 2;
			} else
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.invalid_node_sc[i][j] = 1;
		}

	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_RawDataTest(char *strIniFile)
{
	char str[128];
	char strTemp[MAX_PATH];
	char strValue[MAX_PATH];
	int MaxValue, MinValue, B_MaxValue, B_MinValue;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	/*RawData Test*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Max", "10000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_BFrame_Max", "5000", str, strIniFile);
	B_MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_max[i][j] = MaxValue;
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MaxValue;
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = B_MaxValue;
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Max_Tx%d", (i + 1));
		//FTS_TEST_DBG("%s ",  str);
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "111", strTemp, strIniFile);
		//FTS_TEST_DBG("xiaomi_sdm439_ft5446_GetPrivateProfileString = %d ",  dividerPos);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) Rawdata_Max_Tx%d = %d \n", (i+1), (k+1), (i+1),xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}

	}

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Min", "7000", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_BFrame_Min", "11000", str, strIniFile);
	B_MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_min[i][j] = MinValue;
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MinValue;
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_b_frame_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = B_MinValue;
		}
	}
	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Min_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) Rawdata_Min_Tx%d = %d \n", (i+1), (k+1), (i+1),xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	/*RawData Test Low*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Low_Max", "15000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Max_Low_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Low_Min", "3000", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_min[i][j] = MinValue;
		}
	}
	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Min_Low_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_low_min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	/*RawData Test High*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_High_Max", "15000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_max[i][j] = MaxValue;
		}
	}
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_High_Min", "3000", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_min[i][j] = MinValue;
		}
	}
	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Max_High_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}


	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Min_High_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rawdata_test_high_min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_SCapRawDataTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	/*SCapRawDataTest_OFF*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapRawDataTest_OFF_Min", "150", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapRawDataTest_OFF_Max", "1000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	/*Max*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapRawData_OFF_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	/*Min*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapRawData_OFF_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_off_min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	/*ON*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapRawDataTest_ON_Min", "150", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapRawDataTest_ON_Max", "1000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	/*Max*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapRawData_ON_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	/*Min*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapRawData_ON_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_rawdata_on_min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_SCapCbTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	/*SCapCbTest_ON*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapCbTest_ON_Min", "0", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapCbTest_ON_Max", "240", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	/*Max*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapCB_ON_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_max[i][k] = (xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	/*Min*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapCB_ON_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_on_min[i][k] = (xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	/*SCapCbTest_OFF*/
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapCbTest_OFF_Min", "0", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "SCapCbTest_OFF_Max", "240", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	/*Max*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapCB_OFF_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_max[i][k] = (xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	/*Min*/
	for (i = 0; i < 2; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 2; i++) {
		snprintf(str, PAGE_SIZE, "ScapCB_OFF_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.scap_cb_test_off_min[i][k] = (xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_PanelDifferTest(char *strIniFile)
{

	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue;
	int dividerPos = 0;
	int index = 0;
	int  k = 0, i = 0, j = 0;
	char str_tmp[128];

	FTS_TEST_FUNC_ENTER();
	////////////////////////////Panel_Differ Test
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "PanelDifferTest_Max", "1000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	for (i = 0; i < TX_NUM_MAX; i++) {
		for (j = 0; j < RX_NUM_MAX; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max[i][j] = MaxValue;
		}
	}

	for (i = 0; i < TX_NUM_MAX; i++) {
		snprintf(str, PAGE_SIZE, "Panel_Differ_Max_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}


	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "PanelDifferTest_Min", "150", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	for (i = 0; i < TX_NUM_MAX; i++) {
		for (j = 0; j < RX_NUM_MAX; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min[i][j] = MinValue;
		}
	}

	for (i = 0; i < TX_NUM_MAX; i++) {
		snprintf(str, PAGE_SIZE, "Panel_Differ_Min_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.panel_differ_test_min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();

}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_PanelDiffer_Uniformity_Test(char *strIniFile)
{

	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int dividerPos = 0;
	int index = 0;
	int  k = 0, i = 0, j = 0;
	char str_tmp[128];

	FTS_TEST_FUNC_ENTER();
	/*Panel_Differ_Uniformity Test Tx*/
	for (i = 0; i < TX_NUM_MAX; i++) {
		for (j = 0; j < RX_NUM_MAX; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max[i][j] = 0;
		}
	}

	for (i = 0; i < TX_NUM_MAX; i++) {
		snprintf(str, PAGE_SIZE, "SITOPanelDifferUniformity_Tx_Linearity_Base_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_TxLinearityTest_Max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	/*Panel_Differ_Uniformity Test Rx*/
	for (i = 0; i < TX_NUM_MAX; i++) {
		for (j = 0; j < RX_NUM_MAX; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max[i][j] = 0;
		}
	}

	for (i = 0; i < TX_NUM_MAX; i++) {
		snprintf(str, PAGE_SIZE, "SITOPanelDifferUniformity_Rx_Linearity_Base_Tx%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.PanelDiffer_Uniformity_RxLinearityTest_Max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_RxLinearityTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue = 0;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	////////////////////////////Rx_Linearity Test
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RxLinearityTest_Max", "50", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	//FTS_TEST_DBG("MaxValue = %d  ",  MaxValue);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_tx_num; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rx_linearity_test_max[i][j] = MaxValue;
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_tx_num; i++) {
		snprintf(str, PAGE_SIZE, "Rx_Linearity_Max_Tx%d", (i + 1));
		//FTS_TEST_DBG("%s ",  str);
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "111", strTemp, strIniFile);
		//FTS_TEST_DBG("xiaomi_sdm439_ft5446_GetPrivateProfileString = %d ",  dividerPos);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.rx_linearity_test_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}

	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_TxLinearityTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue = 0;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	////////////////////////////Tx_Linearity Test
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "TxLinearityTest_Max", "50", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	//FTS_TEST_DBG("MaxValue = %d  ",  MaxValue);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_tx_num; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.tx_linearity_test_max[i][j] = MaxValue;
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_tx_num; i++) {
		snprintf(str, PAGE_SIZE, "Tx_Linearity_Max_Tx%d", (i + 1));
		//FTS_TEST_DBG("%s ",  str);
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "111", strTemp, strIniFile);
		//FTS_TEST_DBG("xiaomi_sdm439_ft5446_GetPrivateProfileString = %d ",  dividerPos);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.tx_linearity_test_max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}

	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_ForceTouch_SCapRawDataTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	//////////////////OFF
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapRawDataTest_OFF_Min", "150", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapRawDataTest_OFF_Max", "1000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	///Max
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_OFF_Max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapRawData_OFF_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_OFF_Max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	////Min
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_OFF_Min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapRawData_OFF_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_OFF_Min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	//////////////////ON
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapRawDataTest_ON_Min", "150", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapRawDataTest_ON_Max", "1000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	//FTS_TEST_DBG("%d:%d\r", MinValue, MaxValue);
	//////读取阈值，若无特殊设置，则以Basic_Threshold替代

	///Max
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_ON_Max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapRawData_ON_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp); //FTS_TEST_DBG("%s:%s\r", str, strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_ON_Max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	////Min
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_ON_Min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapRawData_ON_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp); //FTS_TEST_DBG("%s:%s\r", str, strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapRawDataTest_ON_Min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}

void xiaomi_sdm439_ft5446_OnInit_DThreshold_ForceTouch_SCapCbTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	//////////////////ON
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapCbTest_ON_Min", "0", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapCbTest_ON_Max", "240", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	//FTS_TEST_DBG("%d:%d\r", MinValue, MaxValue);
	//////读取阈值，若无特殊设置，则以Basic_Threshold替代

	///Max
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_ON_Max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapCB_ON_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp); //FTS_TEST_DBG("%s:%s\r", str, strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_ON_Max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	////Min
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_ON_Min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapCB_ON_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp); //FTS_TEST_DBG("%s:%s\r", str, strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		FTS_TEST_DBG("%s\r", strTemp);
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_ON_Min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	//////////////////OFF
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapCbTest_OFF_Min", "0", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ForceTouch_SCapCbTest_OFF_Max", "240", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);
	///Max
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_OFF_Max[i][j] = MaxValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapCB_OFF_Max_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_OFF_Max[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	////Min
	for (i = 0; i < 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.used_max_rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_OFF_Min[i][j] = MinValue;
		}
	}
	for (i = 0; i < 1; i++) {
		snprintf(str, PAGE_SIZE, "ForceTouch_ScapCB_OFF_Min_%d", (i + 1));
		dividerPos = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0x00, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.mcap_detail_thr.ForceTouch_SCapCbTest_OFF_Min[i][k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}
void xiaomi_sdm439_ft5446_OnInit_DThreshold_CBTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue, MaxValue_Vkey, MinValue_Vkey;
	int ChannelNumTest_ChannelXNum, ChannelNumTest_ChannelYNum;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "CBTest_Max", "100", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "CBTest_Max_Vkey", "100", str, strIniFile);
	MaxValue_Vkey = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ChannelNumTest_ChannelX", "15", str, strIniFile);
	ChannelNumTest_ChannelXNum = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ChannelNumTest_ChannelY", "24", str, strIniFile);
	ChannelNumTest_ChannelYNum = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MaxValue;
		}

		if (i == ChannelNumTest_ChannelXNum) {
			for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MaxValue_Vkey;
			}
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "CB_Max_Tx%d", (i + 1));
		//FTS_TEST_DBG("%s ",  str);
		dividerPos  = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		// FTS_TEST_DBG("i = %d, dividerPos = %d \n", i+1, dividerPos);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) CB_Max_Tx%d = %d cb_test_max[%d] = %d\n", (i+1), (k+1), (i+1),xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k], i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k, xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}



	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "CBTest_Min", "3", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "CBTest_Min_Vkey", "3", str, strIniFile);
	MinValue_Vkey = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MinValue;
		}

		if (i == ChannelNumTest_ChannelXNum) {
			for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MinValue_Vkey;
			}
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "CB_Min_Tx%d", (i + 1));
		dividerPos  =  xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		//FTS_TEST_DBG("i = %d, dividerPos = %d \n", i+1, dividerPos);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) CB_Min_Tx%d = %d cb_test_min[%d] = %d \n", (i+1), (k+1), (i+1),xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k], i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k, xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i*xiaomi_sdm439_ft5446_test_data.screen_param.rx_num+k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}


void xiaomi_sdm439_ft5446_OnInit_DThreshold_AllButtonCBTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "CBTest_Max", "100", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);


	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MaxValue;
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "CB_Max_Tx%d", (i + 1));
		//FTS_TEST_DBG("%s ",  str);
		dividerPos  = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		// FTS_TEST_DBG("i = %d, dividerPos = %d \n", i+1, dividerPos);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) value = %d \n", (i+1), (k+1), xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_max[i][k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}



	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "CBTest_Min", "3", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MinValue;
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "CB_Min_Tx%d", (i + 1));
		dividerPos  =  xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		//FTS_TEST_DBG("i = %d, dividerPos = %d \n", i+1, dividerPos);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) value = %d \n", (i+1), (k+1), xiaomi_sdm439_ft5446_test_data.incell_detail_thr.cb_test_min[i*dividerPos+k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	FTS_TEST_FUNC_EXIT();
}


void xiaomi_sdm439_ft5446_OnThreshold_VkAndVaRawDataSeparateTest(char *strIniFile)
{
	char str[128], strTemp[MAX_PATH], strValue[MAX_PATH];
	int MaxValue, MinValue, MaxValue_Vkey, MinValue_Vkey;
	int ChannelNumTest_ChannelXNum, ChannelNumTest_ChannelYNum;
	int   dividerPos = 0;
	char str_tmp[128];
	int index = 0;
	int  k = 0, i = 0, j = 0;

	FTS_TEST_FUNC_ENTER();

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Max", "11000", str, strIniFile);
	MaxValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Max_VKey", "11000", str, strIniFile);
	MaxValue_Vkey = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ChannelNumTest_ChannelX", "15", str, strIniFile);
	ChannelNumTest_ChannelXNum = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "ChannelNumTest_ChannelY", "24", str, strIniFile);
	ChannelNumTest_ChannelYNum = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MaxValue;
		}

		if (i == ChannelNumTest_ChannelXNum) {
			for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MaxValue_Vkey;
			}
		}
	}


	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Max_Tx%d", (i + 1));
		dividerPos  = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		//FTS_TEST_DBG("i = %d, dividerPos = %d \n", i+1, dividerPos);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//  FTS_TEST_DBG("node (%d, %d) value = %d \n", (i+1), (k+1), xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_max[i][k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Min", "5000", str, strIniFile);
	MinValue = xiaomi_sdm439_ft5446_fts_atoi(str);

	xiaomi_sdm439_ft5446_GetPrivateProfileString("Basic_Threshold", "RawDataTest_Min_VKey", "5000", str, strIniFile);
	MinValue_Vkey = xiaomi_sdm439_ft5446_fts_atoi(str);

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
			xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MinValue;
		}

		if (i == ChannelNumTest_ChannelXNum) {
			for (j = 0; j < xiaomi_sdm439_ft5446_test_data.screen_param.rx_num; j++) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + j] = MinValue_Vkey;
			}
		}
	}

	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.screen_param.tx_num + 1; i++) {
		snprintf(str, PAGE_SIZE, "RawData_Min_Tx%d", (i + 1));
		dividerPos  = xiaomi_sdm439_ft5446_GetPrivateProfileString("SpecialSet", str, "NULL", strTemp, strIniFile);
		snprintf(strValue, PAGE_SIZE, "%s", strTemp);
		//FTS_TEST_DBG("i = %d, dividerPos = %d \n", i+1, dividerPos);
		if (0 == dividerPos)
			continue;
		index = 0;
		k = 0;
		memset(str_tmp, 0, sizeof(str_tmp));
		for (j = 0; j < dividerPos; j++) {
			if (',' == strValue[j]) {
				xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i * xiaomi_sdm439_ft5446_test_data.screen_param.rx_num + k] = (short)(xiaomi_sdm439_ft5446_fts_atoi(str_tmp));
				//FTS_TEST_DBG("node (%d, %d) value = %d \n", (i+1), (k+1), xiaomi_sdm439_ft5446_test_data.incell_detail_thr.rawdata_test_min[i][k]);
				index = 0;
				memset(str_tmp, 0x00, sizeof(str_tmp));
				k++;
			} else {
				if (' ' == strValue[j])
					continue;
				str_tmp[index] = strValue[j];
				index++;
			}
		}
	}
	FTS_TEST_FUNC_EXIT();
}

