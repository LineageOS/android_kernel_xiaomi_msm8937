/************************************************************************
* Copyright (C) 2012-2018, Focaltech Systems (R)£¬All Rights Reserved.
* Copyright (C) 2021 XiaoMi, Inc.
*
* File Name: focaltech_test_ini.c
*
* Author: Focaltech Driver Team
*
* Created: 2016-08-01
*
* Abstract: parsing function of INI file
*
************************************************************************/
#include "focaltech_test.h"

/*****************************************************************************
* Private constant and macro definitions using #define
*****************************************************************************/

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
/* '[' ']':Section Symbol-Can be defined according to the special need to change */
const char xiaomi_sdm439_ft5446_CFG_SSL = '[';
const char xiaomi_sdm439_ft5446_CFG_SSR = ']';
const char xiaomi_sdm439_ft5446_CFG_NIS = ':';  /* Separator between name and index */
const char xiaomi_sdm439_ft5446_CFG_NTS = '#';  /* annotator */
const char xiaomi_sdm439_ft5446_CFG_EQS = '=';  /* The equal sign */

/*****************************************************************************
* Static function prototypes
*****************************************************************************/
/* Works only for digits and letters, but small and fast */
#define TOLOWER(x) ((x) | 0x20)
int xiaomi_sdm439_ft5446_fts_strncmp(const char *cs, const char *ct, size_t count)
{
	u8 c1 = 0, c2 = 0;

	while (count) {
		c1 = TOLOWER(*cs++);
		c2 = TOLOWER(*ct++);
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
		count--;
	}

	return 0;
}

/*************************************************************
Function:  Get the value of key
Input: char * filedata; char * section; char * key
Output: char * value¡¡key
Return: 0       SUCCESS
		-1      can not find section
		-2      can not find key
		-10     File open failed
		-12     File read  failed
		-14     File format error
		-22     Out of buffer size
Note:
*************************************************************/
int xiaomi_sdm439_ft5446_ini_get_key(char *filedata, char *section, char *key, char *value)
{
	int i = 0;
	int ret = -2;
	for (i = 0; i < xiaomi_sdm439_ft5446_test_data.ini_keyword_num; i++) {
		if (xiaomi_sdm439_ft5446_fts_strncmp(section, xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name,
						xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name_len) != 0)
			continue;
		//FTS_TEST_DBG("Section Name:%s, Len:%d\n",  xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name, xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name_len);
		if (strlen(key) == xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name_len) {
			if (xiaomi_sdm439_ft5446_fts_strncmp(key, xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name,  xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name_len) == 0)
				//xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name_len) == 0)
			{
				memcpy(value, xiaomi_sdm439_ft5446_test_data.ini_data[i].key_value, xiaomi_sdm439_ft5446_test_data.ini_data[i].key_value_len);
				ret = 0;
				break;
			}
		}
	}

	return ret;
}

/*************************************************************
Function: Remove empty character on the right side of the string
Input:  char * buf --String pointer
Output:
Return: String pointer
Note:
*************************************************************/
char *xiaomi_sdm439_ft5446_ini_str_trim_r(char *buf)
{
	int len, i;
	char tmp[MAX_CFG_BUF_LINE_LEN] = { 0 };

	memset(tmp, 0, sizeof(tmp));
	len = strlen(buf);
	if (len > MAX_CFG_BUF_LINE_LEN) {
		FTS_TEST_SAVE_ERR("%s:buf len(%d) fail\n", __func__, len);
		return NULL;
	}

	memset(tmp, 0x00, len);
	for (i = 0; i < len; i++) {
		if (buf[i] != ' ')
			break;
	}
	if (i < len) {
		strlcpy(tmp, (buf + i), (len - i) + 1);
	}
	strlcpy(buf, tmp, len + 1);

	return buf;
}

