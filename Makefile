ifeq ($(CONFIG_MACH_XIAOMI_SDM439),y)
else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
