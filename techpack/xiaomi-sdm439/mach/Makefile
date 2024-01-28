ifeq ($(shell test -d $(srctree)/arch/arm64/boot/dts/xiaomi-sdm439/.git; echo $$?),0)
MI439_DT_GIT_VER := $(shell cd $(srctree)/arch/arm64/boot/dts/xiaomi-sdm439; /usr/bin/env PATH="$$PATH":/usr/bin:/usr/local/bin git rev-parse --short HEAD)
$(info - Xiaomi SDM439 device tree git version: $(MI439_DT_GIT_VER))
ccflags-y += -DMI439_DT_GIT_VER=\"$(MI439_DT_GIT_VER)\"
else
ccflags-y += -DMI439_DT_GIT_VER=\"Unknown\"
endif

ifeq ($(shell test -d $(srctree)/$(src)/../.git; echo $$?),0)
MI439_MODULE_GIT_VER := $(shell cd $(srctree)/$(src); /usr/bin/env PATH="$$PATH":/usr/bin:/usr/local/bin git rev-parse --short HEAD)
$(info - Xiaomi SDM439 module git version: $(MI439_MODULE_GIT_VER))
ccflags-y += -DMI439_MODULE_GIT_VER=\"$(MI439_MODULE_GIT_VER)\"
else
ccflags-y += -DMI439_MODULE_GIT_VER=\"Unknown\"
endif

obj-$(CONFIG_MACH_XIAOMI_SDM439) += mach_detect.o
