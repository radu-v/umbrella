dtb-$(CONFIG_FIH_A1N) += \
  msm8998-mtp_A1N_EVB.dtb \
  msm8998-mtp_A1N_EVB_SS.dtb \
  msm8998-mtp_A1N_EVT.dtb \
  msm8998-mtp_A1N_EVT_SS.dtb \
  msm8998-mtp_A1N_EVT1_SS.dtb \
  msm8998-mtp_A1N_EVT1-1_SS.dtb \
  msm8998-mtp_A1N_EVT1-2_SS.dtb \
  msm8998-mtp_A1N_EVT1_5_SS.dtb \
  msm8998-mtp_A1N_DVT_SS.dtb \
  msm8998-mtp_A1N_DVT.dtb \
  msm8998-mtp_A1N_DVT_ROW.dtb \
  msm8998-mtp_A1N_DVT_CN.dtb \
  msm8998-mtp_A1N_DVT_US.dtb \
  msm8998-mtp_A1N_DVT_new_ROW.dtb \
  msm8998-mtp_A1N_DVT2_5_CN.dtb \
  msm8998-mtp_A1N_DVT3_new_ROW.dtb \
  msm8998-mtp_A1N_PVT_CN.dtb \
  msm8998-mtp_A1N_PVT_new_ROW.dtb \
  msm8998-mtp_A1N_MP_CN.dtb \
  msm8998-mtp_A1N_MP_new_ROW.dtb

dtb-$(CONFIG_FIH_NB1) += \
  msm8998-mtp_NB1_EVB.dtb \
  msm8998-mtp_NB1_EVB1.dtb \
  msm8998-mtp_NB1_EVB2.dtb \
  msm8998-mtp_NB1_EVT.dtb \
  msm8998-mtp_NB1_EVT0_5.dtb \
  msm8998-mtp_NB1_EVT1.dtb \
  msm8998-mtp_NB1_EVT1_SS.dtb \
  msm8998-mtp_NB1_DVT1.dtb \
  msm8998-mtp_NB1_DVT1_SS.dtb \
  msm8998-mtp_NB1_DVT1_CN.dtb \
  msm8998-mtp_NB1_DVT1_5.dtb \
  msm8998-mtp_NB1_DVT1_5_SS.dtb \
  msm8998-mtp_NB1_DVT1_5_CN.dtb \
  msm8998-mtp_NB1_DVT2.dtb \
  msm8998-mtp_NB1_DVT2_SS.dtb \
  msm8998-mtp_NB1_DVT2_CN.dtb \
  msm8998-mtp_NB1_PVT.dtb \
  msm8998-mtp_NB1_PVT_SS.dtb \
  msm8998-mtp_NB1_PVT_NR.dtb \
  msm8998-mtp_NB1_PVT1.dtb \
  msm8998-mtp_NB1_PVT1_SS.dtb \
  msm8998-mtp_NB1_PVT1_NR.dtb \
  msm8998-mtp_NB1_PVT1_Chile.dtb \
  msm8998-mtp_NB1_PVT1_Chile_SS.dtb

ifeq ($(CONFIG_FIH_NB1_TREBLE),y)
dtb-$(CONFIG_FIH_NB1) += \
  NB1_treble.dtb
else
dtb-$(CONFIG_FIH_NB1) += \
  NB1_nontreble.dtb
endif

always          := $(dtb-y)
subdir-y        := $(dts-dirs)
clean-files := *.dtb
