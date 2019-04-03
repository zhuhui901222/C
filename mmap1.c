#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

//运行 ./mmap1  a.out

struct STU{
	int id;
	char name[20];
	char sex;
};


void sys_error(char *str){
	perror(str);
	exit(1);
}

int main(int argc , char*argv[]){
	int fd;
	struct STU student;
	struct STU *mm;
	if(argc<2){
		printf("./a.out file_shared\n");
		exit(1);
	}
	
	fd=open(argv[1],O_RDONLY|O_CREAT,0777);
	if(fd<0){
		perror("open fail");
		exit(1);
	}
	
	mm=mmap(NULL,sizeof(student),PROT_READ,MAP_SHARED,fd,0);
	if(mm==MAP_FAILED){
		perror("mmap fail");
		exit(1);
	}
	
	close(fd);
	
	while(1){
		printf("id=%d\tname=%s\t%c\n",mm->id,mm->name,mm->sex);
		sleep(1);
	}
	
	munmap(mm,sizeof(student));
	return 0;
	
}