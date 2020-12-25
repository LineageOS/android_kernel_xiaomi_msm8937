#include <linux/of.h>

#include <linux/xiaomi_device.h>

int xiaomi_device = 0;

int xiaomi_device_get(void)
{
	int ret = 0;
	const char *xiaomi_device_str;

	ret = of_property_read_string(of_find_node_by_path("/"),"xiaomi,device", &xiaomi_device_str);

	if (!ret)
		printk("Xiaomi device = %s\n",xiaomi_device_str);
	else
		printk("error reading xiaomi device from FDT, ret=%d\n",ret);

	ret = 0;

	if (strcmp(xiaomi_device_str, "ugglite") == 0)
		ret = XIAOMI_DEVICE_UGGLITE;
	else if (strcmp(xiaomi_device_str, "ugg") == 0)
		ret = XIAOMI_DEVICE_UGG;
	else if (strcmp(xiaomi_device_str, "rolex") == 0)
		ret = XIAOMI_DEVICE_ROLEX;
	else if (strcmp(xiaomi_device_str, "riva") == 0)
		ret = XIAOMI_DEVICE_RIVA;
	else if (strcmp(xiaomi_device_str, "tiare") == 0)
		ret = XIAOMI_DEVICE_TIARE;
	else if (strcmp(xiaomi_device_str, "land") == 0)
		ret = XIAOMI_DEVICE_LAND;
	else if (strcmp(xiaomi_device_str, "santoni") == 0)
		ret = XIAOMI_DEVICE_SANTONI;
	else
		ret = XIAOMI_DEVICE_UNKNOWN;

	xiaomi_device = ret;

	return ret;
}

int xiaomi_device_read(void)
{
	int ret = 0;

	if (xiaomi_device == 0)
		ret = xiaomi_device_get();
	else
		ret = xiaomi_device;

	return ret;
}
EXPORT_SYMBOL(xiaomi_device_read);
