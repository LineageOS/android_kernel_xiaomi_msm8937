#
# Makefile for the Novatek ILITEK touchscreen driver.
#

ccflags-y := $(call cc-disable-warning, vla-extension)

# Each configuration option enables a list of files.
obj-$(CONFIG_TOUCHSCREEN_ITK9881H_MI439) += ilitek_plat_qcom.o ilitek_fw.o ilitek_main.o ilitek_mp.o ilitek_node.o ilitek_spi.o ilitek_touch.o ilitek_ic.o
