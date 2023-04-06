dtb-$(CONFIG_ARCH_MSM8917) += rolex.dtb riva.dtb riva-oreo.dtb ugglite.dtb
dtb-$(CONFIG_ARCH_MSM8937) += land.dtb prada.dtb
dtb-$(CONFIG_ARCH_MSM8940) += santoni.dtb ugg.dtb

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb
