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
	alarm(1);
	for(i=0;;i++){
		printf("%d\n",i);
	}
	
		
	return 0;


}

