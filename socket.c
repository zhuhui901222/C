#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <strings.h>


#define	SERV_IP "127.0.0.1"
#define SERV_PORT 9509

int main(){
	int lfd,cfd;
	struct sockaddr_in serv_addr,clie_addr;
	socklen_t clie_addr_len;
	char buf[BUFSIZ],clie_IP[BUFSIZ];
	int n,i,ret;
	
	lfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(lfd==-1){
		perror("socket fail");
		exit(1);
	}
	
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	//本地转网络
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	ret=bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(ret==-1){
		perror("bind fail");
		exit(1);
	}
	ret=listen(lfd,128);
	if(ret==-1){
		perror("bind fail");
		exit(1);
	}
	
	
	clie_addr_len=sizeof(clie_addr);
	cfd=accept(lfd,(struct sockaddr *)&clie_addr,&clie_addr_len);
	if(cfd==-1){
		perror("accept fail");
		exit(1);
	}
	
	printf("cliet IP :%s,cliet POrt: %d\n",
		inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP))
		,ntohs(clie_addr.sin_port));
	
	
	while(1){
		n=read(cfd,buf,sizeof(buf));
		for(i=0;i<n;i++){
			buf[i]=toupper(buf[i]);
		}
		write(cfd,buf,n);
	}
	close(cfd);
	close(lfd);
	
	
	
	
	
	return 0;
}
