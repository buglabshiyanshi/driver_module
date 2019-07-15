#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

int main(void){

	int fd;

	char *plat_node = "/dev/plat_dev";


	/*O_RDWR可读写模式打开,O_NDELAY非阻塞方式*/	
	if((fd = open(plat_node,O_RDWR))<0){

		printf("open %s fail \n",plat_node);
		return fd;
	}

	printf("open %s success\n",plat_node);

	char msg[20];

	while(1){
		
		memset(msg,0,sizeof(msg));	
		scanf("%s",msg);
		//printf("app write msg: %s\n", msg);
	
		if( 0 == strcmp(msg,"exit")){
		
			/* 关闭设备文件 */
			close(fd);
			return 0;
		}

		/* 调用IO操作接口 */
		int ret = write(fd,msg,strlen(msg));
		
		if( ret < 0 ){
			printf("write msg err code: %d\n",ret);
		
		}

	};
	
	
	return 0;
}
