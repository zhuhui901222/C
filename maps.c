#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int var =100;

int main(void){
	int len,ret;
	int *p;
	pid_t pid;
	int fd;
	fd=open("temp",O_RDWR|O_CREAT|O_TRUNC,0777);
	
	//虚拟映射的系统文件
	//fd=open("/dev/zero",O_RDWR|O_CREAT|O_TRUNC,0777);
	//fd=open("/dev/null",O_RDWR|O_CREAT|O_TRUNC,0777);
	if(fd<0){
		perror("open fail");
		exit(1);
	}
	unlink("temp");
	len=ftruncate(fd,4);  //4字节
	if(len==-1){
		perror("ftruncate fail");
		exit(1);
	}
	//MAP_SHARED 会映射到磁盘 用于父子进程间通信 MAP_PRIVATE 映射区修改不会反映到物理设备
	//NULL 指系统自动分配内存区
	//匿名映射  MAP_ANONYMOUS 或者MAP_ANON  fd 改为-1
	
	p=(int *)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(p==MAP_FAILED){
		perror("mmap fail");
		exit(1);
	}
	
	

	
	close(fd);
	
	pid=fork();
	if(pid==0){
		*p=2000;
		var =1000;
		printf("这是子进程，*pid=%d,var=%d\n",*p,var);
		
	}else if(pid>0){
		sleep(1);
		
		printf("这是父进程，*pid=%d,var=%d\n",*p,var);
		wait(NULL);
		
		ret=munmap(p,4);
		if(ret==-1){
			perror("munmap fail");
			exit(1);
		}
			
		
	}else{
		perror("fork error");
		exit(1);
	}
	
	
	
	return 0;




}