#IST30xx touchpanel driver

ccflags-y := $(call cc-disable-warning, unused-but-set-variable)
ccflags-y += $(call cc-disable-warning, vla-extension)
obj-$(CONFIG_TOUCHSCREEN_IST30XX_MI8937) += ist30xxc.o
obj-$(CONFIG_TOUCHSCREEN_IST30XX_MI8937) += ist30xxc_update.o
obj-$(CONFIG_TOUCHSCREEN_IST30XX_MI8937) += ist30xxc_cmcs.o
obj-$(CONFIG_TOUCHSCREEN_IST30XX_MI8937) += ist30xxc_misc.o
obj-$(CONFIG_TOUCHSCREEN_IST30XX_MI8937) += ist30xxc_sys.o
obj-$(CONFIG_TOUCHSCREEN_IST30XX_MI8937) += ist30xxc_tracking.o
