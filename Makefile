ifeq ($(CONFIG_MACH_XIAOMI_SDM439),y)
obj-$(CONFIG_HQ_SYSFS_SUPPORT_MI439) += hqsysfs/
else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
