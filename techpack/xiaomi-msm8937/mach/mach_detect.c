#include <linux/export.h>
#include <linux/kobject.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-msm8937/mach.h>

typedef struct xiaomi_msm8937_mach_info {
	enum xiaomi_msm8937_mach_family_types mach_family;
	const char *of_compatible;
	const char *codename;
	const char *product_name;
} xiaomi_msm8937_mach_info_t;

static const xiaomi_msm8937_mach_info_t xiaomi_msm8937_mach_table[XIAOMI_MSM8937_MACH_MAX] = {
	// No Family
	[XIAOMI_MSM8937_MACH_PRADA] = {XIAOMI_MSM8937_MACH_FAMILY_UNKNOWN, "xiaomi,prada", "prada", "Redmi 4 (Standard)"},

	// Family ULYSSE
	[XIAOMI_MSM8937_MACH_UGG] = {XIAOMI_MSM8937_MACH_FAMILY_ULYSSE, "xiaomi,ugg", "ugg", "Redmi Note 5A / Y1 Prime"},
	[XIAOMI_MSM8937_MACH_UGGLITE] = {XIAOMI_MSM8937_MACH_FAMILY_ULYSSE, "xiaomi,ugglite", "ugglite", "Redmi Note 5A / Y1 Lite"},

	// Family WINGTECH (MSM8917)
	[XIAOMI_MSM8937_MACH_RIVA] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,riva", "riva", "Redmi 5A"},
	[XIAOMI_MSM8937_MACH_ROLEX] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,rolex", "rolex", "Redmi 4A"},
	[XIAOMI_MSM8937_MACH_TIARE] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,tiare", "tiare", "Redmi Go"},

	// Family WINGTECH (MSM8937 / MSM8940)
	[XIAOMI_MSM8937_MACH_LAND] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,land", "land", "Redmi 3S / 3X"},
	[XIAOMI_MSM8937_MACH_SANTONI] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,santoni", "santoni", "Redmi 4 (India) / 4X"},
};

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
static char saved_wingtech_board_id[10];
#endif
static enum xiaomi_msm8937_mach_types saved_mach = XIAOMI_MSM8937_MACH_UNKNOWN;
static struct kobject *xiaomi_msm8937_mach_kobj;

enum xiaomi_msm8937_mach_family_types xiaomi_msm8937_mach_get_family(void) {
	if (!saved_mach)
		return XIAOMI_MSM8937_MACH_FAMILY_UNKNOWN;
	return xiaomi_msm8937_mach_table[saved_mach].mach_family;
}
EXPORT_SYMBOL(xiaomi_msm8937_mach_get_family);

enum xiaomi_msm8937_mach_types xiaomi_msm8937_mach_get(void) {
	return saved_mach;
}
EXPORT_SYMBOL(xiaomi_msm8937_mach_get);

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
char *xiaomi_msm8937_mach_get_wingtech_board_id(void) {
	if (saved_wingtech_board_id[0])
		return saved_wingtech_board_id;
	else
		return "Unknown";
}
EXPORT_SYMBOL(xiaomi_msm8937_mach_get_wingtech_board_id);
#endif

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
static int __init wingtech_board_id_setup(char *str)
{
	strlcpy(saved_wingtech_board_id, str, sizeof(saved_wingtech_board_id));
	pr_info("%s: Wingtech board id: %s\n", __func__, saved_wingtech_board_id);
	return 1;
}
__setup("board_id=", wingtech_board_id_setup);
#endif

static ssize_t xiaomi_msm8937_mach_codename_show(struct kobject *kobj,
						struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", xiaomi_msm8937_mach_table[saved_mach].codename);
}

static struct kobj_attribute xiaomi_msm8937_mach_codename_attr = {
	.attr = {
		.name = "codename",
		.mode = 0444,
	},
	.show = xiaomi_msm8937_mach_codename_show,
};

static ssize_t xiaomi_msm8937_mach_product_name_show(struct kobject *kobj,
						struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", xiaomi_msm8937_mach_table[saved_mach].product_name);
}

static struct kobj_attribute xiaomi_msm8937_mach_product_name_attr = {
	.attr = {
		.name = "product_name",
		.mode = 0444,
	},
	.show = xiaomi_msm8937_mach_product_name_show,
};

/*
static ssize_t xiaomi_msm8937_mach_supported_machines_show(struct kobject *kobj,
							struct kobj_attribute *attr, char *buf)
{
	int i, count = 0;

	for (i=1; i<XIAOMI_MSM8937_MACH_MAX; ++i) {
		count += snprintf(buf+count, PAGE_SIZE - count, "%s (%s)\n",
				xiaomi_msm8937_mach_table[i].product_name,
				xiaomi_msm8937_mach_table[i].codename);
	}

	return count;
}

static struct kobj_attribute xiaomi_msm8937_mach_supported_machines_attr = {
	.attr = {
		.name = "supported_machines",
		.mode = 0444,
	},
	.show = xiaomi_msm8937_mach_supported_machines_show,
};
*/

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
static ssize_t xiaomi_msm8937_mach_wingtech_board_id_show(struct kobject *kobj,
							struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", saved_wingtech_board_id);
}

