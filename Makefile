dtb-$(CONFIG_ARCH_SDM439) += sdm439-pine.dtb
dtb-$(CONFIG_ARCH_SDM439) += sdm439-olive.dtb

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtbo
