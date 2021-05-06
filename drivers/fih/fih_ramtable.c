#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <fih/share/e2p.h>
#include <linux/seq_file.h>
#include "fih_ramtable.h"

static int fih_modem_rf_nv_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_MODEM_RF_NV_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_MODEM_RF_NV_BASE, FIH_MODEM_RF_NV_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_MODEM_RF_NV_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_MODEM_RF_NV_SIZE);
	kfree(block);

	return 0;
}

static int fih_modem_cust_nv_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_MODEM_CUST_NV_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_MODEM_CUST_NV_BASE, FIH_MODEM_CUST_NV_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_MODEM_CUST_NV_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_MODEM_CUST_NV_SIZE);
	kfree(block);

	return 0;
}

static int fih_modem_default_nv_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_MODEM_DEFAULT_NV_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_MODEM_DEFAULT_NV_BASE, FIH_MODEM_DEFAULT_NV_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_MODEM_DEFAULT_NV_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_MODEM_DEFAULT_NV_SIZE);
	kfree(block);

	return 0;
}

static int fih_modem_log_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_MODEM_LOG_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_MODEM_LOG_BASE, FIH_MODEM_LOG_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_MODEM_LOG_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_MODEM_LOG_SIZE);
	kfree(block);

	return 0;
}

static int fih_last_alog_main_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LAST_ALOG_MAIN_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LAST_ALOG_MAIN_BASE, FIH_LAST_ALOG_MAIN_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LAST_ALOG_MAIN_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LAST_ALOG_MAIN_SIZE);
	kfree(block);

	return 0;
}

static int fih_last_alog_events_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LAST_ALOG_EVENTS_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LAST_ALOG_EVENTS_BASE, FIH_LAST_ALOG_EVENTS_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LAST_ALOG_EVENTS_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LAST_ALOG_EVENTS_SIZE);
	kfree(block);

	return 0;
}

static int fih_last_alog_radio_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LAST_ALOG_RADIO_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LAST_ALOG_RADIO_BASE, FIH_LAST_ALOG_RADIO_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LAST_ALOG_RADIO_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LAST_ALOG_RADIO_SIZE);
	kfree(block);

	return 0;
}

static int fih_last_alog_system_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LAST_ALOG_SYSTEM_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LAST_ALOG_SYSTEM_BASE, FIH_LAST_ALOG_SYSTEM_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LAST_ALOG_SYSTEM_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LAST_ALOG_SYSTEM_SIZE);
	kfree(block);

	return 0;
}

static int fih_last_kmsg_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LAST_KMSG_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LAST_KMSG_BASE, FIH_LAST_KMSG_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LAST_KMSG_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LAST_KMSG_SIZE);
	kfree(block);

	return 0;
}

static int fih_last_blog_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LAST_BLOG_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LAST_BLOG_BASE, FIH_LAST_BLOG_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LAST_BLOG_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LAST_BLOG_SIZE);
	kfree(block);

	return 0;
}

static int fih_blog_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_BLOG_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_BLOG_BASE, FIH_BLOG_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_BLOG_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_BLOG_SIZE);
	kfree(block);

	return 0;
}

static int fih_hwid_hwcfg_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_HWID_HWCFG_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_HWID_HWCFG_BASE, FIH_HWID_HWCFG_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_HWID_HWCFG_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_HWID_HWCFG_SIZE);
	kfree(block);

	return 0;
}

static int fih_secboot_devinfo_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SECBOOT_DEVINFO_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SECBOOT_DEVINFO_BASE, FIH_SECBOOT_DEVINFO_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SECBOOT_DEVINFO_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SECBOOT_DEVINFO_SIZE);
	kfree(block);

	return 0;
}

static int fih_secboot_unlock_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SECBOOT_UNLOCK_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SECBOOT_UNLOCK_BASE, FIH_SECBOOT_UNLOCK_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SECBOOT_UNLOCK_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SECBOOT_UNLOCK_SIZE);
	kfree(block);

	return 0;
}

