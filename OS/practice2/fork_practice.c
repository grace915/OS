#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void){
	pid_t pids[2];
	int state1;
	int state2;
	int i = 0;
	
	printf("Waiting for child Processes\n");


	
	pids[1] = fork();
	
	if(pids[1] == 0){
		
		execl("./child2","", NULL);
		exit(0);
	}
		
	pids[0] = fork();
	
	if(pids[0] == 0){
			
		execl("./child", "", NULL);
		exit(0);
		
	}

	else{
		waitpid(pids[0], &state1, 0);
		waitpid(pids[1], &state2, 0);
		printf("Child Processes are exit(%d)(%d))\n", state1, state2);
			
	}
	
	
	return 0;
}
