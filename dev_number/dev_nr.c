#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("claudius");
MODULE_DESCRIPTION("Registers a device nr. and implement some callback functions");

// This function is called, when the device file is opened
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
};

#define MYMAJOR 90

// This function is called, when the module is loaded into the kernel
static int  __init ModuleInit(void) 
{
	int retval;
	printk(KERN_INFO "hello - Hello, Kernel!\n");
	retval = register_chrdev(MYMAJOR, "dev_nr", &fops);
	if (retval == 0) { 
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	} else if (retval > 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	} else {
		printk("Could not register device number!\n");
	}

	return 0;
}

// This function is called. when the module is removed from the kernel
static void __exit ModuleExit(void)
{
	unregister_chrdev(MYMAJOR, "dev_nr");
	printk(KERN_INFO "hello - Goodbye, Kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


