ifeq ($(shell test -d $(srctree)/arch/arm64/boot/dts/xiaomi-msm8937/.git; echo $$?),0)
MI8937_DT_GIT_VER := $(shell cd $(srctree)/arch/arm64/boot/dts/xiaomi-msm8937; /usr/bin/env PATH="$$PATH":/usr/bin:/usr/local/bin git rev-parse --short HEAD)
$(info - Xiaomi MSM8937 device tree git version: $(MI8937_DT_GIT_VER))
ccflags-y += -DMI8937_DT_GIT_VER=\"$(MI8937_DT_GIT_VER)\"
else
ccflags-y += -DMI8937_DT_GIT_VER=\"Unknown\"
endif

ifeq ($(shell test -d $(srctree)/$(src)/../.git; echo $$?),0)
MI8937_MODULE_GIT_VER := $(shell cd $(srctree)/$(src); /usr/bin/env PATH="$$PATH":/usr/bin:/usr/local/bin git rev-parse --short HEAD)
$(info - Xiaomi MSM8937 module git version: $(MI8937_MODULE_GIT_VER))
ccflags-y += -DMI8937_MODULE_GIT_VER=\"$(MI8937_MODULE_GIT_VER)\"
else
ccflags-y += -DMI8937_MODULE_GIT_VER=\"Unknown\"
endif

obj-$(CONFIG_MACH_XIAOMI_MSM8937) += mach_detect.o
