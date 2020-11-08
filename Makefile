# auto-detect subdirs
ifeq ($(CONFIG_ARCH_SDXPOORWILLS),y)
  audioconf := -include $(srctree)/techpack/audio/config/sdxpoorwillsautoconf.h
  include $(srctree)/techpack/audio/config/sdxpoorwillsauto.conf
  export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm710auto.conf)
else ifeq ($(CONFIG_ARCH_SM8150),y)
  audioconf := -include $(srctree)/techpack/audio/config/sm8150autoconf.h
  include $(srctree)/techpack/audio/config/sm8150auto.conf
  export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm710auto.conf)
else ifeq ($(CONFIG_ARCH_SDMSHRIKE),y)
  audioconf := -include $(srctree)/techpack/audio/config/sm8150autoconf.h
  include $(srctree)/techpack/audio/config/sm8150auto.conf
  export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm710auto.conf)
else ifeq ($(CONFIG_ARCH_KONA),y)
  audioconf := -include $(srctree)/techpack/audio/config/konaautoconf.h
  include $(srctree)/techpack/audio/config/konaauto.conf
else ifeq ($(CONFIG_ARCH_SDM660),y)
  audioconf := -include $(srctree)/techpack/audio/config/sdm660autoconf.h
  include $(srctree)/techpack/audio/config/sdm660auto.conf
else
  # msm8953 platform
  ifeq ($(CONFIG_ARCH_SDM632),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_SDM450),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_SDM439),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_SDM429),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_MSM8953),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_MSM8940),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_MSM8937),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else ifeq ($(CONFIG_ARCH_MSM8917),y)
    audioconf := -include $(srctree)/techpack/audio/config/sdm450autoconf.h
    include $(srctree)/techpack/audio/config/sdm450auto.conf
    export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdm450auto.conf)
  else
    # msm8909 platform
    ifeq ($(CONFIG_ARCH_QM215),y)
      audioconf := -include $(srctree)/techpack/audio/config/msm8909autoconf.h
      include $(srctree)/techpack/audio/config/msm8909auto.conf
      export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/msm8909auto.conf)
    else ifeq ($(CONFIG_ARCH_MSM8909),y)
      audioconf := -include $(srctree)/techpack/audio/config/msm8909autoconf.h
      include $(srctree)/techpack/audio/config/msm8909auto.conf
      export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/msm8909auto.conf)
    else
      ifeq ($(CONFIG_ARCH_SDXPOORWILLS),y)
        audioconf := -include $(srctree)/techpack/audio/config/sdxpoorwillsautoconf.h
        include $(srctree)/techpack/audio/config/sdxpoorwillsauto.conf
        export $(shell sed 's/=.*//' $(srctree)/techpack/audio/config/sdxpoorwillsauto.conf)
      endif
    endif
  endif
endif

# Use USERINCLUDE when you must reference the UAPI directories only.
USERINCLUDE     += \
                -I$(srctree)/techpack/audio/include/uapi \
                -I$(srctree)/techpack/audio/include

# Use LINUXINCLUDE when you must reference the include/ directory.
# Needed to be compatible with the O= option
LINUXINCLUDE    += \
                -I$(srctree)/techpack/audio/include/uapi \
                -I$(srctree)/techpack/audio/include \
                $(audioconf)

obj-y += soc/
obj-y += dsp/
obj-y += ipc/
obj-y += asoc/
