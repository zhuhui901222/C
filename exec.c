#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid==-1){
		perror("fork error");
		exit(1);
	}else if(pid==0){
		printf("这是子进程，pid=%u\n,ppid=%u\n",getpid(),getppid());
	//	execlp("ls","ls","-l","-a",NULL);
	//	execl("/bin/ls","ls","-l","-a",NULL);
		char *argv[]={"ls","-l","-a",NULL};
		execv("/bin/ls",argv);
	}else{
		printf("这是父进程，pid=%u\n,ppid=%u\n",getpid(),getppid());
		sleep(1);
	}
	
	return 0;
	
	
}
