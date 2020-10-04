#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <fih/hwid.h>
#include <linux/seq_file.h>


static int fih_info_proc_open_project_show(struct seq_file *m, void *v)
{
	char msg[8];

	switch (fih_hwid_fetch(FIH_HWID_PRJ)) {
		case FIH_PRJ_NB1: strcpy(msg, "NB1"); break;
		default: strcpy(msg, "N/A"); break;
	}
	seq_printf(m, "%s\n", msg);

	return 0;
}

static int fih_info_proc_open_hw_rev_show(struct seq_file *m, void *v)
{
	char msg[8];

	switch (fih_hwid_fetch(FIH_HWID_REV)) {
		case FIH_REV_EVB:  strcpy(msg, "EVB"); break;
		case FIH_REV_EVB1:  strcpy(msg, "EVB1"); break;
		case FIH_REV_EVB2:  strcpy(msg, "EVB2"); break;
		case FIH_REV_EVT:  strcpy(msg, "1.0"); break;
		case FIH_REV_EVT0_5: strcpy(msg, "1.0.5"); break;
		case FIH_REV_EVT1:  strcpy(msg, "1.1"); break;
		case FIH_REV_EVT1_1:  strcpy(msg, "1.1.1"); break;
		case FIH_REV_EVT1_2:  strcpy(msg, "1.1.2"); break;
		case FIH_REV_EVT1_5:  strcpy(msg, "1.1.5"); break;
		case FIH_REV_DVT:  strcpy(msg, "2.0"); break;
		case FIH_REV_DVT1:  strcpy(msg, "2.1"); break;
		case FIH_REV_DVT1_5:  strcpy(msg, "2.1.5"); break;
		case FIH_REV_DVT2: strcpy(msg, "2.2"); break;
		case FIH_REV_DVT2_5: strcpy(msg, "2.2.5"); break;
		case FIH_REV_DVT3: strcpy(msg, "2.3"); break;
		case FIH_REV_PVT:  strcpy(msg, "3.0"); break;
		case FIH_REV_PVT1:  strcpy(msg, "3.1"); break;
		case FIH_REV_PVT2: strcpy(msg, "3.2"); break;
		case FIH_REV_MP:   strcpy(msg, "5.0"); break;
		case FIH_REV_MP1:   strcpy(msg, "5.1"); break;
		case FIH_REV_MP2:  strcpy(msg, "5.2"); break;
		default: strcpy(msg, "N/A"); break;
	}
	seq_printf(m, "%s\n", msg);

	return 0;
}

static int fih_info_proc_open_rf_band_show(struct seq_file *m, void *v)
{
	char msg[128];

	switch (fih_hwid_fetch(FIH_HWID_RF)) {
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^L_1_2_3_4_5_7_8_20_28_38_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^L_1_2_3_4_5_7_8_20_28_38_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_28_38_39_40_41:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^C_0^T_34_39^L_1_2_3_4_5_7_8_28_38_39_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_T_34_39_L_1_2_3_4_5_7_8_20_28_38_39_40_41:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^T_34_39^L_1_2_3_4_5_7_8_20_28_38_39_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_4_5_8^L_1_2_3_4_5_7_8_20_28_38_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_4_5_8^L_1_2_3_4_5_7_8_20_28_38_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_12_13_17_20_28_38_39_40_41_66:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^C_0^T_34_39^L_1_2_3_4_5_7_8_12_13_17_20_28_38_39_40_41_66"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_12_13_17_20_28_38_39_40_41_66_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^C_0^T_34_39^L_1_2_3_4_5_7_8_12_13_17_20_28_38_39_40_41_66"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_20_28_34_38_39_40_41_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^C_0^T_34_39^L_1_2_3_4_5_7_8_20_28_34_38_39_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_66_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_66"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_SS:
			strcpy(msg, "G_850_900_1800_1900^W_1_2_4_5_8^L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41"); break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_T_34_39_L_1_3_5_7_8_28_34_38_39_40_41: /* F11 */
			strcpy(msg, "G_850_900_1800_1900^W_1_2_5_8^T_34_39^L_1_3_5_7_8_28_34_38_39_40_41"); break;
		/* NO BAND */
		case FIH_RF_NONE: strcpy(msg, "NONE"); break;
		default: strcpy(msg, "UNKNOWN\n"); break;
	}
	seq_printf(m, "%s\n", msg);

	return 0;
}

static int fih_info_proc_open_hwmodel_show(struct seq_file *m, void *v)
{
	char msg[8];

	switch (fih_hwid_fetch(FIH_HWID_PRJ)) {
		case FIH_PRJ_NB1:
			if (fih_hwid_fetch(FIH_HWID_RF) == FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_T_34_39_L_1_2_3_4_5_7_8_20_28_38_39_40_41)
				strcpy(msg, "B1C");
			else
				strcpy(msg, "NB1");
			break;
		default: strcpy(msg, "N/A"); break;
	}

	/* special case for same skuid to different customer */
	//strcat(msg, "_XX");

	seq_printf(m, "%s\n", msg);

	return 0;
}

static int fih_info_proc_open_hwcfg_show(struct seq_file *m, void *v)
{
	struct st_hwid_table tb;

	fih_hwid_read(&tb);
	/*
		mpp: r1, r2, r3
		info: prj, rev, rf
		device tree: dtm, dtn
		driver: btn, uart
	*/
	seq_printf(m, "r1=%d\nr2=%d\nr3=%d\nprj=%d\nrev=%d\nrf=%d\ndtm=%d\ndtn=%d\nbtn=%d\nuart=%d\n\n",
		tb.r1, tb.r2, tb.r3, tb.prj, tb.rev, tb.rf, tb.dtm, tb.dtn, tb.btn, tb.uart);

	return 0;
}

static int fih_info_proc_open_simslot_show(struct seq_file *m, void *v)
{
	int slot = 0;

	switch (fih_hwid_fetch(FIH_HWID_RF)) {
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41: slot = 2; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_28_38_39_40_41: slot = 2; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_T_34_39_L_1_2_3_4_5_7_8_20_28_38_39_40_41: slot = 2; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41: slot = 2; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_12_13_17_20_28_38_39_40_41_66_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_12_13_17_20_28_38_39_40_41_66: slot = 2; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_C_0_T_34_39_L_1_2_3_4_5_7_8_20_28_34_38_39_40_41_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_66_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_12_13_17_20_28_38_40_41_SS: slot = 1; break;
		case FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_T_34_39_L_1_3_5_7_8_28_34_38_39_40_41: slot = 2; break; /* F11 */
		default: slot = 0; break;
	}
	seq_printf(m, "%d\n", slot);

	return 0;
}

static int fih_info_proc_open_module_show(struct seq_file *m, void *v)
{
	char msg[8];

	switch (fih_hwid_fetch(FIH_HWID_PRJ)) {
		case FIH_PRJ_NB1: strcpy(msg, "NB1"); break;
		default: strcpy(msg, "N/A"); break;
	}

	seq_printf(m, "%s\n", msg);

	return 0;
}

static int fih_info_proc_read_fqc_xml_show(struct seq_file *m, void *v)
{
	if(fih_hwid_fetch(FIH_HWID_PRJ)==FIH_PRJ_NB1) {
		if(fih_hwid_fetch(FIH_HWID_RF)==FIH_BAND_G_850_900_1800_1900_W_1_2_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41_SS ||
		   fih_hwid_fetch(FIH_HWID_RF)==FIH_BAND_G_850_900_1800_1900_W_1_2_4_5_8_L_1_2_3_4_5_7_8_20_28_38_40_41_SS) {
			seq_printf(m, "system/etc/fqc_NB1_1.xml\n");
		}else {
			seq_printf(m, "system/etc/fqc_NB1_2.xml\n");
		}
	}
	else if(fih_hwid_fetch(FIH_HWID_PRJ)==FIH_PRJ_A1N) {
		seq_printf(m, "system/etc/fqc_A1N.xml\n");
	}
	else {
		seq_printf(m, "system/etc/fqc.xml\n");
	}
	return 0;
}

