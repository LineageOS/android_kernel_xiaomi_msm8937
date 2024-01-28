ifeq ($(CONFIG_MACH_XIAOMI_MSM8937),y)
obj-$(CONFIG_MACH_XIAOMI_MSM8937) += mach/

obj-$(CONFIG_SND_SOC) += audio_pa/
obj-y += fingerprint/
obj-y += ir/
obj-$(CONFIG_POWER_SUPPLY) += power_supply/
obj-$(CONFIG_REGULATOR) += regulator/
obj-$(CONFIG_INPUT_TOUCHSCREEN) += touchscreen/
obj-y += vibrator/

obj-$(CONFIG_NEW_LEDS) += leds/
else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
