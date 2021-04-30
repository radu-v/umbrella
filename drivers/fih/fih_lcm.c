/*
 * Virtual file interface for FIH LCM, 20151103
 * KuroCHChung@fih-foxconn.com
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define FIH_PROC_PATH_AOD "AOD"
#define FIH_PROC_PATH_PANEL_ID "PanelID"
#define FIH_PROC_DIR_LCM0 "AllHWList/LCM0"
#define FIH_PROC_PATH_AOD_LP "setlp"
#define FIH_PROC_PATH_GLANCE "glance"
#define FIH_PROC_PATH_COLORMANAGER "cm"
#define FIH_PROC_PATH_HIGH_BRIGHTNESS_MODE "hbm"
#define FIH_PROC_FULL_PATH_COLORMANAGER "AllHWList/LCM0/cm"
#define FIH_PROC_FULL_PATH_HIGH_BRIGHTNESS_MODE "AllHWList/LCM0/hbm"
#define FIH_PROC_FULL_PATH_AOD "AllHWList/LCM0/AOD"
#define FIH_PROC_FULL_PATH_PANEL_ID "AllHWList/LCM0/PanelID"
#define FIH_PROC_FULL_PATH_AOD_LP "AllHWList/LCM0/setlp"
#define FIH_PROC_FULL_PATH_GLANCE "AllHWList/LCM0/glance"

#define FIH_PROC_PATH_AWER_CNT "awer_cnt"
#define FIH_PROC_PATH_AWER_STATUS "awer_status"
#define FIH_PROC_FULL_PATH_AWER_CNT "AllHWList/LCM0/awer_cnt"
#define FIH_PROC_FULL_PATH_AWER_STATUS "AllHWList/LCM0/awer_status"
#define COLORMODE_STRING_SIZE 3
void fih_awer_cnt_set(char *info);
void fih_awer_status_set(char *info);
#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
extern int fih_mdss_color_config(unsigned char type);
extern int fih_mdss_high_brightness_configure(bool enable);
extern bool fih_mdss_high_brightness_get(void);
#endif
#ifdef CONFIG_AOD_FEATURE
extern int fih_get_aod(void);
extern unsigned int fih_get_panel_id(void);
extern int fih_set_aod(int enable);
extern int fih_set_low_power_mode(int enable);
extern int fih_get_low_power_mode(void);
extern int fih_set_glance(int enable);
extern int fih_get_glance(void);

#endif

#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
static int fih_lcm_show_hbm(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n",fih_mdss_high_brightness_get());
	return 0;
}

static int fih_lcm_open_hbm_settings(struct inode *inode, struct  file *file)
{
	return single_open(file, fih_lcm_show_hbm, NULL);
}

static ssize_t fih_lcm_write_hbm_settings(struct file *file, const char __user *buffer,
					size_t count, loff_t *offp)
{
	char *buf;
	unsigned int res;

	if (count < 1)
		return -EINVAL;

	buf = kmalloc(count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;

	pr_debug("fih_lcm_write_hbm_settings\n");


	res = fih_mdss_high_brightness_configure(simple_strtoull(buf, NULL, 0));

	if (res < 0)
	{
		kfree(buf);
		return res;
	}

	kfree(buf);

	/* claim that we wrote everything */
	return count;
}
static struct file_operations hbm_file_ops = {
	.owner   = THIS_MODULE,
	.write   = fih_lcm_write_hbm_settings,
	.read	= seq_read,
	.open	= fih_lcm_open_hbm_settings,
	.release = single_release
};
#endif


#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
static int fih_lcm_show_color(struct seq_file *m, void *v)
{
	seq_printf(m, "Not Support\n");
	return 0;
}

static int fih_lcm_open_color_settings(struct inode *inode, struct  file *file)
{
	return single_open(file, fih_lcm_show_color, NULL);
}


static ssize_t fih_lcm_write_color_settings(struct file *file, const char __user *buffer,
					size_t count, loff_t *offp)
{
	char *buf;
	unsigned int res;

	if (count < 1)
		return -EINVAL;

	buf = kmalloc(count, GFP_KERNEL);

	if (!buf)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;

	buf[COLORMODE_STRING_SIZE]=0;
	pr_debug("fih_lcm_write_color_settings %s\n",buf);

	res = fih_mdss_color_config(simple_strtoul(buf, NULL, 16));

	if (res < 0)
	{
		kfree(buf);
		return res;
	}

	kfree(buf);

	/* claim that we wrote everything */
	return count;
}
static struct file_operations color_file_ops = {
	.owner   = THIS_MODULE,
	.write   = fih_lcm_write_color_settings,
	.read	= seq_read,
	.llseek  = seq_lseek,
	.open	= fih_lcm_open_color_settings,
	.release = single_release
};
#endif

static int fih_lcm_show_glance(struct seq_file *m, void *v)
{
#ifdef CONFIG_AOD_FEATURE
	seq_printf(m, "%d\n", fih_get_glance());
#else
	seq_printf(m, "0\n");
#endif
	return 0;
}

static int fih_lcm_open_glance_settings(struct inode *inode, struct  file *file)
{
	return single_open(file, fih_lcm_show_glance, NULL);
}


static ssize_t fih_lcm_write_glance_settings(struct file *file, const char __user *buffer,
					size_t count, loff_t *offp)
{
	char *buf;
	unsigned int res;

	if (count < 1)
		return -EINVAL;

	buf = kmalloc(count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;

	pr_debug("fih_lcm_write_glance_settings\n");

#ifdef CONFIG_AOD_FEATURE
	res = fih_set_glance(simple_strtoull(buf, NULL, 0));
#endif
	if (res < 0)
	{
		kfree(buf);
		return res;
	}

	kfree(buf);

	/* claim that we wrote everything */
	return count;
}
static struct file_operations glance_file_ops = {
	.owner   = THIS_MODULE,
	.write   = fih_lcm_write_glance_settings,
	.read	= seq_read,
	.open	= fih_lcm_open_glance_settings,
	.release = single_release
};


static int fih_lcm_show_aod_lp_settings(struct seq_file *m, void *v)
{
#ifdef CONFIG_AOD_FEATURE
	seq_printf(m, "%d\n", fih_get_low_power_mode());
#else
	seq_printf(m, "0\n");
#endif
	return 0;
}

static int fih_lcm_open_aod_lp_settings(struct inode *inode, struct  file *file)
{
	return single_open(file, fih_lcm_show_aod_lp_settings, NULL);
}


static ssize_t fih_lcm_write_aod_lp_settings(struct file *file, const char __user *buffer,
					size_t count, loff_t *offp)
{
	char *buf;
	unsigned int res;

	if (count < 1)
		return -EINVAL;

	buf = kmalloc(count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;
	pr_err("fih_lcm_write_aod_lp_settings\n");

#ifdef CONFIG_AOD_FEATURE
	res = fih_set_low_power_mode(simple_strtoull(buf, NULL, 0));
#endif
	if (res < 0)
	{
		kfree(buf);
		return res;
	}

	kfree(buf);

	/* claim that we wrote everything */
	return count;
}
static struct file_operations aod_lp_file_ops = {
	.owner   = THIS_MODULE,
	.write   = fih_lcm_write_aod_lp_settings,
	.read	= seq_read,
	.open	= fih_lcm_open_aod_lp_settings,
	.release = single_release
};

char fih_awer_cnt[32] = "unknown";
char fih_awer_status[32] = "unknown";

void fih_awer_cnt_set(char *info)
{
	strcpy(fih_awer_cnt, info);
}

static int fih_awer_cnt_read_proc(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", fih_awer_cnt);
	return 0;
}

static int fih_awer_cnt_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, fih_awer_cnt_read_proc, NULL);
}

static struct file_operations awer_cnt_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_awer_cnt_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release,
};

void fih_awer_status_set(char *info)
{
	strcpy(fih_awer_status, info);
}

static int fih_awer_status_read_proc(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", fih_awer_status);
	return 0;
}

static int fih_awer_status_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, fih_awer_status_read_proc, NULL);
}

static struct file_operations awer_status_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_awer_status_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release,
};

static int fih_lcm_show_panelid_settings(struct seq_file *m, void *v)
{
#ifdef CONFIG_AOD_FEATURE
	seq_printf(m, "%d\n", fih_get_panel_id());
#else
	seq_printf(m, "0\n");
#endif
	return 0;
}

static int fih_lcm_open_panelid_settings(struct inode *inode, struct  file *file)
{
	return single_open(file, fih_lcm_show_panelid_settings, NULL);
}

static ssize_t fih_lcm_write_panelid_settings(struct file *file, const char __user *buffer,
					size_t count, loff_t *offp)
{
	return count;
}


static struct file_operations panel_id_file_ops = {
	.owner   = THIS_MODULE,
	.write   = fih_lcm_write_panelid_settings,
	.read	= seq_read,
	.open	= fih_lcm_open_panelid_settings,
	.release = single_release
};

static int fih_lcm_show_aod_settings(struct seq_file *m, void *v)
{
#ifdef CONFIG_AOD_FEATURE
	seq_printf(m, "%d\n", fih_get_aod());
#else
	seq_printf(m, "0\n");
#endif
	return 0;
}

static int fih_lcm_open_aod_settings(struct inode *inode, struct  file *file)
{
	return single_open(file, fih_lcm_show_aod_settings, NULL);
}

static ssize_t fih_lcm_write_aod_settings(struct file *file, const char __user *buffer,
					size_t count, loff_t *offp)
{
	char *buf;
	unsigned int res;

	if (count < 1)
		return -EINVAL;

	buf = kmalloc(count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (copy_from_user(buf, buffer, count))
		return -EFAULT;
#ifdef CONFIG_AOD_FEATURE
	res = fih_set_aod(simple_strtoull(buf, NULL, 0));
#endif
	if (res < 0)
	{
		kfree(buf);
		return res;
	}

	kfree(buf);

	/* claim that we wrote everything */
	return count;
}
static struct file_operations aod_file_ops = {
	.owner   = THIS_MODULE,
	.write   = fih_lcm_write_aod_settings,
	.read	= seq_read,
	.open	= fih_lcm_open_aod_settings,
	.release = single_release
};

static int __init fih_proc_init(void)
{
	struct proc_dir_entry *lcm0_dir;
	lcm0_dir = proc_mkdir (FIH_PROC_DIR_LCM0, NULL);

	pr_err("start to create proc/%s\n", FIH_PROC_PATH_AOD);
	if(proc_create(FIH_PROC_PATH_AOD, 0, lcm0_dir, &aod_file_ops) == NULL)
	{
		pr_err("fail to create proc/%s\n", FIH_PROC_PATH_AOD);
		return (1);
	}

	pr_err("start to create proc/%s\n", FIH_PROC_PATH_PANEL_ID);
	if(proc_create(FIH_PROC_PATH_PANEL_ID, 0, lcm0_dir, &panel_id_file_ops) == NULL)
	{
		pr_err("fail to create proc/%s\n", FIH_PROC_PATH_PANEL_ID);
		return (1);
	}
	pr_err("start to create proc/%s\n", FIH_PROC_PATH_AOD_LP);
	if(proc_create(FIH_PROC_PATH_AOD_LP, 0, lcm0_dir, &aod_lp_file_ops) == NULL)
	{
		pr_err("fail to create proc/%s\n", FIH_PROC_PATH_AOD_LP);
		return (1);
	}

	pr_debug("start to create proc/%s\n", FIH_PROC_PATH_AWER_CNT);
	if (proc_create(FIH_PROC_PATH_AWER_CNT, 0, lcm0_dir, &awer_cnt_file_ops) == NULL)
	{
		pr_err("fail to create /proc/%s\n", FIH_PROC_PATH_AWER_CNT);
	}

	pr_debug("start to create proc/%s\n", FIH_PROC_PATH_AWER_STATUS);
	if (proc_create(FIH_PROC_PATH_AWER_STATUS, 0, lcm0_dir, &awer_status_file_ops) == NULL)
	{
		pr_err("fail to create /proc/%s\n", FIH_PROC_PATH_AWER_STATUS);
	}

	pr_debug("start to create proc/%s\n", FIH_PROC_PATH_GLANCE);
	if (proc_create(FIH_PROC_PATH_GLANCE, 0, lcm0_dir, &glance_file_ops) == NULL)
	{
		pr_err("fail to create /proc/%s\n", FIH_PROC_PATH_GLANCE);
	}
#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
	pr_debug("start to create proc/%s\n", FIH_PROC_FULL_PATH_COLORMANAGER);
	if (proc_create(FIH_PROC_PATH_COLORMANAGER, 0, lcm0_dir, &color_file_ops) == NULL)
	{
		pr_err("fail to create /proc/%s\n", FIH_PROC_FULL_PATH_COLORMANAGER);
	}
	pr_debug("start to create proc/%s\n", FIH_PROC_FULL_PATH_HIGH_BRIGHTNESS_MODE);
	if (proc_create(FIH_PROC_PATH_HIGH_BRIGHTNESS_MODE, 0, lcm0_dir, &hbm_file_ops) == NULL)
	{
		pr_err("fail to create /proc/%s\n", FIH_PROC_FULL_PATH_HIGH_BRIGHTNESS_MODE);
	}

#endif
	return (0);
}

static void __exit fih_proc_exit(void)
{
	remove_proc_entry(FIH_PROC_FULL_PATH_AOD, NULL);
	remove_proc_entry(FIH_PROC_FULL_PATH_PANEL_ID, NULL);
	remove_proc_entry(FIH_PROC_FULL_PATH_AOD_LP, NULL);

	remove_proc_entry(FIH_PROC_FULL_PATH_AWER_CNT, NULL);
	remove_proc_entry(FIH_PROC_FULL_PATH_AWER_STATUS, NULL);
	remove_proc_entry(FIH_PROC_FULL_PATH_GLANCE, NULL);
#ifdef CONFIG_PANEL_COLOR_MANAGERIAL
	remove_proc_entry(FIH_PROC_FULL_PATH_COLORMANAGER, NULL);
remove_proc_entry(FIH_PROC_FULL_PATH_HIGH_BRIGHTNESS_MODE, NULL);
#endif
}

module_init(fih_proc_init);
module_exit(fih_proc_exit);
