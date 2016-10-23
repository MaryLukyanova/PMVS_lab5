#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Calculator");
MODULE_AUTHOR("Mary Lukyanova");
MODULE_VERSION("1");

#define PROC_FIRST "first"
#define PROC_SECOND "second"
#define PROC_OPERAND "operand"
#define DEV_RESULT "result"

#define PROC_MAX_SIZE 20


static struct proc_dir_entry *first_proc_file, *second_proc_file, *operand_proc_file;
static const int first_proc_index = 1, second_proc_index = 2, operand_proc_index = 3;

static ssize_t proc_write(struct file *filp, const char __user *buffer, size_t count, loff_t *data)
{
	
}

static ssize_t dev_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{

}

static struct file_operations proc_file_ops = {
	.owner = THIS_MODULE,
	.write = proc_write,
};
static const struct file_operations dev_file_ops = {
	.owner = THIS_MODULE,
	.read = dev_read,
};
static struct miscdevice result_dev = {
	MISC_DYNAMIC_MINOR,
	DEV_RESULT,
	&dev_file_ops
};

static int calc_init(void)
{		
	printk(KERN_INFO "Calc module started working\n");
	first_proc_file = proc_create_data(PROC_FIRST, 766, NULL, &proc_file_ops, (void*) &first_proc_index);
	if (first_proc_file == NULL) {
		printk(KERN_ERR "can't create first proc");
		remove_proc_entry(PROC_FIRST, NULL);
		return -ENOMEM;
	}
	second_proc_file = proc_create_data(PROC_SECOND, 766, NULL, &proc_file_ops, (void*) &second_proc_index);
	if (second_proc_file == NULL) {
		printk(KERN_ERR "can't create second proc");
		remove_proc_entry(PROC_FIRST, NULL);
		remove_proc_entry(PROC_SECOND, NULL);
		return -ENOMEM;
	}
	operand_proc_file = proc_create_data(PROC_OPERAND, 766, NULL, &proc_file_ops, (void*) &operand_proc_index);
	if (operand_proc_file == NULL) {
		printk(KERN_ERR "can't create operand proc");
		remove_proc_entry(PROC_FIRST, NULL);
		remove_proc_entry(PROC_SECOND, NULL);
		remove_proc_entry(PROC_OPERAND, NULL);
		return -ENOMEM;
	}	
	if (misc_register(&result_dev)) {
		printk(KERN_ERR "Unable to register \"result\" misc device\n");
		remove_proc_entry(PROC_FIRST, NULL);
		remove_proc_entry(PROC_SECOND, NULL);
		remove_proc_entry(PROC_OPERAND, NULL);
		return -ENOMEM;
	}
	return 0;
}

static void calc_exit(void)
{
	printk(KERN_INFO "Calc module stopped working\n");
	remove_proc_entry(PROC_FIRST, NULL);
	remove_proc_entry(PROC_SECOND, NULL);
	remove_proc_entry(PROC_OPERAND, NULL);
	misc_deregister(&result_dev);
}

module_init(calc_init);
module_exit(calc_exit);
