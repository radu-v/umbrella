/* Copyright (c) 2017, FIH Mobile Limited Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/of_platform.h>
#include "../mdss_dsi.h"
#include "../mdss_mdp.h"
#include "fih_msm_mdss_aod.h"
#ifdef CONFIG_TOUCHSCREEN_SIW
#include "../../../../include/linux/input/siw_touch_notify.h" //SW8-Touch_Notify-00+
#include "../../../../fih/fih_touch.h"//SW8-DH-TP_vendor-00+
extern struct fih_touch_cb touch_cb;
#endif

#include "fih_msm_mdss_aod.h"

extern int mdss_dsi_pinctrl_set_state(
	struct mdss_dsi_ctrl_pdata *ctrl_pdata,
	bool active);

void fih_mdss_panel_parse_dt(struct device_node *np,struct mdss_dsi_ctrl_pdata *ctrl_pdata)
{
	int rc=0;
	u32 tmp=0;
	struct mdss_panel_info *pinfo = &(ctrl_pdata->panel_data.panel_info);

	rc = of_property_read_u32(np, "fih,panel-id", &tmp);
	pinfo->panel_id = !rc ? tmp : UNDEFINE_UNKNOW_PANEL;
	pr_info("%s:fih,panel-id =%d\n", __func__, tmp);


	pinfo->aod_power_keep = of_property_read_bool(np,
		"fih,always_display_power_keep");
	pr_info("%s:Always on power keeping =%d\n", __func__, pinfo->aod_power_keep);

	if(pinfo->aod_power_keep)
	{
		pinfo->aod_power_keep_1p8= of_property_read_bool(np,
			"fih,always_display_power_keep-1p8");

		pr_info("%s:keep 1P8V is %s\n", __func__, pinfo->aod_power_keep_1p8?"on":"off");

		pinfo->aod_power_keep_3p3= of_property_read_bool(np,
			"fih,always_display_power_keep-3p3");
		pr_info("%s:keep 3P3V is %s\n", __func__, pinfo->aod_power_keep_3p3?"on":"off");

		pinfo->aod_power_keep_lab= of_property_read_bool(np,
			"fih,always_display_power_keep-lab");
		pr_info("%s:keep LAB is %s\n", __func__, pinfo->aod_power_keep_lab?"on":"off");

		pinfo->aod_power_keep_ibb= of_property_read_bool(np,
			"fih,always_display_power_keep-ibb");
		pr_info("%s:keep IBB is %s\n", __func__, pinfo->aod_power_keep_ibb?"on":"off");

	}
	return;
}

void fih_mdss_panel_ulps_pwr_parse_dt(struct device_node *np,struct mdss_dsi_ctrl_pdata *ctrl_pdata)
{
	struct mdss_panel_info *pinfo = &(ctrl_pdata->panel_data.panel_info);

	pinfo->aod_ulps_pwr_feature = of_property_read_bool(np,
		"fih,aod-ulps-pwr-feature");
	pr_info("%s:mipi phy power is default %s\n", __func__,
		(pinfo->ulps_suspend_enabled && !pinfo->aod_ulps_pwr_feature)?"on":"off");

	return;
}

void mdss_dsi_extra_power_init(struct dsi_shared_data *sdata,struct mdss_panel_info *pinfo)
{
	int rc=0;
	if (pinfo->ulps_suspend_enabled) {
		/*There are some of panel need to always keep power, when aod enable the power will always keep*/
		if(pinfo->panel_id != UNDEFINE_UNKNOW_PANEL || pinfo->aod_power_keep){
			pr_err("%s: Keep to enable vregs for start\n",
				__func__);
			if(pinfo->aod_power_keep_1p8){
				rc = msm_dss_enable_vreg(
					sdata->power_data[DSI_VDDIO_PM].vreg_config,
					sdata->power_data[DSI_VDDIO_PM].num_vreg, 1);
				if (rc) {
					pr_err("%s: failed to enable vregs for DSI_VDDIO_PM\n",
						__func__);
					return ;
				}
			}
			if(pinfo->aod_power_keep_3p3){
				rc = msm_dss_enable_vreg(
					sdata->power_data[DSI_VPNL_PM].vreg_config,
					sdata->power_data[DSI_VPNL_PM].num_vreg, 1);
				if (rc) {
					pr_err("%s: failed to enable vregs for DSI_VPNL_PM\n",
						__func__);
					return;
				}
			}
			if(pinfo->aod_power_keep_lab){
				rc = msm_dss_enable_vreg(
					sdata->power_data[DSI_LAB_PM].vreg_config,
					sdata->power_data[DSI_LAB_PM].num_vreg, 1);
				if (rc) {
					pr_err("%s: failed to enable vregs for DSI_LAB_PM\n",
						__func__);
					return;
				}
			}
			if(pinfo->aod_power_keep_ibb){
				rc = msm_dss_enable_vreg(
					sdata->power_data[DSI_IBB_PM].vreg_config,
					sdata->power_data[DSI_IBB_PM].num_vreg, 1);
				if (rc) {
					pr_err("%s: failed to enable vregs for DSI_IBB_PM\n",
						__func__);
					return;
				}
			}
			pr_err("%s: Keep to enable vregs for end\n",
							__func__);

		}
	}
}


