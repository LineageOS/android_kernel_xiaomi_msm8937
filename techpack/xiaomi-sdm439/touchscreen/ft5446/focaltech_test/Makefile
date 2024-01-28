#drivers/input/touchscreen/focaltech_touch/focaltech_test
#
#Makefile for test module
#



ccflags-y := $(call cc-disable-warning, fortify-source)
ccflags-y += $(call cc-disable-warning, switch-bool)
ccflags-y += $(call cc-disable-warning, unused-but-set-variable)
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439) += focaltech_test.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439) += focaltech_test_ini.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439) += focaltech_test_detail_threshold.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439) += supported_ic/

