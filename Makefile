dtb-$(CONFIG_MACH_XIAOMI_LAND) += land.dtb
dtb-$(CONFIG_MACH_XIAOMI_PRADA) += prada.dtb
dtb-$(CONFIG_MACH_XIAOMI_RIVA_OREO) += riva-oreo.dtb
dtb-$(CONFIG_MACH_XIAOMI_RIVA) += riva.dtb
dtb-$(CONFIG_MACH_XIAOMI_ROLEX) += rolex.dtb
dtb-$(CONFIG_MACH_XIAOMI_SANTONI) += santoni.dtb
dtb-$(CONFIG_MACH_XIAOMI_TIARE) += tiare.dtb
dtb-$(CONFIG_MACH_XIAOMI_UGGLITE) += ugglite.dtb
dtb-$(CONFIG_MACH_XIAOMI_UGG) += ugg.dtb

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb
