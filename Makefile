ifeq ($(CONFIG_MACH_XIAOMI_MSM8937),y)
obj-$(CONFIG_MACH_XIAOMI_MSM8937) += mach/

else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