static int fih_info_proc_open_project(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_project_show, NULL);
}

static int fih_info_proc_open_hw_rev(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_hw_rev_show, NULL);
}

static int fih_info_proc_open_rf_band(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_rf_band_show, NULL);
}

static int fih_info_proc_open_hwmodel(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_hwmodel_show, NULL);
}

static int fih_info_proc_open_hwcfg(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_hwcfg_show, NULL);
}

static int fih_info_proc_open_simslot(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_simslot_show, NULL);
}

static int fih_info_proc_open_module(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_open_module_show, NULL);
}

static int fqc_xml_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, fih_info_proc_read_fqc_xml_show, NULL);
};

/* This structure gather "function" that manage the /proc file
 */
static const struct file_operations project_file_ops = {
	.owner   = THIS_MODULE,
	.open	 = fih_info_proc_open_project,
	.read    = seq_read
};

static const struct file_operations hw_rev_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fih_info_proc_open_hw_rev,
	.read    = seq_read
};

static const struct file_operations rf_band_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fih_info_proc_open_rf_band,
	.read    = seq_read
};

static const struct file_operations hwmodel_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fih_info_proc_open_hwmodel,
	.read    = seq_read
};

static const struct file_operations hwcfg_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fih_info_proc_open_hwcfg,
	.read    = seq_read
};

static const struct file_operations simslot_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fih_info_proc_open_simslot,
	.read    = seq_read
};

static const struct file_operations module_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fih_info_proc_open_module,
	.read    = seq_read
};

static struct file_operations fqc_xml_file_ops = {
	.owner   = THIS_MODULE,
	.open    = fqc_xml_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release
};

static int __init fih_info_init(void)
{

	if (proc_create("devmodel", 0, NULL, &project_file_ops) == NULL) {
		pr_err("fail to create proc/devmodel\n");
	}

	if (proc_create("baseband", 0, NULL, &hw_rev_file_ops) == NULL) {
		pr_err("fail to create proc/baseband\n");
	}

	if (proc_create("bandinfo", 0, NULL, &rf_band_file_ops) == NULL) {
		pr_err("fail to create proc/bandinfo\n");
	}

	if (proc_create("hwmodel", 0, NULL, &hwmodel_file_ops) == NULL) {
		pr_err("fail to create proc/hwmodel\n");
	}

	if (proc_create("hwcfg", 0, NULL, &hwcfg_file_ops) == NULL) {
		pr_err("fail to create proc/hwcfg\n");
	}

	if (proc_create("SIMSlot", 0, NULL, &simslot_file_ops) == NULL) {
		pr_err("fail to create proc/SIMSlot\n");
	}

	if (proc_create("MODULE", 0, NULL, &module_file_ops) == NULL) {
		pr_err("fail to create proc/MODULE\n");
	}

	if (proc_create("fqc_xml", 0, NULL, &fqc_xml_file_ops) == NULL) {
		pr_err("fail to create proc/fqc_xml\n");
	}

	return (0);
}

static void __exit fih_info_exit(void)
{

	remove_proc_entry("devmodel", NULL);
	remove_proc_entry("baseband", NULL);
	remove_proc_entry("bandinfo", NULL);
	remove_proc_entry("hwmodel", NULL);
	remove_proc_entry("hwcfg", NULL);
	remove_proc_entry("SIMSlot", NULL);
	remove_proc_entry("MODULE", NULL);
	remove_proc_entry("fqc_xml", NULL);
}

module_init(fih_info_init);
module_exit(fih_info_exit);
