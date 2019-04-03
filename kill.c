#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <signal.h>


#define N 5

int main(void){
	int i;
	pid_t pid,q;
	for(i=0;i<N;i++){
		pid=fork();
		//子进程
		if(pid==0){
			break;
		}
		if(i==2){
			q=pid;
		}
		
	}
	
	if(i<5){
		while(1){
			printf("我是子进程%d：pid= %u\n",i,getpid());
			sleep(1);
		}
	}else{
		sleep(1);
		kill(q,SIGKILL);
		while(1);
	}
		
	return 0;


}