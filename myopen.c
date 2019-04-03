#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
        int fd;
        //打开已存在文件
        fd=open("bucunzai",O_RDWR|O_CREAT,777);
		//fd=open("bucunzai",O_RDWR|O_TRUNC);
        if(fd==-1){
                perror("open fail");
                exit(1);
        }
		printf("fd=%d\n",fd);
        //关闭文件
        int ret=close(fd);
        printf("ret=%d\n",ret);
        if(ret==-1){
                perror("close file");
                exit(1);
        }
}
