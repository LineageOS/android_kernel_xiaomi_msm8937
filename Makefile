dtb-$(CONFIG_ARCH_MSM8917) += rolex.dtb riva.dtb riva-oreo.dtb ugglite.dtb
dtb-$(CONFIG_ARCH_MSM8940) += ugg.dtb

dts-dirs += wingtech/msm8937

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb
