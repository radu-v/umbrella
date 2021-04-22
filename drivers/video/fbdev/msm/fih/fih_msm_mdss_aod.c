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
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/qpnp/pin.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/leds.h>
#include <linux/qpnp/pwm.h>
#include <linux/err.h>
#include <linux/string.h>

#include "../mdss_dsi.h"
#include "../mdss_mdp.h"
#include "../mdss_fb.h"

#ifdef CONFIG_TOUCHSCREEN_SIW
#include "../../../../include/linux/input/siw_touch_notify.h"
#include "../../../../fih/fih_touch.h"
extern struct fih_touch_cb touch_cb;
extern int fih_JDI_notifier(int aod_enable); //SW8-DH-JDI-double_tap-00+
#endif

#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
#include "fih_mdss_color_managerial.h"
#endif

int aod_en=0;
int previous_bl_level = 0;
int aod_feature = 0;
int blank_mode=0;
int wled_aod_set=0;
int glance_option =0;
static struct mdss_dsi_ctrl_pdata *gpdata  = NULL;
static struct mdss_dsi_ctrl_pdata *spdata  = NULL;
static int previous_blank=0;
#define VSYNC_DELAY msecs_to_jiffies(17)
static bool aod_ready=0;
static bool recovery_touch=0;
extern void mdss_dsi_panel_cmds_send(struct mdss_dsi_ctrl_pdata *ctrl,
			struct dsi_panel_cmds *pcmds, u32 flags);
extern int mdss_dsi_parse_dcs_cmds(struct device_node *np,
		struct dsi_panel_cmds *pcmds, char *cmd_key, char *link_key);

extern struct mdss_dsi_ctrl_pdata *mdss_dsi_get_ctrl(u32 ctrl_id);

int fih_get_blank_mode(void)
{
	pr_debug("***%s: Blank mode(%d)***\n", __func__,blank_mode);
	return blank_mode;
}

int fih_set_blank_mode(int mode)
{
	blank_mode = mode;
	return 0;
}

int fih_get_aod_wled_state(void)
{
	pr_debug("***%s: Is AOD enabled(%d)***\n", __func__,wled_aod_set);
	return wled_aod_set;
}

int fih_set_aod_wled_state(int enable)
{
	wled_aod_set = enable;
	return 0;
}

int fih_get_aod(void)
{
	pr_debug("***%s: Is AOD enabled(%d)***\n", __func__,aod_en);
	return aod_en;
}

int fih_set_aod(int enable)
{
	aod_en = enable;
	pr_err("***%s: AOD enabled(%d)***\n", __func__,aod_en);
	return 0;
}

unsigned int fih_get_panel_id(void)
{
	struct mdss_panel_info *pinfo;
	pinfo = &gpdata->panel_data.panel_info;

	return pinfo->panel_id;
}

bool fih_get_aod_ready(void)
{
	struct mdss_panel_info *gpinfo,*spinfo;
	gpinfo = &gpdata->panel_data.panel_info;
	spinfo = &spdata->panel_data.panel_info;

	aod_ready = gpinfo->aod_ready_on|spinfo->aod_ready_on;
	return aod_ready;

}

int fih_set_glance(int enable)
{
	if(enable >0){
		glance_option = 1;
	}else{
		glance_option = 0;
	}
	return 0;
}
int fih_get_glance(void)
{
	return glance_option;
}
//SW8-DH-AllPowerOff+[
int fih_get_aod_timeout(void)
{
	bool timeout = false;
	struct mdss_panel_info *pinfo, *sinfo;
	pinfo = &gpdata->panel_data.panel_info;
	if(pinfo != NULL)
	{
		timeout |= pinfo->aod_screen_timeout;
	}
	sinfo = &spdata->panel_data.panel_info;
	if(sinfo != NULL)
	{
		timeout |= sinfo->aod_screen_timeout;
	}

	return timeout;
}
//SW8-DH-AllPowerOff+]

int fih_get_recovery_touch(void)
{
	return recovery_touch;
}

int fih_set_recovery_touch(bool covery)
{
	recovery_touch=covery;
	return 0;
}


