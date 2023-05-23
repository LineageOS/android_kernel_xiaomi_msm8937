# Goodix GT1x Touch Driver

ccflags-y := -O0
ccflags-y += $(call cc-disable-warning, sizeof-pointer-div)
ccflags-y += $(call cc-disable-warning, unused-but-set-variable)
ccflags-y += $(call cc-disable-warning, vla-extension)
obj-$(CONFIG_TOUCHSCREEN_GOODIX_GT1X_MI439) += gt1.o
gt1-objs	+= gt1x.o gt1x_generic.o gt1x_extents.o gt1x_update.o gt1x_tools.o gt1x_test.o test_function.o