static struct kobj_attribute xiaomi_msm8937_mach_wingtech_board_id_attr = {
	.attr = {
		.name = "wingtech_board_id",
		.mode = 0444,
	},
	.show = xiaomi_msm8937_mach_wingtech_board_id_show,
};
#endif

static int xiaomi_msm8937_mach_detect(void) {
	int i, rc;

	for (i=1; i<XIAOMI_MSM8937_MACH_MAX; ++i) {
		rc = of_machine_is_compatible(xiaomi_msm8937_mach_table[i].of_compatible);
		if (rc) {
			saved_mach = i;
			break;
		}
	}

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH_MSM8917)
	if (saved_wingtech_board_id[0]) {
		if ((saved_mach == XIAOMI_MSM8937_MACH_ROLEX && strncmp(saved_wingtech_board_id, "S88503", 6) != 0) ||
			(saved_mach == XIAOMI_MSM8937_MACH_RIVA  && strncmp(saved_wingtech_board_id, "S88505", 6) != 0) ||
			(saved_mach == XIAOMI_MSM8937_MACH_TIARE && strncmp(saved_wingtech_board_id, "S88508", 6) != 0)) {
#if !IS_ENABLED(CONFIG_MACH_XIAOMI_RIVA_OREO)
			if (!strncmp(saved_wingtech_board_id, "S88505", 6))
				pr_emerg("%s: %d: !!! This device is Redmi 5A. Make sure to use Nougat bootloader. Oreo bootloader is NOT supported on this kernel build !!!\n", __func__, __LINE__);
#endif
			goto emerg_wingtech_board_id;
		}
	}
#endif

	return rc;

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH_MSM8917)
emerg_wingtech_board_id:
	pr_emerg("%s: %d: Machine type mismatches with wingtech board ID!\n", __func__, __LINE__);
	pr_emerg("%s: %d: Current machine codename: \"%s\", Current wingtech board ID:\"%s\"\n", __func__, __LINE__, xiaomi_msm8937_mach_table[saved_mach].codename, saved_wingtech_board_id);
	pr_emerg("%s: %d: Triggering kernel panic\n", __func__, __LINE__);
	panic("Xiaomi MSM8937 machine type mismatches with wingtech board ID\n");
#endif

	return -ENODEV;
}

static int __init xiaomi_msm8937_mach_detect_init(void) {
	int rc;

	// Print version
	pr_info("%s: Xiaomi MSM8937 device tree git version: %s\n", __func__, MI8937_DT_GIT_VER);
	pr_info("%s: Xiaomi MSM8937 module git version: %s\n", __func__, MI8937_MODULE_GIT_VER);

	// Detect
	rc = xiaomi_msm8937_mach_detect();
	if (!rc) {
		pr_err("%s: Could not detect Xiaomi MSM8937 machine, rc=%d\n", __func__, rc);
		goto fail;
	}

	// Print the current machine
	pr_info("%s: Current machine: %s (%s)\n", __func__,
			xiaomi_msm8937_mach_table[saved_mach].product_name,
			xiaomi_msm8937_mach_table[saved_mach].codename);

	// Create sysfs dir
	xiaomi_msm8937_mach_kobj = kobject_create_and_add("xiaomi-msm8937-mach", NULL);
	if (!xiaomi_msm8937_mach_kobj) {
		pr_err("%s: Failed to create sysfs dir\n", __func__);
		goto fail;
	}

	// Create sysfs files
	rc = sysfs_create_file(xiaomi_msm8937_mach_kobj,
			&xiaomi_msm8937_mach_codename_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file codename, rc=%d\n", __func__, rc);

	rc = sysfs_create_file(xiaomi_msm8937_mach_kobj,
			&xiaomi_msm8937_mach_product_name_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file product_name, rc=%d\n", __func__, rc);

/*
	rc = sysfs_create_file(xiaomi_msm8937_mach_kobj,
			&xiaomi_msm8937_mach_supported_machines_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file supported_machines, rc=%d\n", __func__, rc);
*/

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
	if (saved_wingtech_board_id[0]) {
		rc = sysfs_create_file(xiaomi_msm8937_mach_kobj,
				&xiaomi_msm8937_mach_wingtech_board_id_attr.attr);
		if (rc < 0)
			pr_err("%s: Failed to create sysfs file wingtech_board_id, rc=%d\n",
				__func__, rc);
	}
#endif

	return 0;
fail:
	return rc;
}
core_initcall(xiaomi_msm8937_mach_detect_init);