EXPORT_SYMBOL(fih_set_aod);
EXPORT_SYMBOL(fih_get_aod);
EXPORT_SYMBOL(fih_get_panel_id);
EXPORT_SYMBOL(fih_set_aod_wled_state);
EXPORT_SYMBOL(fih_get_aod_wled_state);
EXPORT_SYMBOL(fih_set_blank_mode);
EXPORT_SYMBOL(fih_get_blank_mode);
EXPORT_SYMBOL(fih_get_aod_ready);
EXPORT_SYMBOL(fih_set_glance);
EXPORT_SYMBOL(fih_get_glance);
EXPORT_SYMBOL(fih_get_aod_timeout);
EXPORT_SYMBOL(fih_get_recovery_touch);
EXPORT_SYMBOL(fih_set_recovery_touch);

void fih_mdss_dsi_panel_config_aod_res_properties(struct device_node *np, struct dsi_panel_timing *pt)
{
	mdss_dsi_parse_dcs_cmds(np, &pt->aod_resume_cmds,
		"qcom,mdss-dsi-aod-resume-command",
		"qcom,mdss-dsi-aod-resume-command-state");

	mdss_dsi_parse_dcs_cmds(np, &pt->aod_8color_exit_cmds,
		"qcom,mdss-dsi-aod-8color-exit-command",
		"qcom,mdss-dsi-aod-8color-exit-command-state");

	return;
}

void fih_mdss_dsi_panel_config_aod_parse_dt(struct device_node *np, struct mdss_dsi_ctrl_pdata *ctrl_pdata)
{
	mdss_dsi_parse_dcs_cmds(np, &ctrl_pdata->aod_suspend_cmds,
		"qcom,mdss-dsi-aod-suspend-command", "qcom,mdss-dsi-aod-suspend-command-state");


	mdss_dsi_parse_dcs_cmds(np, &ctrl_pdata->aod_8color_enter_cmds,
		"qcom,mdss-dsi-aod-8color-enter-command", "qcom,mdss-dsi-aod-8color-enter-command-state");
	mdss_dsi_parse_dcs_cmds(np, &ctrl_pdata->post_aod_8color_enter_cmds,
		"qcom,mdss-dsi-post-aod-8color-enter-command", "qcom,mdss-dsi-post-aod-8color-enter-command-state");

	ctrl_pdata->cmd_early_lp_exit= of_property_read_bool(np,"fih,aod-early-lp-exit");
	if(!ctrl_pdata->cmd_early_lp_exit){
		pr_err("%s: Always on display exit by framework\n", __func__);
	}else{
		pr_err("%s: Always on display exit by driver\n", __func__);
	}

	return;
}

void fih_mdss_dsi_panel_aod_exit_register(struct mdss_dsi_ctrl_pdata *ctrl, struct dsi_panel_timing *pt)
{
	ctrl->aod_resume_cmds= pt->aod_resume_cmds;
	ctrl->aod_8color_exit_cmds= pt->aod_8color_exit_cmds;
	return;
}
//LGD
int mdss_dsi_panel_LH530QH1_low_power_config(struct mdss_panel_data *pdata,int enable)
{
		struct mdss_dsi_ctrl_pdata *ctrl = NULL;
		struct mdss_panel_info *pinfo;
		struct dsi_panel_cmds *on_cmds;
		int blank=0;
		#ifdef CONFIG_TOUCHSCREEN_SIW
		int panel_mode = LCD_EVENT_LCD_MODE_U3;
		#endif

		if (pdata == NULL) {
			pr_err("%s: Invalid input data\n", __func__);
			return -EINVAL;
		}

		pinfo = &pdata->panel_info;
		ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
					panel_data);

		if (pinfo->dcs_cmd_by_left) {
			if (ctrl->ndx != DSI_CTRL_LEFT)
				goto end;
		}

		if(pinfo->aod_screen_timeout&& !enable){
			pr_debug("%s: AOD screen timeout leave\n", __func__);
			pinfo->aod_screen_timeout = 0;
			return 0;
		}

		pr_debug("%s: ctrl=%pK ndx=%d enable=%d\n", __func__, ctrl, ctrl->ndx,
			enable);
		blank = fih_get_blank_mode();

		if(enable){
			if(pinfo->aod_ready_on)
			{
				pr_debug("%s: Already initial Glance mode\n", __func__);
				msleep(200);
			}
			#ifdef CONFIG_TOUCHSCREEN_SIW
			if(ctrl->ndx== DSI_CTRL_0){
				panel_mode = LCD_EVENT_LCD_MODE_U2;
			}
			#endif

			pr_debug("%s: Always on display is enable\n", __func__);
#ifdef CONFIG_TOUCHSCREEN_SIW
			if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == LGD)){
				//SW8-DH-Double_Tap_workaround+[
				if(ctrl->ndx == DSI_CTRL_0){
				pr_debug("%s, U3 -> U2 , Step 1 : LPWG setup\n", __func__);
				siw_hal_lpwg_FIH(9, 1, 0, 1, 0);
				//SW8-DH-Double_Tap_workaround+]
				pr_debug("%s, U3 -> U2, Step 2 : Set diplay mode to U2\n", __func__);
				}
			}
#endif

			if (ctrl->aod_suspend_cmds.cmd_cnt)
					mdss_dsi_panel_cmds_send(ctrl, &ctrl->aod_suspend_cmds, CMD_REQ_COMMIT);

#ifdef CONFIG_TOUCHSCREEN_SIW
			if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == LGD)){
				if(ctrl->ndx == DSI_CTRL_0){
					pr_debug("%s , U3 -> U2, Step 3 : Change lcd_mode to U2 via notifier\n", __func__);
					siw_touch_notifier_call_chain(LCD_EVENT_LCD_MODE, (void *)&panel_mode);
				}
			}
#endif
			pinfo->aod_ready_on = 1;

		}else{
			if(!pinfo->aod_ready_on )
				goto end;

			if(blank!=FB_BLANK_UNBLANK)
			{
				pr_debug("%s: Still in low power mode\n", __func__);
				msleep(100);
				goto end;
			}
#ifdef CONFIG_TOUCHSCREEN_SIW
			if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == LGD)){
				if (ctrl->ndx == DSI_CTRL_0) {
					pr_debug(" %s U2 -> U3, Step 3 : Set diplay mode to U3\n", __func__);
				}
			}
#endif
			pr_debug("%s: Always on display is disable\n", __func__);
			on_cmds = &ctrl->aod_resume_cmds;
			#ifdef CONFIG_TOUCHSCREEN_SIW
			if(ctrl->ndx== DSI_CTRL_0){
				panel_mode = LCD_EVENT_LCD_MODE_U3;
			}
			#endif

			if (on_cmds->cmd_cnt){
//				msleep(VSYNC_DELAY);
				mdss_dsi_panel_cmds_send(ctrl, on_cmds, CMD_REQ_COMMIT);
			}

#ifdef CONFIG_FIH_NB1
#ifdef CONFIG_TOUCHSCREEN_SIW
			if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == LGD)){
				if (ctrl->ndx == DSI_CTRL_0) {
					pr_debug("%s U2 -> U3, Step 4 : Change lcd_mode to U3 via notifier \n", __func__);
					siw_touch_notifier_call_chain(LCD_EVENT_LCD_MODE, (void *)&panel_mode);
					pr_debug("%s: dsi_on from panel low power state\n", __func__);
					ctrl->tp_state=4;
				}
			}
#endif
#endif


			pinfo->aod_ready_on = 0;
		}
	/* Any panel specific low power commands/config */
	pr_debug("%s:-\n", __func__);
end:
	if(ctrl->ndx== DSI_CTRL_1)
		previous_blank = blank;
	return 0;
}

