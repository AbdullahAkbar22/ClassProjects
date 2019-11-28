/*

Abdullah Akbar CS 3377

Code adapted from Prof. Eric Peterson

Program to demonstrate child processes and signal handling in C

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


static void childExit(int signal){
	printf("SIGTERM called on child!\n");
	exit(0);

}

static void parentExit(void){
	printf("Exiting parent process!\n");

}


int main(){
	pid_t forkType = fork();
	
	
	if(forkType == 0){
		printf("Child process has started!\n");
		
		
		struct sigaction childExitAction;
		childExitAction.sa_handler = childExit;
		sigemptyset(&childExitAction.sa_mask);
		sigaction(SIGTERM, &childExitAction, 0);
		for(;;){
			pause();
		}
	}
	else{
		printf("Parent process has started!\n");	
		sleep(5);
		
		kill(forkType, SIGTERM);
		int status;
		if(waitpid(forkType, &status,0) > 0){
			printf("Child has exited!\n");
		}
		atexit(parentExit);
	}

	return 0;

}