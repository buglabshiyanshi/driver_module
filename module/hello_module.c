#include <linux/init.h>		/* 模块出入口所需头文件 */
#include <linux/module.h>	/* 驱动声明宏函数所需头文件 */


MODULE_LICENSE("GPL");		/* 声明许可证：遵循GPL协议 */
MODULE_AUTHOR("buglab/bug");/* 声明作者 */
MODULE_DESCRIPTION("hello module");	/* 驱动描述 */

/* 驱动入口 */
static int hello_init(void)
{
	printk(KERN_INFO "hello driver enter!\n");

	return 0;
}

/* 驱动卸载 */
static void hello_exit(void)
{
	printk(KERN_INFO "hello driver exit!\n");
}


module_init(hello_init);	/* 模块入口 */
module_exit(hello_exit);	/* 模块出口 */