static int fih_sutinfo_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SUTINFO_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SUTINFO_BASE, FIH_SUTINFO_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SUTINFO_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SUTINFO_SIZE);
	kfree(block);

	return 0;
}

static int fih_bset_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_BSET_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_BSET_BASE, FIH_BSET_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_BSET_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_BSET_SIZE);
	kfree(block);

	return 0;
}

static int fih_bat_id_adc_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_BAT_ID_ADC_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_BAT_ID_ADC_BASE, FIH_BAT_ID_ADC_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_BAT_ID_ADC_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_BAT_ID_ADC_SIZE);
	kfree(block);

	return 0;
}

static int fih_apr_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_APR_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_APR_BASE, FIH_APR_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_APR_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_APR_SIZE);
	kfree(block);

	return 0;
}

static int fih_mem_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_MEM_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_MEM_BASE, FIH_MEM_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_MEM_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_MEM_SIZE);
	kfree(block);

	return 0;
}

static int fih_e2p_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_E2P_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_E2P_BASE, FIH_E2P_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_E2P_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_E2P_SIZE);
	kfree(block);

	return 0;
}

static int fih_cda_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_CDA_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_CDA_BASE, FIH_CDA_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_CDA_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_CDA_SIZE);
	kfree(block);

	return 0;
}

static int fih_note_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_NOTE_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_NOTE_BASE, FIH_NOTE_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_NOTE_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_NOTE_SIZE);
	kfree(block);

	return 0;
}

static int fih_hwcfg_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_HWCFG_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_HWCFG_BASE, FIH_HWCFG_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_HWCFG_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_HWCFG_SIZE);
	kfree(block);

	return 0;
}

static int fih_fver_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_FVER_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_FVER_BASE, FIH_FVER_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_FVER_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_FVER_SIZE);
	kfree(block);

	return 0;
}

static int fih_sensordata_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SENSORDATA_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SENSORDATA_BASE, FIH_SENSORDATA_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SENSORDATA_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SENSORDATA_SIZE);
	kfree(block);

	return 0;
}

static int fih_lcmdata_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_LCMDATA_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_LCMDATA_BASE, FIH_LCMDATA_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_LCMDATA_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_LCMDATA_SIZE);
	kfree(block);

	return 0;
}

static int fih_mem_ddr_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_MEM_DDR_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_MEM_DDR_BASE, FIH_MEM_DDR_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_MEM_DDR_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_MEM_DDR_SIZE);
	kfree(block);

	return 0;
}

static int fih_sensor_tof_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SENSOR_TOF_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SENSOR_TOF_BASE, FIH_SENSOR_TOF_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SENSOR_TOF_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SENSOR_TOF_SIZE);
	kfree(block);

	return 0;
}

static int fih_sensor_ssc_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SENSOR_SSC_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SENSOR_SSC_BASE, FIH_SENSOR_SSC_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SENSOR_SSC_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SENSOR_SSC_SIZE);
	kfree(block);

	return 0;
}

static int fih_sensordata2_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_SENSORDATA2_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_SENSORDATA2_BASE, FIH_SENSORDATA2_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_SENSORDATA2_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_SENSORDATA2_SIZE);
	kfree(block);

	return 0;
}

static int fih_pstore_show(struct seq_file *m, void *v)
{
	void *io_block;
	void *block = kzalloc(FIH_PSTORE_SIZE, GFP_KERNEL);

	if (!block) {
		pr_err("%s: could not allocate buffer", __func__);
		return 0;
	}

	io_block = ioremap(FIH_PSTORE_BASE, FIH_PSTORE_SIZE);
	if (io_block == NULL) {
		pr_err("%s: ioremap fail", __func__);
		return (0);
	}

	memcpy_fromio(block, io_block, FIH_PSTORE_SIZE);
	iounmap(io_block);

	seq_write(m, block, FIH_PSTORE_SIZE);
	kfree(block);

	return 0;
}

static int fih_modem_rf_nv(struct inode *inode, struct file *file)
{
	return single_open(file, fih_modem_rf_nv_show, NULL);
}

