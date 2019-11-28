/*

Abdullah Akbar CS 3377

Code adapted from Prof. Eric Peterson

Program to demonstrate mutexes, pthreads, and condition variables in C

*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

static int value = 0;
const int numIncrements = 100000;
pthread_mutex_t theLock; //The lock we will be using
pthread_cond_t theCond = PTHREAD_COND_INITIALIZER; // initialize the condition var

int turn = 1; // 1 if main should increment, 0  if thread1 should increment

void* threadStart(void* arg) {
	int myNumber = 0;
		
	while ( myNumber < numIncrements) {
		if ( (myNumber % 10000) == 0) {
			printf("Up to %d\n", myNumber);
		}

		// It's possible that the main thread got here first, so check in a loop
		while (value == myNumber) {
			
		}
		pthread_mutex_lock(&theLock); // lock the mutex
		if ( value > myNumber+1) {
			printf("Error: other number increased too much (%d vs. %d)!\n", value, myNumber);
			exit(1);
		}
		if (turn == 1) { //If its main's turn to increment, put this thread to sleep again
			pthread_cond_wait(&theCond, &theLock);
			printf("waking\n");
		} 
		else { //otherwise wake it up
	  
		
			pthread_cond_signal(&theCond); 
			printf("huh\n");
		} 
		printf("next\n");
		myNumber++; //increment myNumber
		turn = 1; //set turn to main's turn
		pthread_mutex_unlock(&theLock); //unlock the mutex
			
	}
	
	return (void*) NULL;
}

int main(int argc, char *argv[])
{
	pthread_mutex_init(&theLock, NULL); //initialize the mutex lock

	pthread_t thread1;
	int err = pthread_create(&thread1, NULL, threadStart, (void*) NULL);
	if ( err != 0) {
		//wprintf(STDERR_FILENO, "Cannot create thread.\n");
		exit(1);
	}
	
	while ( value < numIncrements) {
		pthread_mutex_lock(&theLock);//lock the mutex
		if (turn == 0) { //It it's thread1's turn to increment, put main thread to sleep
			pthread_cond_wait(&theCond, &theLock);
		
		} 
		else { //otherwise wake it up
	  
		
			pthread_cond_signal(&theCond); 
		} 
		value++; //increment value
		turn = 0; //set turn to thread1's
		
		pthread_mutex_unlock(&theLock);	
		
	}
	
	err = pthread_join(thread1, NULL);
	if ( err != 0) {
		//wprintf(STDERR_FILENO, "Cannot join with thread.\n");
		exit(1);
	}
	printf("All done...\n");
}