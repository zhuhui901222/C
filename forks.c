#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	pid_t pid;
	printf("xxxxxxx/oooo\n");
	
	for(i=0;i<5;i++){
		pid=fork();
		if(pid==-1){
			perror("fork error");
			exit(1);
		}else if(pid==0){
			printf("这是第%d子进程，pid=%u\n,ppid=%u\n",i+1,getpid(),getppid());
			break;
		}else{
			printf("这是父进程，pid=%u\n,ppid=%u\n",getpid(),getppid());
			sleep(1);
		}
	}
	
	
	
	printf("yyyyyyyyyyyy/oooo\n");
	
	return 0;
	
	
}
