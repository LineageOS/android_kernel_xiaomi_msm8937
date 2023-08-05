#
# Makefile for the focaltech touchscreen drivers.
#

# Each configuration option enables a list of files.

ccflags-y := $(call cc-disable-warning, fortify-source)
ccflags-y += $(call cc-disable-warning, invalid-source-encoding)
ccflags-y += $(call cc-disable-warning, switch-bool)
ccflags-y += $(call cc-disable-warning, unused-but-set-variable)

obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_core.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_ex_fun.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_ex_mode.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_flash.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_gesture.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_esdcheck.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_i2c.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_point_report_check.o
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_flash/
obj-$(CONFIG_TOUCHSCREEN_FT5446_MI439)	+=  focaltech_test/

