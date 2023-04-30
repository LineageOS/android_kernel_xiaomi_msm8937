GCC_VERSION      := $(shell $(CONFIG_SHELL) $(srctree)/scripts/gcc-version.sh $(CROSS_COMPILE)gcc)

ccflags-y += -Itechpack/camera-legacy/jpeg_10
ccflags-y += -Itechpack/camera-legacy/sensor/io
ccflags-y += -Itechpack/camera-legacy/common

obj-$(CONFIG_MSMB_JPEG) += msm_jpeg_dev.o msm_jpeg_sync.o msm_jpeg_core.o msm_jpeg_hw.o msm_jpeg_platform.o