//LGD pOLED
int mdss_dsi_panel_D53G6EA8151_low_power_config(struct mdss_panel_data *pdata,int enable)
{
		struct mdss_dsi_ctrl_pdata *ctrl = NULL;
		struct mdss_panel_info *pinfo;
		struct dsi_panel_cmds *on_cmds;
		int blank=0;

		if (pdata == NULL) {
			pr_err("%s: Invalid input data\n", __func__);
			return -EINVAL;
		}

		pinfo = &pdata->panel_info;
		ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
					panel_data);

		if (pinfo->dcs_cmd_by_left) {
			if (ctrl->ndx != DSI_CTRL_LEFT)
				goto end;
		}
		pr_info("%s: ctrl=%pK ndx=%d enable=%d\n", __func__, ctrl, ctrl->ndx,
			enable);
		blank = fih_get_blank_mode();

		if(enable){
			if(pinfo->aod_ready_on)
			{
				pr_info("%s: Already initial Glance mode\n", __func__);
				msleep(200);
			}

			pr_info("%s: Always on display is enable\n", __func__);

			if (ctrl->aod_suspend_cmds.cmd_cnt)
					mdss_dsi_panel_cmds_send(ctrl, &ctrl->aod_suspend_cmds, CMD_REQ_COMMIT);

			pinfo->aod_ready_on = 1;

		}else{
			if(!pinfo->aod_ready_on )
				goto end;

			if(blank!=FB_BLANK_UNBLANK)
			{
				pr_info("%s: Still in low power mode\n", __func__);
				msleep(100);
				goto end;
			}

			pr_info("%s: Always on display is disable\n", __func__);
			on_cmds = &ctrl->aod_resume_cmds;
			pinfo->aod_screen_timeout=0;

			if (on_cmds->cmd_cnt){
				mdss_dsi_panel_cmds_send(ctrl, on_cmds, CMD_REQ_COMMIT);
			}

			pinfo->aod_ready_on = 0;
		}
	/* Any panel specific low power commands/config */
	pr_info("%s:-\n", __func__);
end:
	if(ctrl->ndx== DSI_CTRL_1)
		previous_blank = blank;
	return 0;
}

/*JDI Panel*/
#define PANEL_REG_ADDR_LEN 8
static char aod_reg[2] = {0x56, 0x00};
static struct dsi_cmd_desc aod_read_cmd = {
	{DTYPE_DCS_READ, 1, 0, 1, 5, sizeof(aod_read_cmd)},
	aod_reg
};

int oem_dsi_panel_cmd_read(struct mdss_dsi_ctrl_pdata *ctrl, char cmd0,
		char cmd1, void (*fxn)(int), char *rbuf, int len)
{
	struct dcs_cmd_req cmdreq;
	struct mdss_panel_info *pinfo;

	pinfo = &(ctrl->panel_data.panel_info);
	if (pinfo->dcs_cmd_by_left) {
		if (ctrl->ndx != DSI_CTRL_LEFT)
			return -EINVAL;
	}

	aod_reg[0] = cmd0;
	aod_reg[1] = cmd1;
	memset(&cmdreq, 0, sizeof(cmdreq));
	cmdreq.cmds = &aod_read_cmd;
	cmdreq.cmds_cnt = 1;
	cmdreq.flags = CMD_REQ_RX | CMD_REQ_COMMIT;
	cmdreq.rlen = len;
	cmdreq.rbuf = rbuf;
	cmdreq.cb = fxn; /* call back */
	/*
	 * blocked here, until call back called
	 */

	return mdss_dsi_cmdlist_put(ctrl, &cmdreq);
}

static int mdss_dsi_panel_LPM053A348A_low_power_config(struct mdss_panel_data *pdata,
	int enable)
{
	struct mdss_dsi_ctrl_pdata *ctrl = NULL;
//	struct msm_fb_data_type *mfd=NULL;
	struct mdss_panel_info *pinfo;
	char *rx_buf;
	char test1 = 0x0F;
	char test2 = 0x90;
	int blank=0;
	struct dsi_panel_cmds *on_cmds;

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return -EINVAL;
	}

	pinfo = &pdata->panel_info;
	ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);

	if (pinfo->dcs_cmd_by_left) {
		if (ctrl->ndx != DSI_CTRL_LEFT)
			return -EINVAL;
	}

	if(pinfo->aod_screen_timeout && !enable){
		pr_info("%s: AOD screen timeout leave\n", __func__);
		pinfo->aod_screen_timeout = 0;
		return 0;
	}

	blank = fih_get_blank_mode();

	if(enable){
		pr_err("%s:  ndx=%d enable=%d\n", __func__, ctrl->ndx,enable);

		if(pinfo->aod_ready_on)
		{
			pr_info("%s: Already initial Glance mode\n", __func__);
			msleep(200);
			goto end;
		}
		on_cmds = &ctrl->aod_8color_enter_cmds;

		pr_info("%s: Always on display is enable\n", __func__);

		if (on_cmds->cmd_cnt)
			mdss_dsi_panel_cmds_send(ctrl, on_cmds, CMD_REQ_COMMIT);

		//****Please read 0x56 register value,and store only the low order 4bit of the 0x56 read value.
		//After that,Please write 0x56 register Combining of "9h" in the upper 4bit
		//and "read value" in the lower 4bit. ex)  Read value!G0x8A  Write value!G0x9A
		rx_buf = kzalloc(PANEL_REG_ADDR_LEN, GFP_KERNEL);

		oem_dsi_panel_cmd_read(ctrl, aod_reg[0], aod_reg[1],
												NULL, rx_buf, 1);

		pr_debug("%s:rx_buf[0] = 0x%x\n", __func__, rx_buf[0]);
		pr_debug("%s:rx_buf[1] = 0x%x\n", __func__, rx_buf[1]);
		pr_debug("%s:on_cmds->buf[8]=((rx_buf[0] & test1) | test2)=0x%x\n", __func__, on_cmds->buf[8]);

		on_cmds = &ctrl->post_aod_8color_enter_cmds;
		pr_debug("%s:on_cmds->buf[8]=((rx_buf[0] & test1) | test2)=0x%x\n", __func__, on_cmds->buf[8]);

		on_cmds->buf[8] = ((rx_buf[0] & test1) | test2);
		pr_debug("%s:on_cmds->buf[8]=((rx_buf[0] & test1) | test2)=0x%x\n", __func__, on_cmds->buf[8]);

		if (on_cmds->cmd_cnt)
		{
			msleep(VSYNC_DELAY);	/* wait for a vsync passed */
			mdss_dsi_panel_cmds_send(ctrl, on_cmds, CMD_REQ_COMMIT);
		}
		kfree(rx_buf);
		pinfo->aod_ready_on = 1;
		#ifdef CONFIG_TOUCHSCREEN_SIW
		if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == JDI))
			fih_JDI_notifier(pinfo->aod_ready_on);//SW8-DH-JDI-double_tap-00+
		#endif

	}else{
		if(!pinfo->aod_ready_on )
			goto end;
		if(blank!=FB_BLANK_UNBLANK)
		{
			pr_info("%s: Still in low power mode\n", __func__);
			msleep(100);
			goto end;
		}
		on_cmds =&ctrl->aod_8color_exit_cmds;
		pinfo->aod_screen_timeout=0;

		pr_err("%s: Always on display is disable\n", __func__);

		if (on_cmds->cmd_cnt){
			msleep(VSYNC_DELAY);	/* wait for a vsync passed */
			mdss_dsi_panel_cmds_send(ctrl, on_cmds, CMD_REQ_COMMIT);
		}
		if (pinfo->dcs_cmd_by_left) {
			//Wait for framework fill image
			msleep(50);
		}
		pinfo->aod_ready_on = 0;
		#ifdef CONFIG_TOUCHSCREEN_SIW
                if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == JDI))
			fih_JDI_notifier(pinfo->aod_ready_on);//SW8-DH-JDI-double_tap-00+
		#endif

	}
	pr_info("%s:-\n", __func__);

end:
	if(ctrl->ndx== DSI_CTRL_1)
		previous_blank = blank;
	return 0;


}

void fih_mdss_lp_config(struct mdss_panel_data *pdata,int enable,int ndx)
{
	struct mdss_dsi_ctrl_pdata *ctrl_pdata = NULL;
	struct mdss_panel_info *pinfo;
	ctrl_pdata = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);

	pinfo = &pdata->panel_info;

	if(!ctrl_pdata->cmd_early_lp_exit && !enable)
	{
		return;
	}

	if(!fih_get_glance()){
		pr_info("%s, the panel is not enable glance\n",__func__);
		fih_set_recovery_touch(1);
		return;
	}

	pr_info("%s, mdss_dsi%d\n",__func__,ndx);
	if(!pinfo->aod_ready_on)
	{
		//If it is not FIH AP trigger Doze low power mode reject initial code setting
		pr_info("%s, aod ready is %d, enable state %d \n",__func__,pinfo->aod_ready_on,enable);
		if(!fih_get_glance()){
			pr_info("%s, mdss It is not Doze AP \n",__func__);
			return;
		}
	}
	if(pinfo->panel_id==LGD_LH530QH1_WQXGA_CMD_PANEL)
		mdss_dsi_panel_LH530QH1_low_power_config(pdata, enable);
	else if(pinfo->panel_id==JDI_LPM053A466A_WQXGA_CMD_PANEL)
		mdss_dsi_panel_LPM053A348A_low_power_config(pdata, enable);
	else if(pinfo->panel_id==LGD_D53G6EA8151_POLED_WQXGA_CMD_PANEL)
		mdss_dsi_panel_D53G6EA8151_low_power_config(pdata, enable);
	else
		pr_err("%s, the panel don't support Doze mode\n",__func__);

	if(enable){
		pinfo->aod_screen_timeout=0;
	}else{
#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
		mdss_dsi_color_mode_restore(ctrl_pdata);
#endif
	}

	return;
}
void mdss_lp_early_config(struct mdss_panel_data *pdata)
{
	struct mdss_dsi_ctrl_pdata *ctrl_pdata = NULL;
	struct mdss_panel_info *pinfo;
	ctrl_pdata = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);
	pinfo = &pdata->panel_info;

	if (ctrl_pdata->low_power_config&& ctrl_pdata->cmd_early_lp_exit){
		pr_info("%s: dsi_unblank with panel always on\n", __func__);
		ctrl_pdata->low_power_config(pdata, false);
	}
	return;
}

void mdss_aod_resume_config(struct mdss_panel_data *pdata)
{
	struct mdss_dsi_ctrl_pdata *ctrl = NULL;
	struct mdss_panel_data *adata=NULL;
	struct mdss_panel_info *pinfo,*dsi1pinfo;

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return;
	}

	pinfo = &pdata->panel_info;
	ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);

	if(!fih_get_glance()){
		pr_info("%s, the panel is not enable glance\n",__func__);
		return;
	}


	if(pinfo->aod_ready_on){
		pr_info("%s, Brfore is aod suspend\n", __func__);
		if(pinfo->panel_id==LGD_LH530QH1_WQXGA_CMD_PANEL){
			pinfo->aod_ready_on=0;
			if (ctrl->aod_resume_cmds.cmd_cnt)
				mdss_dsi_panel_cmds_send(ctrl, &ctrl->aod_resume_cmds, CMD_REQ_COMMIT);
		}else if(pinfo->panel_id==JDI_LPM053A466A_WQXGA_CMD_PANEL){
			pinfo->aod_ready_on=0;
			if (ctrl->aod_8color_exit_cmds.cmd_cnt)
				mdss_dsi_panel_cmds_send(ctrl, &ctrl->aod_8color_exit_cmds, CMD_REQ_COMMIT);
			#ifdef CONFIG_TOUCHSCREEN_SIW
	                if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == JDI))
				fih_JDI_notifier(pinfo->aod_ready_on);//SW8-DH-JDI-double_tap-00+
			#endif

		}else if(pinfo->panel_id==LGD_D53G6EA8151_POLED_WQXGA_CMD_PANEL){
			pinfo->aod_ready_on=0;
			if (ctrl->aod_resume_cmds.cmd_cnt)
				mdss_dsi_panel_cmds_send(ctrl, &ctrl->aod_resume_cmds, CMD_REQ_COMMIT);
		}
		pinfo->aod_screen_timeout=1;

		/*As dual dsi and command by left set up screen timeout in dsi1 structure*/
		if (pinfo->dcs_cmd_by_left) {
			adata = &spdata->panel_data;
			dsi1pinfo = &adata->panel_info;
			dsi1pinfo->aod_screen_timeout =1;
		}
	}
	return;
}

void mdss_cleaup_aod_flag(struct mdss_panel_data *pdata)
{
	struct mdss_dsi_ctrl_pdata *ctrl = NULL;
	struct mdss_panel_info *pinfo;

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return;
	}

	pinfo = &pdata->panel_info;
	ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);

	pinfo->aod_ready_on=0;
	pinfo->aod_screen_timeout=0;

	return;
}
void mdss_bl_backup(struct mdss_panel_data *pdata,int level)
{
	struct mdss_dsi_ctrl_pdata *ctrl = NULL;
	struct mdss_panel_info *pinfo;

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return;
	}

	pinfo = &pdata->panel_info;
	ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
							panel_data);
	pinfo->aod_bl_backup=level;
	return;
}

int fih_set_low_power_mode(int enable)
{
#if 0
	struct mdss_panel_data *adata=NULL;
	struct mdss_panel_info *pinfo;
	int i =0,j=0,k=0;
	int bl_restore=0;
	if(!aod_feature){
			pr_info("Not support AOD feature\n");
			return 0;
	}
	pr_info("%s, the panel %s Doze mode\n",__func__,enable?"enter":"leave");

	if(!fih_get_glance()){
		pr_info("%s, the panel is not enable glance\n",__func__);
		return 0;
	}
	for(i=0;i<DSI_CTRL_MAX;i++)
	{
		if(i==DSI_CTRL_0){
			if(gpdata==NULL){
				pr_debug("%s, NULL BUS%d\n",__func__,i);
				continue;
			}
			adata = &gpdata->panel_data;
			pinfo = &adata->panel_info;
		}else{
			if(spdata==NULL){
				pr_debug("%s, NULL BUS%d\n",__func__,i);
				continue;
			}
			adata = &spdata->panel_data;
			pinfo = &adata->panel_info;
		}
		/*As leave AOD, disable backlight to avoid flicker. And control backlight by one porting only*/
		if(!enable && adata!=NULL &&j==0 && pinfo->aod_ready_on){
			bl_restore=pinfo->aod_bl_backup;
			pr_info("%s,mdss old backlight,level(%d)+\n",__func__,bl_restore);
			if(bl_restore!=0){
				adata->set_backlight(adata, 0);
			}
			j++;
		}
		if(pinfo->panel_id==LGD_LH530QH1_WQXGA_CMD_PANEL)
			mdss_dsi_panel_LH530QH1_low_power_config(adata, enable);
		else if(pinfo->panel_id==JDI_LPM053A466A_WQXGA_CMD_PANEL)
			mdss_dsi_panel_LPM053A348A_low_power_config(adata, enable);
		else if(pinfo->panel_id==LGD_D53G6EA8151_POLED_WQXGA_CMD_PANEL)
			mdss_dsi_panel_D53G6EA8151_low_power_config(adata, enable);
		else
			pr_err("%s, the panel don't support Doze mode\n",__func__);

		if(bl_restore!=0&& adata!=NULL&&k==0 ){
			pr_info("%s,mdss restore backlight,level(%d)\n",__func__,bl_restore);
			adata->set_backlight(adata, bl_restore);
			k++;
		}
	}
#endif
	return 0;

}
EXPORT_SYMBOL(fih_set_low_power_mode);
int mdss_set_tp_event(struct mdss_panel_data *pdata,int event)
{
	struct mdss_dsi_ctrl_pdata *ctrl = NULL;
	struct mdss_panel_info *pinfo;
#ifdef CONFIG_FIH_NB1
#ifdef CONFIG_TOUCHSCREEN_SIW
	int panel_mode=LCD_EVENT_LCD_MODE_U3;
#endif
#endif

	if (pdata == NULL) {
		pr_err("%s: Invalid input data\n", __func__);
		return -EINVAL;
	}

	pinfo = &pdata->panel_info;
	ctrl = container_of(pdata, struct mdss_dsi_ctrl_pdata,
				panel_data);

	if(pinfo->panel_id==LGD_LH530QH1_WQXGA_CMD_PANEL){
#ifdef CONFIG_FIH_NB1
#ifdef CONFIG_TOUCHSCREEN_SIW
	switch(event)
	{
	case TP_EVENT_REINIT:
		if ((touch_cb.touch_vendor_id_read != NULL) &&(touch_cb.touch_vendor_id_read() == LGD)){
			if (ctrl->ndx == DSI_CTRL_0) {
				pr_info("%s U2 -> U3, Step 4 : Change lcd_mode to U3 via notifier \n", __func__);
				siw_touch_notifier_call_chain(LCD_EVENT_LCD_MODE, (void *)&panel_mode);
				pr_debug("%s: dsi_on from panel low power state\n", __func__);
				ctrl->tp_state=4;
			}
		}
		break;
	default:
		pr_err("%s: Unknow TP event %d\n", __func__,event);
		break;
	}
#endif
#endif
	}
	return 0;
}
EXPORT_SYMBOL(mdss_set_tp_event);

