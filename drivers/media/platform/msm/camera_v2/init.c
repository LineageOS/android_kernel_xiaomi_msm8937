#include <linux/module.h>
#include <linux/printk.h>

/*
extern bool msmb_camera_enable;

	if (!msmb_camera_enable)
		return -ENODEV;
*/

bool msmb_camera_enable = false;

static int __init msmb_camera_init(void)
{
	msmb_camera_enable = true;

	if (msmb_camera_enable)
		pr_info("Enable MSMB Camera Stack.\n");

	return 0;
}

module_init(msmb_camera_init);