/*************************************************************
Function: Remove empty character on the left side of the string
Input: char * buf --String pointer
Output:
Return: String pointer
Note:
*************************************************************/
char *xiaomi_sdm439_ft5446_ini_str_trim_l(char *buf)
{
	int len, i;
	char tmp[MAX_CFG_BUF_LINE_LEN] = { 0 };

	memset(tmp, 0, sizeof(tmp));
	len = strlen(buf);
	if (len > MAX_CFG_BUF_LINE_LEN) {
		FTS_TEST_SAVE_ERR("%s:buf len(%d) fail\n", __func__, len);
		return NULL;
	}

	memset(tmp, 0x00, len);

	for (i = 0; i < len; i++) {
		if (buf[len - i - 1] != ' ')
			break;
	}
	if (i < len) {
		strlcpy(tmp, buf, (len - i) + 1);
	}
	strlcpy(buf, tmp, len + 1);

	return buf;
}

/*************************************************************
Function: Read a line from file
Input:  FILE *fp; int maxlen-- Maximum length of buffer
Output: char *buffer --  A string
Return: >0      Actual read length
		-1      End of file
		-2      Error reading file
Note:
*************************************************************/
static int ini_file_get_line(char *filedata, char *buffer, int maxlen)
{
	int i = 0;
	int j = 0;
	int iRetNum = -1;
	char ch1 = '\0';

	for (i = 0, j = 0; i < maxlen; j++) {
		ch1 = filedata[j];
		iRetNum = j + 1;
		if (ch1 == '\n' || ch1 == '\r') { //line end
			ch1 = filedata[j + 1];
			if (ch1 == '\n' || ch1 == '\r') {
				iRetNum++;
			}

			break; // line breaks
		} else if (ch1 == 0x00) {
			iRetNum = -1;
			break; //file end
		} else {
			buffer[i++] = ch1;    /* ignore carriage return */
		}
	}
	buffer[i] = '\0';

	return iRetNum;
}

int xiaomi_sdm439_ft5446_isspace(int x)
{
	if (x == ' ' || x == '\t' || x == '\n' || x == '\f' || x == '\b' || x == '\r')
		return 1;
	else
		return 0;
}

int xiaomi_sdm439_ft5446_isdigit(int x)
{
	if (x <= '9' && x >= '0')
		return 1;
	else
		return 0;
}

static long fts_atol(char *nptr)
{
	int c; /* current char */
	long total; /* current total */
	int sign; /* if ''-'', then negative, otherwise positive */
	/* skip whitespace */
	while (xiaomi_sdm439_ft5446_isspace((int)(unsigned char)*nptr))
		++nptr;
	c = (int)(unsigned char) *nptr++;
	sign = c; /* save sign indication */
	if (c == '-' || c == '+')
		c = (int)(unsigned char) *nptr++; /* skip sign */
	total = 0;
	while (xiaomi_sdm439_ft5446_isdigit(c)) {
		total = 10 * total + (c - '0'); /* accumulate digit */
		c = (int)(unsigned char) *nptr++; /* get next char */
	}
	if (sign == '-')
		return -total;
	else
		return total; /* return result, negated if necessary */
}

int xiaomi_sdm439_ft5446_fts_atoi(char *nptr)
{
	return (int)fts_atol(nptr);
}

int xiaomi_sdm439_ft5446_init_key_data(void)
{
	int i = 0;

	FTS_TEST_FUNC_ENTER();

	xiaomi_sdm439_ft5446_test_data.ini_keyword_num = 0;

	for (i = 0; i < MAX_KEYWORD_NUM; i++) {
		memset(xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name, 0, MAX_KEYWORD_NAME_LEN);
		memset(xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name, 0, MAX_KEYWORD_NAME_LEN);
		memset(xiaomi_sdm439_ft5446_test_data.ini_data[i].key_value, 0, MAX_KEYWORD_VALUE_LEN);
		xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name_len = 0;
		xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name_len = 0;
		xiaomi_sdm439_ft5446_test_data.ini_data[i].key_value_len = 0;
	}

	FTS_TEST_FUNC_EXIT();
	return 1;
}

