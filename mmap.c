#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int main(void){
	int len,ret;
	char *p=NULL;
	int fd=open("mytest.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	if(fd<0){
		perror("open fail");
		exit(1);
	}
	len=ftruncate(fd,4);  //4字节
	if(len==-1){
		perror("ftruncate fail");
		exit(1);
	}

	//MAP_SHARED 会映射到磁盘 MAP_PRIVATE 映射区修改不会反映到物理设备
	//NULL 指系统自动分配内存区
	p=mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p==MAP_FAILED){
		perror("mmap fail");
		exit(1);
	}
	strcpy(p,"abc");//写数据
	
	ret=munmap(p,4);
	if(ret==-1){
		perror("munmap fail");
		exit(1);
	}
	close(fd);
	
	
	
	return 0;

}