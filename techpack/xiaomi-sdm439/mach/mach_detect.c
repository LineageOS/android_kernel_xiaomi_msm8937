#include <linux/export.h>
#include <linux/kobject.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/printk.h>
#include <xiaomi-sdm439/mach.h>
#if IS_ENABLED(CONFIG_HQ_SYSFS_SUPPORT_MI439)
#include "../hqsysfs/hqsys_pcba.h"
#endif

typedef struct xiaomi_sdm439_mach_info {
	enum xiaomi_sdm439_mach_family_types mach_family;
	const char *of_compatible;
	const char *codename;
	const char *product_name;
} xiaomi_sdm439_mach_info_t;

static const xiaomi_sdm439_mach_info_t xiaomi_sdm439_mach_table[XIAOMI_SDM439_MACH_MAX] = {
	// Family PINE
	[XIAOMI_SDM439_MACH_PINE] = {XIAOMI_SDM439_MACH_FAMILY_PINE, "xiaomi,pine", "pine", "Redmi 7A"},

	// Family OLIVE
	[XIAOMI_SDM439_MACH_OLIVE] = {XIAOMI_SDM439_MACH_FAMILY_OLIVE, "xiaomi,olive", "olive", "Redmi 8"},
	[XIAOMI_SDM439_MACH_OLIVELITE] = {XIAOMI_SDM439_MACH_FAMILY_OLIVE, "xiaomi,olive", "olivelite", "Redmi 8A"},
	[XIAOMI_SDM439_MACH_OLIVEWOOD] = {XIAOMI_SDM439_MACH_FAMILY_OLIVE, "xiaomi,olive", "olivewood", "Redmi 8A Dual"},
};

static enum xiaomi_sdm439_mach_types saved_mach = XIAOMI_SDM439_MACH_UNKNOWN;
static struct kobject *xiaomi_sdm439_mach_kobj;

enum xiaomi_sdm439_mach_family_types xiaomi_sdm439_mach_get_family(void) {
	if (!saved_mach)
		return XIAOMI_SDM439_MACH_FAMILY_UNKNOWN;
	return xiaomi_sdm439_mach_table[saved_mach].mach_family;
}
EXPORT_SYMBOL(xiaomi_sdm439_mach_get_family);

enum xiaomi_sdm439_mach_types xiaomi_sdm439_mach_get(void) {
	return saved_mach;
}
EXPORT_SYMBOL(xiaomi_sdm439_mach_get);

static void xiaomi_sdm439_mach_set_machine(enum xiaomi_sdm439_mach_types mach)
{
	pr_info("%s: Set machine to: %s (%s)\n", __func__,
			xiaomi_sdm439_mach_table[mach].product_name,
			xiaomi_sdm439_mach_table[mach].codename);
	saved_mach = mach;
}

#if IS_ENABLED(CONFIG_HQ_SYSFS_SUPPORT_MI439)
void xiaomi_sdm439_mach_notify_hq_pcba_config(PCBA_CONFIG hq_pcba)
{
	switch (hq_pcba) {
		case PCBA_OLIVE:
		case PCBA_OLIVE_P0_1_CN:
		case PCBA_OLIVE_P0_1_GLOBAL_B28:
		case PCBA_OLIVE_P0_1_INDIA:
		case PCBA_OLIVE_P1_CN:
		case PCBA_OLIVE_P1_GLOBAL_B28:
		case PCBA_OLIVE_P1_INDIA:
		case PCBA_OLIVE_P1_1_GLOBAL:
		case PCBA_OLIVE_P1_1_GLOBAL_B28:
		case PCBA_OLIVE_P1_1_INDIA:
		case PCBA_OLIVE_P2_CN:
		case PCBA_OLIVE_P2_GLOBAL:
		case PCBA_OLIVE_P2_GLOBAL_B28:
		case PCBA_OLIVE_P2_INDIA:
		case PCBA_OLIVE_P2_1_INDIA:
		case PCBA_OLIVE_MP_CN:
		case PCBA_OLIVE_MP_GLOBAL:
		case PCBA_OLIVE_MP_GLOBAL_B28:
		case PCBA_OLIVE_MP_INDIA:
		case PCBA_OLIVE_END:
			xiaomi_sdm439_mach_set_machine(XIAOMI_SDM439_MACH_OLIVE);
			break;
		case PCBA_PINE:
		case PCBA_PINE_P0_CN:
		case PCBA_PINE_P0_GLOBAL:
		case PCBA_PINE_P1_GLOBALNB28:
		case PCBA_PINE_P1_GLOBALB28:
		case PCBA_PINE_P1_CN:
		case PCBA_PINE_P1_INDIA:
		case PCBA_PINE_P1_1_INDIA:
		case PCBA_PINE_P1_1_GLOBALB28:
		case PCBA_PINE_P2_GLOBALNB28:
		case PCBA_PINE_P2_GLOBALB28:
		case PCBA_PINE_P2_CN:
		case PCBA_PINE_P2_INDIA:
		case PCBA_PINE_P2_MOBILE:
		case PCBA_PINE_MP_GLOBALNB28:
		case PCBA_PINE_MP_GLOBALB28:
		case PCBA_PINE_MP_CN:
		case PCBA_PINE_MP_INDIA:
		case PCBA_PINE_MP_MOBILE:
		case PCBA_PINE_END:
			xiaomi_sdm439_mach_set_machine(XIAOMI_SDM439_MACH_PINE);
			break;
		case PCBA_OLIVELITE:
		case PCBA_OLIVELITE_P0_1_CN:
		case PCBA_OLIVELITE_P1_CN:
		case PCBA_OLIVELITE_P1_GLOBAL_B28:
		case PCBA_OLIVELITE_P1_INDIA:
		case PCBA_OLIVELITE_P1_1_GLOBAL:
		case PCBA_OLIVELITE_P1_1_GLOBAL_B28:
		case PCBA_OLIVELITE_P1_1_INDIA:
		case PCBA_OLIVELITE_P2_CN:
		case PCBA_OLIVELITE_P2_GLOBAL:
		case PCBA_OLIVELITE_P2_GLOBAL_B28:
		case PCBA_OLIVELITE_P2_INDIA:
		case PCBA_OLIVELITE_P2_1_CN_PUBLIC:
		case PCBA_OLIVELITE_P2_1_CN:
		case PCBA_OLIVELITE_MP_CN:
		case PCBA_OLIVELITE_MP_GLOBAL:
		case PCBA_OLIVELITE_MP_GLOBAL_B28:
		case PCBA_OLIVELITE_MP_INDIA:
		case PCBA_OLIVELITE_END:
			xiaomi_sdm439_mach_set_machine(XIAOMI_SDM439_MACH_OLIVELITE);
			break;
		case PCBA_OLIVEWOOD:
		case PCBA_OLIVEWOOD_P2_NIKALA:
		case PCBA_OLIVEWOOD_P2_INDIA:
		case PCBA_OLIVEWOOD_MP_NIKALA:
		case PCBA_OLIVEWOOD_MP_INDIA:
		case PCBA_OLIVEWOOD_END:
			xiaomi_sdm439_mach_set_machine(XIAOMI_SDM439_MACH_OLIVEWOOD);
			break;
		default:
			return;
	}
}
EXPORT_SYMBOL(xiaomi_sdm439_mach_notify_hq_pcba_config);
#endif

