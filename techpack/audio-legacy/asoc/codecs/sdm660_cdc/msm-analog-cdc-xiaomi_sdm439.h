#ifndef MSM_ANALOG_CDC_XIAOMI_SDM439_H
#define MSM_ANALOG_CDC_XIAOMI_SDM439_H

#include <xiaomi-sdm439/mach.h>

static const struct snd_soc_dapm_route xiaomi_sdm439_pine_audio_map[] = {
	{"SPK_OUT", NULL, "MI439 AW87329 PA"},
	{"MI439 AW87329 PA", "Switch", "LINEOUT PA"},
};

static const struct snd_soc_dapm_route xiaomi_sdm439_olive_audio_map[] = {
	{"SPK_OUT", NULL, "MI439 AW87519 PA"},
	{"MI439 AW87519 PA", "Switch", "LINEOUT PA"},
};

static int msm_anlg_cdc_add_xiaomi_sdm439_routes(struct snd_soc_dapm_context *dapm)
{
	switch (xiaomi_sdm439_mach_get_family()) {
		case XIAOMI_SDM439_MACH_FAMILY_PINE:
			return snd_soc_dapm_add_routes(dapm,
				xiaomi_sdm439_pine_audio_map,
				ARRAY_SIZE(xiaomi_sdm439_pine_audio_map));
		case XIAOMI_SDM439_MACH_FAMILY_OLIVE:
			return snd_soc_dapm_add_routes(dapm,
				xiaomi_sdm439_olive_audio_map,
				ARRAY_SIZE(xiaomi_sdm439_olive_audio_map));
		default:
			return -ENODEV;
	}
}

#endif