static int fih_modem_cust_nv(struct inode *inode, struct file *file)
{
	return single_open(file, fih_modem_cust_nv_show, NULL);
}

static int fih_modem_default_nv(struct inode *inode, struct file *file)
{
	return single_open(file, fih_modem_default_nv_show, NULL);
}

static int fih_modem_log(struct inode *inode, struct file *file)
{
	return single_open(file, fih_modem_log_show, NULL);
}

static int fih_last_alog_main(struct inode *inode, struct file *file)
{
	return single_open(file, fih_last_alog_main_show, NULL);
}

static int fih_last_alog_events(struct inode *inode, struct file *file)
{
	return single_open(file, fih_last_alog_events_show, NULL);
}

static int fih_last_alog_radio(struct inode *inode, struct file *file)
{
	return single_open(file, fih_last_alog_radio_show, NULL);
}

static int fih_last_alog_system(struct inode *inode, struct file *file)
{
	return single_open(file, fih_last_alog_system_show, NULL);
}

static int fih_last_kmsg(struct inode *inode, struct file *file)
{
	return single_open(file, fih_last_kmsg_show, NULL);
}

static int fih_last_blog(struct inode *inode, struct file *file)
{
	return single_open(file, fih_last_blog_show, NULL);
}

static int fih_blog(struct inode *inode, struct file *file)
{
	return single_open(file, fih_blog_show, NULL);
}

static int fih_hwid_hwcfg(struct inode *inode, struct file *file)
{
	return single_open(file, fih_hwid_hwcfg_show, NULL);
}

static int fih_secboot_devinfo(struct inode *inode, struct file *file)
{
	return single_open(file, fih_secboot_devinfo_show, NULL);
}

static int fih_secboot_unlock(struct inode *inode, struct file *file)
{
	return single_open(file, fih_secboot_unlock_show, NULL);
}

static int fih_sutinfo(struct inode *inode, struct file *file)
{
	return single_open(file, fih_sutinfo_show, NULL);
}

static int fih_bset(struct inode *inode, struct file *file)
{
	return single_open(file, fih_bset_show, NULL);
}

static int fih_bat_id_adc(struct inode *inode, struct file *file)
{
	return single_open(file, fih_bat_id_adc_show, NULL);
}

static int fih_apr(struct inode *inode, struct file *file)
{
	return single_open(file, fih_apr_show, NULL);
}

static int fih_mem(struct inode *inode, struct file *file)
{
	return single_open(file, fih_mem_show, NULL);
}

static int fih_e2p(struct inode *inode, struct file *file)
{
	return single_open(file, fih_e2p_show, NULL);
}

static int fih_cda(struct inode *inode, struct file *file)
{
	return single_open(file, fih_cda_show, NULL);
}

static int fih_note(struct inode *inode, struct file *file)
{
	return single_open(file, fih_note_show, NULL);
}

static int fih_hwcfg(struct inode *inode, struct file *file)
{
	return single_open(file, fih_hwcfg_show, NULL);
}

static int fih_fver(struct inode *inode, struct file *file)
{
	return single_open(file, fih_fver_show, NULL);
}

static int fih_sensordata(struct inode *inode, struct file *file)
{
	return single_open(file, fih_sensordata_show, NULL);
}

static int fih_lcmdata(struct inode *inode, struct file *file)
{
	return single_open(file, fih_lcmdata_show, NULL);
}

static int fih_mem_ddr(struct inode *inode, struct file *file)
{
	return single_open(file, fih_mem_ddr_show, NULL);
}

static int fih_sensor_tof(struct inode *inode, struct file *file)
{
	return single_open(file, fih_sensor_tof_show, NULL);
}

static int fih_sensor_ssc(struct inode *inode, struct file *file)
{
	return single_open(file, fih_sensor_ssc_show, NULL);
}

static int fih_sensordata2(struct inode *inode, struct file *file)
{
	return single_open(file, fih_sensordata2_show, NULL);
}

static int fih_pstore(struct inode *inode, struct file *file)
{
	return single_open(file, fih_pstore_show, NULL);
}

/* This structure gather "function" that manage the /proc file
 */
static const struct file_operations fih_modem_rf_nv_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_modem_rf_nv,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_modem_cust_nv_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_modem_cust_nv,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_modem_default_nv_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_modem_default_nv,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_modem_log_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_modem_log,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_last_alog_main_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_last_alog_main,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_last_alog_events_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_last_alog_events,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_last_alog_radio_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_last_alog_radio,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_last_alog_system_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_last_alog_system,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_last_kmsg_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_last_kmsg,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_last_blog_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_last_blog,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_blog_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_blog,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_hwid_hwcfg_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_hwid_hwcfg,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_secboot_devinfo_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_secboot_devinfo,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_secboot_unlock_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_secboot_unlock,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_sutinfo_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_sutinfo,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_bset_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_bset,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_bat_id_adc_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_bat_id_adc,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_apr_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_apr,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_mem_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_mem,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_e2p_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_e2p,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_cda_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_cda,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_note_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_note,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_hwcfg_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_hwcfg,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_fver_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_fver,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_sensordata_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_sensordata,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_lcmdata_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_lcmdata,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_mem_ddr_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_mem_ddr,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_sensor_tof_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_sensor_tof,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_sensor_ssc_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_sensor_ssc,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_sensordata2_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_sensordata2,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static const struct file_operations fih_pstore_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_pstore,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init fih_ramtable_init(void)
{
	struct proc_dir_entry *root;

	root = proc_mkdir("fih_ramtable", NULL);
	if (!root)
		return 1;

	if (proc_create("fih_ramtable/modem_rf_nv", 0, NULL, &fih_modem_rf_nv_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/modem_rf_nv");
	}

	if (proc_create("fih_ramtable/modem_cust_nv", 0, NULL, &fih_modem_cust_nv_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/modem_cust_nv");
	}

	if (proc_create("fih_ramtable/modem_default_nv", 0, NULL, &fih_modem_default_nv_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/modem_default_nv");
	}

	if (proc_create("fih_ramtable/modem_log", 0, NULL, &fih_modem_log_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/modem_log");
	}

	if (proc_create("fih_ramtable/last_alog_main", 0, NULL, &fih_last_alog_main_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/last_alog_main");
	}

	if (proc_create("fih_ramtable/last_alog_events", 0, NULL, &fih_last_alog_events_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/last_alog_events");
	}

	if (proc_create("fih_ramtable/last_alog_radio", 0, NULL, &fih_last_alog_radio_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/last_alog_radio");
	}

	if (proc_create("fih_ramtable/last_alog_system", 0, NULL, &fih_last_alog_system_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/last_alog_system");
	}

	if (proc_create("fih_ramtable/last_kmsg", 0, NULL, &fih_last_kmsg_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/last_kmsg");
	}

	if (proc_create("fih_ramtable/last_blog", 0, NULL, &fih_last_blog_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/last_blog");
	}

	if (proc_create("fih_ramtable/blog", 0, NULL, &fih_blog_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/blog");
	}

	if (proc_create("fih_ramtable/hwid_hwcfg", 0, NULL, &fih_hwid_hwcfg_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/hwid_hwcfg");
	}

	if (proc_create("fih_ramtable/secboot_devinfo", 0, NULL, &fih_secboot_devinfo_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/secboot_devinfo");
	}

	if (proc_create("fih_ramtable/secboot_unlock", 0, NULL, &fih_secboot_unlock_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/secboot_unlock");
	}

	if (proc_create("fih_ramtable/sutinfo", 0, NULL, &fih_sutinfo_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/sutinfo");
	}

	if (proc_create("fih_ramtable/bset", 0, NULL, &fih_bset_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/bset");
	}

	if (proc_create("fih_ramtable/bat_id_adc", 0, NULL, &fih_bat_id_adc_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/bat_id_adc");
	}

	if (proc_create("fih_ramtable/apr", 0, NULL, &fih_apr_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/apr");
	}

	if (proc_create("fih_ramtable/mem", 0, NULL, &fih_mem_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/mem");
	}

	if (proc_create("fih_ramtable/e2p", 0, NULL, &fih_e2p_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/e2p");
	}

	if (proc_create("fih_ramtable/cda", 0, NULL, &fih_cda_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/cda");
	}

	if (proc_create("fih_ramtable/note", 0, NULL, &fih_note_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/note");
	}

	if (proc_create("fih_ramtable/hwcfg", 0, NULL, &fih_hwcfg_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/hwcfg");
	}

	if (proc_create("fih_ramtable/fver", 0, NULL, &fih_fver_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/fver");
	}

	if (proc_create("fih_ramtable/sensordata", 0, NULL, &fih_sensordata_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/sensordata");
	}

	if (proc_create("fih_ramtable/lcmdata", 0, NULL, &fih_lcmdata_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/lcmdata");
	}

	if (proc_create("fih_ramtable/mem_ddr", 0, NULL, &fih_mem_ddr_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/mem_ddr");
	}

	if (proc_create("fih_ramtable/sensor_tof", 0, NULL, &fih_sensor_tof_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/sensor_tof");
	}

	if (proc_create("fih_ramtable/sensor_ssc", 0, NULL, &fih_sensor_ssc_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/sensor_ssc");
	}

	if (proc_create("fih_ramtable/sensordata2", 0, NULL, &fih_sensordata2_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/sensordata2");
	}

	if (proc_create("fih_ramtable/pstore", 0, NULL, &fih_pstore_file_ops) == NULL) {
		pr_err("fail to create proc/fih_ramtable/pstore");
	}

	return (0);
}

static void __exit fih_ramtable_exit(void)
{
	remove_proc_entry("fih_ramtable/modem_rf_nv", NULL);
	remove_proc_entry("fih_ramtable/modem_cust_nv", NULL);
	remove_proc_entry("fih_ramtable/modem_default_nv", NULL);
	remove_proc_entry("fih_ramtable/modem_log", NULL);
	remove_proc_entry("fih_ramtable/last_alog_main", NULL);
	remove_proc_entry("fih_ramtable/last_alog_events", NULL);
	remove_proc_entry("fih_ramtable/last_alog_radio", NULL);
	remove_proc_entry("fih_ramtable/last_alog_system", NULL);
	remove_proc_entry("fih_ramtable/last_kmsg", NULL);
	remove_proc_entry("fih_ramtable/last_blog", NULL);
	remove_proc_entry("fih_ramtable/blog", NULL);
	remove_proc_entry("fih_ramtable/hwid_hwcfg", NULL);
	remove_proc_entry("fih_ramtable/secboot_devinfo", NULL);
	remove_proc_entry("fih_ramtable/secboot_unlock", NULL);
	remove_proc_entry("fih_ramtable/sutinfo", NULL);
	remove_proc_entry("fih_ramtable/bset", NULL);
	remove_proc_entry("fih_ramtable/bat_id_adc", NULL);
	remove_proc_entry("fih_ramtable/apr", NULL);
	remove_proc_entry("fih_ramtable/mem", NULL);
	remove_proc_entry("fih_ramtable/e2p", NULL);
	remove_proc_entry("fih_ramtable/cda", NULL);
	remove_proc_entry("fih_ramtable/note", NULL);
	remove_proc_entry("fih_ramtable/hwcfg", NULL);
	remove_proc_entry("fih_ramtable/fver", NULL);
	remove_proc_entry("fih_ramtable/sensordata", NULL);
	remove_proc_entry("fih_ramtable/lcmdata", NULL);
	remove_proc_entry("fih_ramtable/mem_ddr", NULL);
	remove_proc_entry("fih_ramtable/sensor_tof", NULL);
	remove_proc_entry("fih_ramtable/sensor_ssc", NULL);
	remove_proc_entry("fih_ramtable/sensordata2", NULL);
	remove_proc_entry("fih_ramtable/pstore", NULL);
}

module_init(fih_ramtable_init);
module_exit(fih_ramtable_exit);
