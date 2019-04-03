#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(){
	//打开一个已经存在的文件
	int fd =open("english.txt",O_RDONLY);
	if(fd==-1){
		perror("open fail");
		exit(1);
	}
	
	//创建新文件
	int fd1=open("newfile",O_CREAT|O_WRONLY,0664);
	if(fd1==-1){
		perror("creat fail");
		exit(1);
	}
	
	//read file
	char buf[2048]={0};
	//读到缓冲区  一次2K
	int count =read(fd,buf,sizeof(buf));
	if(count==-1){
		perror("read fail");
		exit(1);
	}
	
	while(count){
		//将读出的数据写入另一个文件
		int ret=write(fd1,buf,count);
		printf("write bytes %d\n",ret);
		count=read(fd,buf,sizeof(buf));
	}
	
	//关闭文件
	close(fd);
	close(fd1);
	
}