static int xiaomi_sdm439_mach_early_detect(void) {
	if (of_machine_is_compatible(xiaomi_sdm439_mach_table[XIAOMI_SDM439_MACH_PINE].of_compatible))
		xiaomi_sdm439_mach_set_machine(XIAOMI_SDM439_MACH_PINE);
	else if (of_machine_is_compatible(xiaomi_sdm439_mach_table[XIAOMI_SDM439_MACH_OLIVE].of_compatible))
		xiaomi_sdm439_mach_set_machine(XIAOMI_SDM439_MACH_OLIVE);
	else
		return -EINVAL;

	return 0;
}

static ssize_t xiaomi_sdm439_mach_codename_show(struct kobject *kobj,
						struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", xiaomi_sdm439_mach_table[saved_mach].codename);
}

static struct kobj_attribute xiaomi_sdm439_mach_codename_attr = {
	.attr = {
		.name = "codename",
		.mode = 0444,
	},
	.show = xiaomi_sdm439_mach_codename_show,
};

static ssize_t xiaomi_sdm439_mach_product_name_show(struct kobject *kobj,
						struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", xiaomi_sdm439_mach_table[saved_mach].product_name);
}

static struct kobj_attribute xiaomi_sdm439_mach_product_name_attr = {
	.attr = {
		.name = "product_name",
		.mode = 0444,
	},
	.show = xiaomi_sdm439_mach_product_name_show,
};

static int __init xiaomi_sdm439_mach_detect_init(void) {
	int rc;

	// Print version
	pr_info("%s: Xiaomi SDM439 device tree git version: %s\n", __func__, MI439_DT_GIT_VER);
	pr_info("%s: Xiaomi SDM439 module git version: %s\n", __func__, MI439_MODULE_GIT_VER);

	// Detect
	rc = xiaomi_sdm439_mach_early_detect();
	if (rc < 0) {
		pr_err("%s: Could not early detect Xiaomi SDM439 machine, rc=%d\n", __func__, rc);
		goto fail;
	}

	// Create sysfs dir
	xiaomi_sdm439_mach_kobj = kobject_create_and_add("xiaomi-sdm439-mach", NULL);
	if (!xiaomi_sdm439_mach_kobj) {
		pr_err("%s: Failed to create sysfs dir\n", __func__);
		goto fail;
	}

	// Create sysfs files
	rc = sysfs_create_file(xiaomi_sdm439_mach_kobj,
			&xiaomi_sdm439_mach_codename_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file codename, rc=%d\n", __func__, rc);

	rc = sysfs_create_file(xiaomi_sdm439_mach_kobj,
			&xiaomi_sdm439_mach_product_name_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file product_name, rc=%d\n", __func__, rc);

	return 0;
fail:
	return rc;
}
core_initcall(xiaomi_sdm439_mach_detect_init);
