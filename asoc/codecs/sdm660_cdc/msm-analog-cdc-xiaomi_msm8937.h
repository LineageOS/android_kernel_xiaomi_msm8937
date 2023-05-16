#ifndef MSM_ANALOG_CDC_XIAOMI_MSM8937_H
#define MSM_ANALOG_CDC_XIAOMI_MSM8937_H

#include <xiaomi-msm8937/mach.h>

#define MI8937_ADD_ROUTE(route) \
	snd_soc_dapm_add_routes(dapm, xiaomi_msm8937_audio_map_##route, \
		ARRAY_SIZE(xiaomi_msm8937_audio_map_##route))

#define MI8937_DEFINE_SPK_ROUTE(name, widget, source) \
	static const struct snd_soc_dapm_route xiaomi_msm8937_audio_map_##name[] = { \
		{"SPK_OUT", NULL, #widget}, \
		{#widget, "Switch", #source}, \
	};

static const struct snd_soc_dapm_route xiaomi_msm8937_audio_map_hph_pa_gpio[] = {
	{"HEADPHONE", NULL, "HPH PA GPIO"},
	{"HPH PA GPIO", "Switch", "HPHL PA"},
	{"HPH PA GPIO", "Switch", "HPHR PA"},
};

MI8937_DEFINE_SPK_ROUTE(spk_pa_gpio_hphl, SPK PA GPIO, HPHL PA)
MI8937_DEFINE_SPK_ROUTE(spk_pa_gpio_hphr, SPK PA GPIO, HPHR PA)

#if IS_ENABLED(CONFIG_SND_SOC_AW87319_MI8937)
MI8937_DEFINE_SPK_ROUTE(aw87319_spk_hphr, MI8937 AW87319 PA, HPHR PA)
#endif
#if IS_ENABLED(CONFIG_SND_SOC_AW87329_MI8937)
MI8937_DEFINE_SPK_ROUTE(aw87329_spk_hphr, MI8937 AW87329 PA, HPHR PA)
#endif

static int msm_anlg_cdc_add_xiaomi_msm8937_routes(struct snd_soc_dapm_context *dapm)
{
	int ret = 0;

	if (!xiaomi_msm8937_mach_get())
		return -ENODEV;

	ret |= MI8937_ADD_ROUTE(hph_pa_gpio);

	switch (xiaomi_msm8937_mach_get()) {
		case XIAOMI_MSM8937_MACH_UGG:
		case XIAOMI_MSM8937_MACH_UGGLITE:
			ret |= MI8937_ADD_ROUTE(spk_pa_gpio_hphl);
			break;
		case XIAOMI_MSM8937_MACH_LAND:
		case XIAOMI_MSM8937_MACH_PRADA:
		case XIAOMI_MSM8937_MACH_RIVA:
		case XIAOMI_MSM8937_MACH_ROLEX:
			ret |= MI8937_ADD_ROUTE(spk_pa_gpio_hphr);
			break;
		case XIAOMI_MSM8937_MACH_SANTONI:
#if IS_ENABLED(CONFIG_SND_SOC_AW87319_MI8937)
			ret |= MI8937_ADD_ROUTE(aw87319_spk_hphr);
#endif
			break;
		case XIAOMI_MSM8937_MACH_TIARE:
#if IS_ENABLED(CONFIG_SND_SOC_AW87329_MI8937)
			ret |= MI8937_ADD_ROUTE(aw87329_spk_hphr);
#endif
			break;
		default:
			break;
	}

	return ret;
}

#endif
