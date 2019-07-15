#include <linux/init.h>		/* 模块出入口宏函数所需头文件 */
#include <linux/module.h>	/* 驱动申明宏函数所需头文件 */

#include <linux/platform_device.h> /* 平台设备驱动注册卸载相关的函数 */



#define DRIVER_NAME "plat_dev"


static int plat_probe(struct platform_device *pdv)
{
	
	printk(KERN_INFO "device driver probe\n");
	
	return 0;
}

static int plat_remove(struct platform_device *pdv)
{
	
	printk(KERN_INFO " remove device driver\n");
	return 0;
}

static void plat_shutdown(struct platform_device *pdv)
{
	
}

static int plat_suspend(struct platform_device *pdv,pm_message_t pmt)
{
	
	return 0;
}

static int plat_resume(struct platform_device *pdv)
{
	
	return 0;
}

struct platform_driver plat_drv = {
	.probe = plat_probe,
	.remove = plat_remove,
	.shutdown = plat_shutdown,
	.suspend = plat_suspend,
	.resume = plat_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	}
};

static int platform_init(void)
{
	int ret;
	
	printk(KERN_INFO "platform module entry!\n");
	ret = platform_driver_register(&plat_drv);
	
	/* 如果驱动注册失败，则打印提示 */
	if( ret < 0 ){
		printk(KERN_ERR "platform driver register error code: %d\n",ret);
		return ret;
	}	
	return 0;
}

static void platform_exit(void)
{
	printk(KERN_INFO "platform module exit!\n");
	
	platform_driver_unregister(&plat_drv);	
}

module_init(platform_init);
module_exit(platform_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("buglab/bug");
MODULE_DESCRIPTION("platform module test");