int mdss_dsi_panel_extra_power_lp(struct mdss_panel_data *pdata, int enable)
{
	/* Panel power control when entering/exiting lp mode */
	int rc=0;
	struct mdss_panel_info *pinfo;
	struct dsi_shared_data *sdata;
	struct mdss_dsi_ctrl_pdata *ctrl_pdata = NULL;


	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return -EINVAL;
	}
	ctrl_pdata = container_of(pdata, struct mdss_dsi_ctrl_pdata,
					panel_data);

	pinfo = &pdata->panel_info;
	sdata = ctrl_pdata->shared_data;

	pr_info("%s: enable(%d)\n",__func__,enable);
	if(!pinfo->ulps_suspend_enabled){
		pr_info("%s: ulps syspend is not defainition\n",__func__);
		return 0;
	}
	if(enable){
		pr_info("%s: ulps syspend setup PHY Enable\n",__func__);

		if(!pinfo->aod_phy_pwr){
			rc = msm_dss_enable_vreg(
				sdata->power_data[DSI_PHY_PM].vreg_config,
				sdata->power_data[DSI_PHY_PM].num_vreg, 1);
		}else{
			pr_info("%s: ulps syspend have been PHY Enable\n",__func__);
			return rc;
		}
		if (rc) {
			pr_err("%s: failed to enable vregs for DSI_PHY_PM\n",
				__func__);
			return rc;
		}
		pinfo->aod_phy_pwr=true;
	}else{
		pr_info("%s: ulps syspend setup PHY disable \n",__func__);

		if(pinfo->aod_phy_pwr){
			rc = msm_dss_enable_vreg(
				sdata->power_data[DSI_PHY_PM].vreg_config,
				sdata->power_data[DSI_PHY_PM].num_vreg, 0);
		}else{
			pr_info("%s: ulps syspend have been PHY disable\n",__func__);
			return rc;
		}
		if (rc) {
			pr_err("%s: failed to enable vregs for DSI_PHY_PM\n",
				__func__);
			return rc;
		}
		pinfo->aod_phy_pwr=false;
	}
	return 0;
}

