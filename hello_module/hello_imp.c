#include <linux/module.h>
#include <linux/init.h>

static int my_init(void) 
{
	printk(KERN_INFO "hello - Hello, Kernel!\n");
	return 0;
}

static void my_exit(void)
{
	printk(KERN_INFO "hello - Goodbye, Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("claudius");
