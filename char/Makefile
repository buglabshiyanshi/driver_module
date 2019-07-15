#!/bin/bash

#编译*.c文件成的中间文件*.o

#申请设备编号
obj-m += req_devt.o

#设备注册 
obj-m += reg_cdev.o

#创建设备节点 
obj-m += char_drv.o 



#Linux Kernel源码目录变量，根据实际情况选择路径

KDIR := ~/src/kernel/tc4_Kernel_3.0

#当前目录变量

PWD ?= $(shell pwd)



#make -C就是指调用执行的路径

# modules 表示将驱动编译成模块，最终生成.ko文件

all:

	make -C $(KDIR) M=$(PWD) modules

clean:

	rm -rf *.o *.mod.* *.order *.symvers *.ko
