ifeq ($(CONFIG_MSMB_CAMERA_LEGACY),y)
ccflags-y += -I $(srctree)/techpack/camera-legacy
ccflags-y += -I $(srctree)/techpack/camera-legacy/sensor
ccflags-y += -I $(srctree)/techpack/camera-legacy/codecs
ccflags-y += -I $(srctree)/techpack/camera-legacy/isps
ccflags-y += -I $(srctree)/techpack/camera-legacy/pproc
ccflags-y += -I $(srctree)/techpack/camera-legacy/msm_vb2
ccflags-y += -I $(srctree)/techpack/camera-legacy/camera
ccflags-y += -I $(srctree)/techpack/camera-legacy/jpeg_10
ccflags-y += -I $(srctree)/techpack/camera-legacy/jpeg_dma
ccflags-y += -I $(srctree)/techpack/camera-legacy/fd
ccflags-y += -I $(srctree)/techpack/camera-legacy/common

ccflags-y += $(DISABLE_CFI_CLANG) $(DISABLE_LTO_CLANG)

# Use USERINCLUDE when you must reference the UAPI directories only.
USERINCLUDE     += \
                -I$(srctree)/techpack/camera-legacy/include/uapi \

# Use LINUXINCLUDE when you must reference the include/ directory.
# Needed to be compatible with the O= option
LINUXINCLUDE    += \
                -I$(srctree)/techpack/camera-legacy/include \
                -I$(srctree)/techpack/camera-legacy/include/uapi

obj-$(CONFIG_MSMB_CAMERA_LEGACY) += init.o

obj-$(CONFIG_MSMB_CAMERA) += common/
obj-$(CONFIG_MSMB_CAMERA) += msm.o
obj-$(CONFIG_MSMB_CAMERA) += camera/
obj-$(CONFIG_MSMB_CAMERA) += msm_vb2/
obj-$(CONFIG_MSMB_CAMERA) += sensor/
obj-$(CONFIG_MSMB_CAMERA) += pproc/
obj-$(CONFIG_MSMB_CAMERA) += isp/
obj-$(CONFIG_MSMB_CAMERA) += ispif/
obj-$(CONFIG_MSMB_JPEG) += jpeg_10/
obj-$(CONFIG_MSM_JPEGDMA) += jpeg_dma/
obj-$(CONFIG_MSMB_CAMERA) += msm_buf_mgr/
obj-$(CONFIG_MSM_FD) += fd/
else
ccflags-y := -Wno-unused-function
obj-y := stub.o
endif