int fih_get_low_power_mode(void)
{
	struct mdss_panel_info *pinfo;
	pinfo = &gpdata->panel_data.panel_info;
	if(!aod_feature){
		pr_info("Not support AOD feature");
		return 0;
	}
	return pinfo->aod_ready_on;

}
EXPORT_SYMBOL(fih_get_low_power_mode);

void fih_mdss_dsi_aod_panel_init(struct platform_device *pdev,struct mdss_dsi_ctrl_pdata *ctrl_pdata,u32 ctrl_id)
{
	if(ctrl_id==DSI_CTRL_0)
	{
		gpdata = devm_kzalloc(&pdev->dev,
					  sizeof(struct mdss_dsi_ctrl_pdata),
					  GFP_KERNEL);
		if (!gpdata) {
			pr_err("%s: FAILED: cannot alloc dsi ctr - gpdata\n",__func__);
			goto error_no_mem;
		}
		gpdata = mdss_dsi_get_ctrl(ctrl_id);
		platform_set_drvdata(pdev, gpdata);


	}else if(ctrl_id==DSI_CTRL_1)
	{
		spdata = devm_kzalloc(&pdev->dev,
					  sizeof(struct mdss_dsi_ctrl_pdata),
					  GFP_KERNEL);
		if (!spdata) {
			pr_err("%s: FAILED: cannot alloc dsi ctr - spdata\n",__func__);
			goto error_no_mem;
		}
		spdata = mdss_dsi_get_ctrl(ctrl_id);
		platform_set_drvdata(pdev, spdata);

	}else
	{
		pr_err("%s: Out of bus number(%d)\n",__func__,ctrl_id);
		return;
	}

	pr_info("\n\n***%s, aod_feature = %d ***\n\n", __func__, aod_feature);
	if(aod_feature>=DSI_CTRL_MAX){
		pr_info("\n\n***%s, aod_feature, probe ok return  ***\n\n", __func__);
		return;
	}

	if(((ctrl_pdata->aod_resume_cmds.cmd_cnt) &&
		(ctrl_pdata->aod_suspend_cmds.cmd_cnt))||
		((ctrl_pdata->aod_8color_enter_cmds.cmd_cnt) &&
		(ctrl_pdata->aod_8color_exit_cmds.cmd_cnt))){
		aod_feature++;
	}
	pr_info("\n\n***%s, aod_feature = %d ***\n\n", __func__, aod_feature);
	pr_info("\n\n***%s, probe pass return \n\n", __func__);
	return;
error_no_mem:
	if(ctrl_id==DSI_CTRL_0)
		devm_kfree(&pdev->dev, gpdata);
	else if(ctrl_id==DSI_CTRL_1)
		devm_kfree(&pdev->dev, spdata);
	return;
}

