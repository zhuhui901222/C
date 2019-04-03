#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(void){
	int fd[2];
	//fd[0]->r  fd[1]->w
	int ret=pipe(fd);
	pid_t pid;
	if(ret==-1){
		perror("pipe error");
		exit(1);
	}
	pid=fork();
	if(pid==-1){
		perror("fork error");
		exit(1);
	}else if(pid==0){	//子 可读  关闭写
		close(fd[1]);
		char buf[1024];
		ret=read(fd[0],buf,sizeof(buf));
		if(ret==0){
			printf("-----\n");
		}
		write(STDOUT_FILENO,buf,ret);
		
	}else{	//父  可写  关闭读
	//	sleep(1);
		close(fd[0]);
		write(fd[1],"hello pipe\n",strlen("hello pipe\n"));
		
	}
	
	
	return 0;
	
}



/**

7种linux文件类型
- 文件	
d 目录
l 符号链接
s 套接字
b 块设备
c 字符设备
p 管道

前3种占用磁盘存储  后4种为伪文件 不占用磁盘存储

*/