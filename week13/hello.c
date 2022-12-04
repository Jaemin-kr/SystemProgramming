#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int __init init_hello(void){
	printk(KERN_ALERT "[Module Message] init_hello\n");
	return 0;
}
int __exit exit_hello(void){
	printk(KERN_ALERT "[Module Message] exit_hello\n");
}

module_init(init_hello);
module_exit(exit_hello);

MODULE_LICENSE("GPL");

