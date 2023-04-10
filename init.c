#include <linux/module.h>
#include <linux/printk.h>

/*
extern bool camera_legacy_m_enable;

	if (!camera_legacy_m_enable)
		return -ENODEV;
*/

bool camera_legacy_m_enable = false;

static int __init camera_legacy_m_init(void)
{
	camera_legacy_m_enable = true;

	if (camera_legacy_m_enable)
		pr_info("Enable Legacy (Marshmallow) Camera Stack.\n");

	return 0;
}

module_init(camera_legacy_m_init);
