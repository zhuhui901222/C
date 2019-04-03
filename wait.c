#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	pid_t pid,wpid;
	int status;
	pid=fork();
	if(pid==0){
		printf("这是子进程，pid=%u\n,ppid=%u\n",getpid(),getppid());
		sleep(20);
		return 100;
	}else if(pid>0){
		wpid=wait(&status);
		if(wpid==-1){
			perror("wait error");
			exit(1);
		}
		if(WIFEXITED(status)){
			printf("子进程退出返回： %d/n",WEXITSTATUS(status));
		}
		
		if(WIFSIGNALED(status)){
			printf("子进程被杀死： %d/n",WTERMSIG(status));
		}
		
		while(1){
			printf("这是父进程，pid=%u\n,ppid=%u\n",getpid(),getppid());
			sleep(1);
		}
		
		
	}else{
		perror("fork error");
		exit(1);
	}
	
	
	//waitpid(-1,NULL,WNOHANG)  非阻塞等待
	
	return 0;
	
	
}