int xiaomi_sdm439_ft5446_print_key_data(void)
{
	int i = 0;

	FTS_TEST_DBG("xiaomi_sdm439_ft5446_test_data.ini_keyword_num = %d",  xiaomi_sdm439_ft5446_test_data.ini_keyword_num);
	for (i = 0; i < MAX_KEYWORD_NUM; i++) {

		FTS_TEST_DBG("section_name_%d:%s, key_name_%d:%s\n,key_value_%d:%s",
					 i, xiaomi_sdm439_ft5446_test_data.ini_data[i].section_name,
					 i, xiaomi_sdm439_ft5446_test_data.ini_data[i].key_name,
					 i, xiaomi_sdm439_ft5446_test_data.ini_data[i].key_value
					);
	}

	return 0;
}

/*************************************************************
Function: Read all the parameters and values to the structure.
Return: Returns the number of key. If you go wrong, return a negative number.
		-10         File open failed
		-12         File read  failed
		-14         File format error
Note:
*************************************************************/
int xiaomi_sdm439_ft5446_ini_get_key_data(char *filedata)
{
	char buf1[MAX_CFG_BUF_LINE_LEN + 1] = {0};
	int n = 0;
	int ret = 0;
	int dataoff = 0;
	int iEqualSign = 0;
	int i = 0;
	char tmsection_name[MAX_CFG_BUF_LINE_LEN + 1] = {0};

	FTS_TEST_FUNC_ENTER();
	ret = xiaomi_sdm439_ft5446_init_key_data();
	if (ret < 0) {
		FTS_TEST_ERROR("init key data failed");
		return -EIO;
	}

	xiaomi_sdm439_ft5446_test_data.ini_keyword_num = 0;
	while (1) { /*find section */
		ret = CFG_ERR_READ_FILE;
		n = ini_file_get_line(filedata + dataoff, buf1, MAX_CFG_BUF_LINE_LEN);
		if (n < -1)
			goto cfg_scts_end;
		if (n < 0)
			break;/* file end */
		if (n >= MAX_CFG_BUF_LINE_LEN) {
			FTS_TEST_ERROR("Error Length:%d\n",  n);
			goto cfg_scts_end;
		}
		dataoff += n;
		n = strlen(xiaomi_sdm439_ft5446_ini_str_trim_l(xiaomi_sdm439_ft5446_ini_str_trim_r(buf1)));
		if (n == 0 || buf1[0] == xiaomi_sdm439_ft5446_CFG_NTS)
			continue;       /* A blank line or a comment line */
		ret = CFG_ERR_FILE_FORMAT;
		//get section name
		if (n > 2 && ((buf1[0] == xiaomi_sdm439_ft5446_CFG_SSL && buf1[n - 1] != xiaomi_sdm439_ft5446_CFG_SSR))) {
			FTS_TEST_ERROR("Bad Section:%s\n",  buf1);
			goto cfg_scts_end;//bad section
		}

		if (buf1[0] == xiaomi_sdm439_ft5446_CFG_SSL) {
			xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].section_name_len = n - 2;
			if (MAX_KEYWORD_NAME_LEN < xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].section_name_len) {
				ret = CFG_ERR_OUT_OF_LEN;
				FTS_TEST_ERROR("MAX_KEYWORD_NAME_LEN: CFG_ERR_OUT_OF_LEN\n");
				goto cfg_scts_end;
			}
			buf1[n - 1] = 0x00;
			strlcpy((char *)tmsection_name, buf1 + 1, MAX_CFG_BUF_LINE_LEN + 1);

			continue;
		}
		//get section name end
		strlcpy(xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].section_name, tmsection_name, MAX_KEYWORD_NAME_LEN);
		xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].section_name_len = strlen(tmsection_name);

		iEqualSign = 0;
		for (i = 0; i < n; i++) {
			if (buf1[i] == xiaomi_sdm439_ft5446_CFG_EQS) {
				iEqualSign = i;
				break;
			}
		}
		if (0 == iEqualSign)
			continue;
		/* before equal sign is assigned to the key name*/
		xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_name_len = iEqualSign;
		if (MAX_KEYWORD_NAME_LEN < xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_name_len) {
			ret = CFG_ERR_OUT_OF_LEN;
			FTS_TEST_ERROR("MAX_KEYWORD_NAME_LEN: CFG_ERR_OUT_OF_LEN\n");
			goto cfg_scts_end;
		}
		memcpy(xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_name,
			   buf1, xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_name_len);

		/* After equal sign is assigned to the key value*/
		xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_value_len = n - iEqualSign - 1;
		if (MAX_KEYWORD_VALUE_LEN < xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_value_len) {
			ret = CFG_ERR_OUT_OF_LEN;
			FTS_TEST_ERROR("MAX_KEYWORD_VALUE_LEN: CFG_ERR_OUT_OF_LEN\n");
			goto cfg_scts_end;
		}
		memcpy(xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_value,
			   buf1 + iEqualSign + 1, xiaomi_sdm439_ft5446_test_data.ini_data[xiaomi_sdm439_ft5446_test_data.ini_keyword_num].key_value_len);

		ret = xiaomi_sdm439_ft5446_test_data.ini_keyword_num;
		xiaomi_sdm439_ft5446_test_data.ini_keyword_num++;   /*Parameter number accumulation*/
		if (MAX_KEYWORD_NUM < xiaomi_sdm439_ft5446_test_data.ini_keyword_num) {
			ret = CFG_ERR_TOO_MANY_KEY_NUM;
			FTS_TEST_ERROR("MAX_KEYWORD_NUM: CFG_ERR_TOO_MANY_KEY_NUM\n");
			goto cfg_scts_end;
		}
	}

	FTS_TEST_FUNC_EXIT();

	return 0;

