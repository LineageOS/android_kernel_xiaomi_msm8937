dtbo-$(CONFIG_ARCH_SDM439) += sdm439-qrd-overlay-pine.dtbo
sdm439-qrd-overlay-pine.dtbo-base := sdm439-pine.dtb

#dtbo-$(CONFIG_ARCH_SDM439) += sdm439-qrd-olive-overlay.dtbo
#sdm439-qrd-olive-overlay.dtbo-base := sdm439-olive.dtb

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtbo
