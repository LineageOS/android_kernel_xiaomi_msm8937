#include <linux/printk.h>
#include <linux/module.h>

static int no_techpack_audio_init(void)
{
	pr_info("techpack/audio isn't compiled in!");
	return 0;
}
module_init(no_techpack_audio_init)
