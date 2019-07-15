#include <linux/init.h>		/* 模块出入口宏函数所需头文件 */
#include <linux/module.h>	/* 驱动申明宏函数所需头文件 */


#include <linux/kdev_t.h>	/* 设备号处理相关函数所需头文件 */
#include <linux/fs.h>	/* 设备号申请函数所需头文件 */

#include <linux/cdev.h>	/* (cdev)字符设备所需头文件 */


#include <linux/slab.h>	/* 分配内存空间所需头文件 */


#include <linux/device.h>	/* 创建设备节点所需头文件 */


#define DEVICE_NAME "char_dev"
#define CLASS_NAME "char_class"
#define DEVICE_COUNT 2
#define MAJOR_NUM 0		// 默认的主设备号
#define MINOR_NUM 0		// 默认的次设备号


/* 保存主设备号，初始化为默认主设备号，如为非零值，则静态申请设备号，否，则动态申请设备号 */
int major_num = MAJOR_NUM;	
/* 保存次设备号，初始化为第一个次设备号 */
int minor_num = MINOR_NUM;

/* 定义一个设备类表示：此类设备 */
static struct class *char_class;

/* 自定义设备结构 */
struct char_dev
{
	/* 这里可插入设备的私有数据 */
	
	struct cdev cdev;
};

struct char_dev *char_device;


/**** 文件操作:打开设备文件 *****/
static int dev_node_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "dev node open is success \n");
	
	return 0;
}

/**** 文件操作:关闭设备文件 *****/
static int dev_node_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "dev node release is success \n");
	
	return 0;
}

/**** 文件操作:io操作 *****/
static long dev_node_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "\ndev node ioctl is success, cmd is %d,arg is %ld \n",cmd,arg);
	
	return 0;
}



struct file_operations char_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = dev_node_ioctl,
	.open = dev_node_open,
	.release = dev_node_release,
};


/* 设备初始化和注册 */
static void setup_char_dev(struct char_dev *dev,int index)
{
	int ret;
	dev_t devno = MKDEV(major_num,minor_num+index);

	printk(KERN_INFO " setup char device driver \n");
	
	/* 设备初始化 */
	cdev_init(&dev->cdev,&char_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &char_fops;

	/*注册设备到系统*/
	ret = cdev_add(&dev->cdev,devno,1);
	if(ret){
		printk(KERN_EMERG "add char device %d  fail, code: %d\n",index,ret);
	
	}else{
		printk(KERN_EMERG "add char device %d  success\n",minor_num+index);
	}

}


static int char_init(void)
{
	

	int ret = -1;
	int i;
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

	/* 初始化设备类 */
	//char_class = class_create(THIS_MODULE,DEVICE_NAME);
	char_class = class_create(THIS_MODULE,CLASS_NAME);

	/****** 设备初始化和注册 *******/

	/* 分配多个char_device结构内存 */
	char_device = kmalloc((DEVICE_COUNT * sizeof(struct char_dev)),GFP_KERNEL);
	if(!char_device){
		printk(KERN_ERR "kmalloc char device fail\n");
		return -ENOMEM;
	}

	/* 新分配的内存段清零 */
	memset(char_device,0,(DEVICE_COUNT * sizeof(struct char_dev)) );
	
	/* 多个设备数据的初始化 */
	for(i=0;i<DEVICE_COUNT;i++){
		
		/* 调用设备初始化接口 */
		setup_char_dev(&char_device[i],i);

		/*创建设备节点*/
		device_create(char_class,NULL,MKDEV(major_num,minor_num+i),NULL,DEVICE_NAME"%d",i);
	}
	
	return 0;
}

static void char_exit(void)
{
	int i;
	
	printk(KERN_INFO " char device driver exit\n");
	
	
	for(i=0;i<DEVICE_COUNT;i++){
		
		/* 注销字符设备 */
		cdev_del(&(char_device[i].cdev));

		/* 注销设备节点 */
		device_destroy(char_class,MKDEV(major_num,minor_num+i));
	}

	/*释放内存*/
	kfree(char_device);

	
	/* 销毁设备类 */
	class_destroy(char_class);

	/* 注销设备号 */
	unregister_chrdev_region(MKDEV(major_num, minor_num),DEVICE_COUNT);
}


module_init(char_init);
module_exit(char_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("buglab/bug");
MODULE_DESCRIPTION("char device module test");
