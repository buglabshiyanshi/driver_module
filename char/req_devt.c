#include <linux/init.h>		/* 模块出入口宏函数所需头文件 */
#include <linux/module.h>	/* 驱动申明宏函数所需头文件 */


#include <linux/kdev_t.h>	/* 设备号处理相关函数所需头文件 */
#include <linux/fs.h>	/* 设备号申请函数所需头文件 */



#define DEVICE_NAME "char_dev"
#define DEVICE_COUNT 1
#define MAJOR_NUM 10		// 默认的主设备号
#define MINOR_NUM 0		// 默认的次设备号


/* 保存主设备号，初始化为默认主设备号，如为非零值，则静态申请设备号，否，则动态申请设备号 */
int major_num = MAJOR_NUM;	

/* 保存次设备号，初始化为第一个次设备号 */
int minor_num = MINOR_NUM;


static int char_init(void)
{
	int ret = -1;
	dev_t dev_num;

	printk(KERN_INFO " char device driver init\n");

	
	if(major_num){
		
		dev_num = MKDEV(major_num,minor_num);
		
		/* 静态申请设备号 */
		ret = register_chrdev_region(dev_num,DEVICE_COUNT,DEVICE_NAME);
	}

	/* 如果静态申请设备号失败，则使用动态申请设备号 */
	if( ret < 0){
		
		printk(KERN_INFO "register_chardev_region fail, code: %d\n", ret);

		/* 动态申请设备号 */
		ret = alloc_chrdev_region(&dev_num,minor_num,DEVICE_COUNT,DEVICE_NAME);

		/* 动态申请设备号失败，则驱动初始化失败，退出 */
		if(ret<0){
			printk(KERN_ERR "alloc chrdev region fail, code: %d\n", ret);	
			return ret;	
		}

	}

	/* 保存申请到的主设备号，后用 */
	major_num = MAJOR(dev_num);
	printk(KERN_INFO "char dev major num: %d \n",major_num);

	
	return 0;
}

static void char_exit(void)
{
	printk(KERN_INFO " char device driver exit\n");

	/* 注销设备号 */
	unregister_chrdev_region(MKDEV(major_num, minor_num),DEVICE_COUNT);
}


module_init(char_init);
module_exit(char_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("buglab/bug");
MODULE_DESCRIPTION("char device module request device num test");