cfg_scts_end:

	FTS_TEST_FUNC_EXIT();
	return ret;
}

int xiaomi_sdm439_ft5446_GetPrivateProfileString(char *section, char *ItemName, char *defaultvalue, char *returnValue, char *IniFile)
{
	char value[MAX_KEYWORD_VALUE_LEN] = { 0 };
	int len = 0;

	if (NULL == returnValue) {
		FTS_TEST_DBG("return Value==NULL");
		return 0;
	}
	if (xiaomi_sdm439_ft5446_ini_get_key(IniFile, section, ItemName, value) < 0) {
		if (NULL != defaultvalue)
			memcpy(value, defaultvalue, strlen(defaultvalue));
		snprintf(returnValue, PAGE_SIZE, "%s", value);
		return 0;
	} else {
		len = snprintf(returnValue, PAGE_SIZE, "%s", value);
	}

	return len;
}

int xiaomi_sdm439_ft5446_fts_test_get_ini_size(char *config_name)
{
	struct file *pfile = NULL;
	struct filename *filename;
	struct inode *inode = NULL;
	off_t fsize = 0;
	char filepath[128];

	FTS_TEST_FUNC_ENTER();

	memset(filepath, 0, sizeof(filepath));
	snprintf(filepath, PAGE_SIZE, "%s%s", FTS_INI_FILE_PATH, config_name);
	filename = getname_kernel(filepath);

	if (NULL == pfile)
		pfile = file_open_name(filename, O_RDONLY, 0);
	if (IS_ERR(pfile)) {
		FTS_TEST_ERROR("error occured while opening file %s.",  filepath);
		return -EIO;
	}

#if 1
	inode = pfile->f_inode;
#else
	/* reserved for linux earlier verion */
	inode = pfile->f_dentry->d_inode;
#endif
	fsize = inode->i_size;
	filp_close(pfile, NULL);

	FTS_TEST_FUNC_ENTER();

	return fsize;
}

