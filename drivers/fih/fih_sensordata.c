#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <fih/share/e2p.h>
#include <linux/seq_file.h>
#include "fih_ramtable.h"

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

static int fih_sensordata2(struct inode *inode, struct file *file)
{
	return single_open(file, fih_sensordata2_show, NULL);
}

/* This structure gather "function" that manage the /proc file
 */
static const struct file_operations fih_sensordata2_file_ops = {
	.owner		= THIS_MODULE,
	.open		= fih_sensordata2,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init fih_ramtable_init(void)
{
	struct proc_dir_entry *root;

	root = proc_mkdir("sensordata", NULL);
	if (!root)
		return 1;

	if (proc_create("sensordata/ALS", 0, NULL, &fih_sensordata2_file_ops) == NULL) {
		pr_err("fail to create proc/sensordata/ALS");
	}

	return (0);
}

static void __exit fih_ramtable_exit(void)
{
	remove_proc_entry("sensordata/ALS", NULL);
}

module_init(fih_ramtable_init);
module_exit(fih_ramtable_exit);
