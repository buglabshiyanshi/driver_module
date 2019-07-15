#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void){

	int fd;

	char *char_node = "/dev/char_dev0";


	/*O_RDWR可读写模式打开,O_NDELAY非阻塞方式*/	
	if((fd = open(char_node,O_RDWR))<0){

		printf("open %s fail \n",char_node);
		return fd;
	}

	printf("open %s success\n",char_node);

	int cmd, arg;

	while(1){
		
		scanf("%d %d",&cmd, &arg);
	
		if( (cmd < 0) || (arg < 0) ){
		
			/* 关闭设备文件 */
			close(fd);
			return 0;
		}

		/* 调用IO操作接口 */
		ioctl(fd,cmd,arg);
	};
	
	
	return 0;
}
