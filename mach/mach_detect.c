#include <linux/export.h>
#include <linux/kobject.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <xiaomi-msm8937/mach.h>

typedef struct xiaomi_msm8937_mach_info {
	int mach_family;
	const char *of_compatible;
	const char *codename;
	const char *product_name;
} xiaomi_msm8937_mach_info_t;

static const xiaomi_msm8937_mach_info_t xiaomi_msm8937_mach_table[XIAOMI_MSM8937_MACH_MAX] = {
	// No Family
#if IS_ENABLED(CONFIG_MACH_XIAOMI_PRADA)
	[XIAOMI_MSM8937_MACH_PRADA] = {XIAOMI_MSM8937_MACH_FAMILY_UNKNOWN, "xiaomi,prada", "prada", "Redmi 4 (Standard)"},
#endif

	// Family ULYSSE
#if IS_ENABLED(CONFIG_MACH_XIAOMI_UGG)
	[XIAOMI_MSM8937_MACH_UGG] = {XIAOMI_MSM8937_MACH_FAMILY_ULYSSE, "xiaomi,ugg", "ugg", "Redmi Note 5A / Y1 Prime"},
#endif
#if IS_ENABLED(CONFIG_MACH_XIAOMI_UGGLITE)
	[XIAOMI_MSM8937_MACH_UGGLITE] = {XIAOMI_MSM8937_MACH_FAMILY_ULYSSE, "xiaomi,ugglite", "ugglite", "Redmi Note 5A / Y1 Lite"},
#endif

	// Family WINGTECH (MSM8917)
#if IS_ENABLED(CONFIG_MACH_XIAOMI_RIVA)
	[XIAOMI_MSM8937_MACH_RIVA] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,riva", "riva", "Redmi 5A"},
#endif
#if IS_ENABLED(CONFIG_MACH_XIAOMI_ROLEX)
	[XIAOMI_MSM8937_MACH_ROLEX] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,rolex", "rolex", "Redmi 4A"},
#endif
#if IS_ENABLED(CONFIG_MACH_XIAOMI_TIARE)
	[XIAOMI_MSM8937_MACH_TIARE] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,tiare", "tiare", "Redmi Go"},
#endif

	// Family WINGTECH (MSM8937 / MSM8940)
#if IS_ENABLED(CONFIG_MACH_XIAOMI_LAND)
	[XIAOMI_MSM8937_MACH_LAND] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,land", "land", "Redmi 3S / 3X"},
#endif
#if IS_ENABLED(CONFIG_MACH_XIAOMI_SANTONI)
	[XIAOMI_MSM8937_MACH_SANTONI] = {XIAOMI_MSM8937_MACH_FAMILY_WINGTECH, "xiaomi,santoni", "santoni", "Redmi 4 (India) / 4X"},
#endif
};

#if IS_ENABLED(CONFIG_MACH_FAMILY_XIAOMI_WINGTECH)
static char saved_wingtech_board_id[10];
#endif
static int saved_mach = XIAOMI_MSM8937_MACH_UNKNOWN;
static struct kobject *xiaomi_msm8937_mach_kobj;

int xiaomi_msm8937_mach_get_family(void) {
	if (!saved_mach)
		return XIAOMI_MSM8937_MACH_FAMILY_UNKNOWN;
	return xiaomi_msm8937_mach_table[saved_mach].mach_family;
}
EXPORT_SYMBOL(xiaomi_msm8937_mach_get_family);

int xiaomi_msm8937_mach_get(void) {
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

	return rc;
}

static int __init xiaomi_msm8937_mach_detect_init(void) {
	int rc;

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

	rc = sysfs_create_file(xiaomi_msm8937_mach_kobj,
			&xiaomi_msm8937_mach_supported_machines_attr.attr);
	if (rc < 0)
		pr_err("%s: Failed to create sysfs file supported_machines, rc=%d\n", __func__, rc);

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