//Read configuration to memory
int xiaomi_sdm439_ft5446_fts_test_read_ini_data(char *config_name, char *config_buf)
{
	struct file *pfile = NULL;
	struct filename *filename;
	struct inode *inode = NULL;
	off_t fsize = 0;
	char filepath[128];
	loff_t pos = 0;
	mm_segment_t old_fs;

	FTS_TEST_FUNC_ENTER();

	memset(filepath, 0, sizeof(filepath));
	snprintf(filepath, PAGE_SIZE, "%s%s", FTS_INI_FILE_PATH, config_name);
	filename = getname_kernel(filepath);
	if (NULL == pfile) {
		pfile = file_open_name(filename, O_RDONLY, 0);
	}
	if (IS_ERR(pfile)) {
		FTS_TEST_ERROR("error occured while opening file %s.",  filepath);
		return -EIO;
	}

#if 1
	inode = pfile->f_inode;
#else
	/* reserved for linux earlier verion */
	inode = pfile->f_dentry->d_inode;
#endif
	fsize = inode->i_size;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	pos = 0;
	vfs_read(pfile, config_buf, fsize, &pos);
	filp_close(pfile, NULL);
	set_fs(old_fs);

	FTS_TEST_FUNC_EXIT();
	return 0;
}

int xiaomi_sdm439_ft5446_init_interface(char *ini)
{
	char str[MAX_KEYWORD_VALUE_LEN] = { 0 };
	u32 ic_type = 0xFF;

	FTS_TEST_FUNC_ENTER();

	/* IC type */
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Interface", "IC_Type", "FT5X36", str, ini);
	ic_type = xiaomi_sdm439_ft5446_fts_ic_table_get_ic_code_from_ic_name(str);
	if (0 == ic_type) {
		FTS_TEST_ERROR("get ic code fail");
		return -EINVAL;
	}
	xiaomi_sdm439_ft5446_test_data.screen_param.selected_ic = ic_type;
	/*Get IC Name*/
	snprintf(xiaomi_sdm439_ft5446_test_data.ini_ic_name, PAGE_SIZE, "%s", str);
	FTS_TEST_INFO("IC Name:%s IC Code:0x%02x. ", xiaomi_sdm439_ft5446_test_data.ini_ic_name, xiaomi_sdm439_ft5446_test_data.screen_param.selected_ic);

	/* Normalize Type */
	xiaomi_sdm439_ft5446_GetPrivateProfileString("Interface", "Normalize_Type", 0, str, ini);
	xiaomi_sdm439_ft5446_test_data.screen_param.normalize = xiaomi_sdm439_ft5446_fts_atoi(str);

	FTS_TEST_FUNC_EXIT();
	return 0;
}