int mdss_dsi_extra_panel_power_on(struct mdss_panel_data *pdata)
{
	int ret = 0;
	struct mdss_dsi_ctrl_pdata *ctrl_pdata = NULL;
	struct mdss_panel_info *pinfo;

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return -EINVAL;
	}
	pr_err("%s: +. \n",__func__);

	ctrl_pdata = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);
	pinfo = &pdata->panel_info;

	switch(pinfo->panel_id)
	{
	case LGD_LH530QH1_WQXGA_CMD_PANEL:
		if(!pinfo->panel_power_init){

			ret = msm_dss_enable_vreg(
				ctrl_pdata->panel_power_data.vreg_config,
				ctrl_pdata->panel_power_data.num_vreg, 1);
			if (ret) {
				pr_err("%s: failed to enable vregs for %s\n",
					__func__, __mdss_dsi_pm_name(DSI_PANEL_PM));
				return ret;
			}
			if(!pinfo->aod_phy_pwr&&pinfo->aod_ulps_pwr_feature){
				mdss_dsi_panel_extra_power_lp(pdata,1);
			}
			pr_err("%s: panel power on\n", __func__);
			pinfo->panel_power_init =1;
		}
		break;

	case JDI_LPM053A466A_WQXGA_CMD_PANEL:
	default:
		ret = msm_dss_enable_vreg(
			ctrl_pdata->panel_power_data.vreg_config,
			ctrl_pdata->panel_power_data.num_vreg, 1);
		if (ret) {
			pr_err("%s: failed to enable vregs for %s\n",
				__func__, __mdss_dsi_pm_name(DSI_PANEL_PM));
			return ret;
		}
		if(!pinfo->aod_phy_pwr&&pinfo->aod_ulps_pwr_feature){
			mdss_dsi_panel_extra_power_lp(pdata,1);
		}

		break;
	}
	return ret;
}

int mdss_dsi_extra_panel_power_off(struct mdss_panel_data *pdata)
{
	int ret = 0;
	struct mdss_dsi_ctrl_pdata *ctrl_pdata = NULL;
	struct mdss_panel_info *pinfo;

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		ret = -EINVAL;
		return ret;
	}

	ctrl_pdata = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);
	pinfo = &pdata->panel_info;
	switch(pinfo->panel_id)
	{
	case LGD_LH530QH1_WQXGA_CMD_PANEL:
		ret = mdss_dsi_panel_reset(pdata, 0);
		if (ret) {
			pr_warn("%s: Panel reset failed. rc=%d\n", __func__, ret);
			ret = 0;
		}

		if (mdss_dsi_pinctrl_set_state(ctrl_pdata, false))
			pr_debug("reset disable: pinctrl not enabled\n");
#ifdef CONFIG_TOUCHSCREEN_SIW
		if((pinfo->panel_power_init && !fih_get_glance() && !touch_cb.touch_double_tap_read()) ||
			(pinfo->panel_power_init && pinfo->aod_screen_timeout && !touch_cb.touch_double_tap_read()))
#else
		if((pinfo->panel_power_init && !fih_get_glance()))
#endif
		{
			ret = msm_dss_enable_vreg(
				ctrl_pdata->panel_power_data.vreg_config,
				ctrl_pdata->panel_power_data.num_vreg, 0);
			if (ret){
				pr_err("%s: failed to disable vregs for %s\n",
					__func__, __mdss_dsi_pm_name(DSI_PANEL_PM));
			}
			pr_err("%s: panel power off\n", __func__);
			pinfo->panel_power_init=0;
		}
		if(pinfo->aod_phy_pwr&&pinfo->aod_ulps_pwr_feature){
				mdss_dsi_panel_extra_power_lp(pdata,0);
		}
		break;

	case JDI_LPM053A466A_WQXGA_CMD_PANEL:
	default:
		ret = mdss_dsi_panel_reset(pdata, 0);
		if (ret) {
			pr_warn("%s: Panel reset failed. rc=%d\n", __func__, ret);
			ret = 0;
		}

		if (mdss_dsi_pinctrl_set_state(ctrl_pdata, false))
			pr_debug("reset disable: pinctrl not enabled\n");
		ret = msm_dss_enable_vreg(
			ctrl_pdata->panel_power_data.vreg_config,
			ctrl_pdata->panel_power_data.num_vreg, 0);
		if (ret){
			pr_err("%s: failed to disable vregs for %s\n",
				__func__, __mdss_dsi_pm_name(DSI_PANEL_PM));
		}
		if(pinfo->aod_phy_pwr&&pinfo->aod_ulps_pwr_feature){
			mdss_dsi_panel_extra_power_lp(pdata,0);
		}

		break;
	}
	return ret;
}

