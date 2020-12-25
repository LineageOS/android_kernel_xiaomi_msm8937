#include <linux/of.h>

#include <linux/xiaomi_series.h>

int xiaomi_series = 0;

int xiaomi_series_get(void)
{
	int ret = 0;
	const char *xiaomi_series_str;

	ret = of_property_read_string(of_find_node_by_path("/"),"xiaomi,series", &xiaomi_series_str);

	if (!ret)
		printk("Xiaomi series = %s\n",xiaomi_series_str);
	else
		printk("error reading xiaomi series from FDT, ret=%d\n",ret);

	ret = 0;

	if (strcmp(xiaomi_series_str, "ulysse") == 0)
		ret = XIAOMI_SERIES_ULYSSE;
	else if (strcmp(xiaomi_series_str, "rova") == 0)
		ret = XIAOMI_SERIES_ROVA;
	else if (strcmp(xiaomi_series_str, "landtoni") == 0)
		ret = XIAOMI_SERIES_LANDTONI;
	else
		ret = XIAOMI_SERIES_UNKNOWN;

	xiaomi_series = ret;

	return ret;
}

int xiaomi_series_read(void)
{
	int ret = 0;

	if (xiaomi_series == 0)
		ret = xiaomi_series_get();
	else
		ret = xiaomi_series;

	return ret;
}
EXPORT_SYMBOL(xiaomi_series_read);