/************************************************************************
* Name: xiaomi_sdm439_ft5446_set_param_data
* Brief:  load Config. Set IC series, init test items, init basic threshold, int detailThreshold, and set order of test items
* Input: TestParamData, from ini file.
* Output: none
* Return: 0. No sense, just according to the old format.
***********************************************************************/
int xiaomi_sdm439_ft5446_set_param_data(char *test_param)
{
	int ret = 0;

	FTS_TEST_FUNC_ENTER();

	xiaomi_sdm439_ft5446_test_data.ini_data = (struct _ini_data *)xiaomi_sdm439_ft5446_fts_malloc(sizeof(struct _ini_data) * MAX_KEYWORD_NUM);
	if (NULL == xiaomi_sdm439_ft5446_test_data.ini_data) {
		FTS_ERROR("mallock memory for ini_data fail");
		goto SET_PARAM_ERR;
	}

	ret = xiaomi_sdm439_ft5446_ini_get_key_data(test_param);
	if (ret < 0) {
		FTS_TEST_ERROR("xiaomi_sdm439_ft5446_ini_get_key_data error.");
		return ret;
	}

	/* Read the selected chip from the configuration */
	ret = xiaomi_sdm439_ft5446_init_interface(test_param);
	if (ret < 0) {
		FTS_TEST_ERROR("IC_Type in ini is not supported");
		return ret;
	}

	/* Get test function */
	ret = xiaomi_sdm439_ft5446_init_test_funcs(xiaomi_sdm439_ft5446_test_data.screen_param.selected_ic);
	if (ret < 0) {
		FTS_TEST_ERROR("no ic series match");
		return ret;
	}

	if (NULL == xiaomi_sdm439_ft5446_test_data.func) {
		FTS_TEST_ERROR("test function is NULL");
		return -ENODATA;
	}

	/* test configuration */
	if (xiaomi_sdm439_ft5446_test_data.func->init_testitem) {
		xiaomi_sdm439_ft5446_test_data.func->init_testitem(test_param);
	}
	if (xiaomi_sdm439_ft5446_test_data.func->init_basicthreshold) {
		xiaomi_sdm439_ft5446_test_data.func->init_basicthreshold(test_param);
	}

	if (xiaomi_sdm439_ft5446_test_data.func->init_detailthreshold)
		xiaomi_sdm439_ft5446_test_data.func->init_detailthreshold(test_param);

	if (xiaomi_sdm439_ft5446_test_data.func->set_testitem_sequence) {
		xiaomi_sdm439_ft5446_test_data.func->set_testitem_sequence();
	}

	if (xiaomi_sdm439_ft5446_test_data.ini_data) {
		fts_free(xiaomi_sdm439_ft5446_test_data.ini_data);
	}
	FTS_TEST_FUNC_EXIT();
	return 0;

SET_PARAM_ERR:
	if (xiaomi_sdm439_ft5446_test_data.ini_data) {
		fts_free(xiaomi_sdm439_ft5446_test_data.ini_data);
	}
	return ret;
}

/*
 * xiaomi_sdm439_ft5446_fts_test_get_testparam_from_ini - get test parameters from ini
 *
 * read, parse the configuration file, initialize the test variable
 *
 * return 0 if succuss, else errro code
 */
int xiaomi_sdm439_ft5446_fts_test_get_testparam_from_ini(char *config_name)
{
	int ret = 0;
	char *ini_file_data = NULL;
	int inisize = 0;

	FTS_TEST_FUNC_ENTER();

	inisize = xiaomi_sdm439_ft5446_fts_test_get_ini_size(config_name);
	FTS_TEST_DBG("ini_size = %d ", inisize);
	if (inisize <= 0) {
		FTS_TEST_ERROR("%s ERROR:Get firmware size failed",  __func__);
		return -EIO;
	}

	ini_file_data = xiaomi_sdm439_ft5446_fts_malloc(inisize + 1); // 1: end mark
	if (NULL == ini_file_data) {
		FTS_TEST_ERROR("xiaomi_sdm439_ft5446_fts_malloc failed in function:%s",  __func__);
		return -ENOMEM;
	}
	memset(ini_file_data, 0, inisize + 1);

	ret = xiaomi_sdm439_ft5446_fts_test_read_ini_data(config_name, ini_file_data);
	if (ret) {
		FTS_TEST_ERROR(" - ERROR: xiaomi_sdm439_ft5446_fts_test_read_ini_data failed");
		goto GET_INI_DATA_ERR;
	} else {
		FTS_TEST_DBG("xiaomi_sdm439_ft5446_fts_test_read_ini_data successful");
	}

	ret = xiaomi_sdm439_ft5446_set_param_data(ini_file_data);
	if (ret) {
		FTS_TEST_ERROR("set param data fail");
		goto GET_INI_DATA_ERR;
	}

	if (ini_file_data) {
		fts_free(ini_file_data);
	}
	FTS_TEST_FUNC_EXIT();
	return 0;

GET_INI_DATA_ERR:
	if (ini_file_data) {
		fts_free(ini_file_data);
	}
	return ret;
}
