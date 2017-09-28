// Troy Veldhuizen
// Jordan Ward
// CIS 452 - Lab2


#define MAXLINE 80
#define MAXARG 20

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



void run(char* cmd);

/******************************************************
 * Function: main
 * Gets command from user, and spawns off a process to 
 * 	complete the command.
 *
 * return: int, the status of program termination
 * ***************************************************/
int main(){
	char cmd[MAXLINE]; // array to hold args
	int pid; // id of process

	while(1){
			
		struct rusage usage;
	
		printf("lab2shell: "); 
		fgets(cmd, MAXLINE, stdin);  // get input from the user
		
		// return from program if user enters quit
		if(strcmp(cmd, "quit\n") == 0){
			return(0);
		}
		
		// fork child to execute the command
		pid = fork();
		
		// parent waits for child, then prints out usage stats
		if(pid != 0){
			wait(NULL);
			getrusage(RUSAGE_CHILDREN, &usage);		
			printf(
						"CPU Time Used: %ld.%06ld\n",
						usage.ru_utime.tv_sec,
						usage.ru_utime.tv_usec
			);
			printf("Involuntary context switches: %ld\n", usage.ru_nivcsw);
			
			// flush stdout for next input
			fflush(stdout);
		} else {
			run(cmd); // call run function if child
		}
	}

	return 0;
}

/******************************************************
 * Function: run
 * run is the function used to execute the command
 * char* cmd : the pointer to the full command string
 *
 * return: void
 * ***************************************************/

void run(char* cmd){

	int i = 0;
	char *argv[MAXARG];
	char *token;

	// get first arg
	token = strtok(cmd, "\t \n");
  
	// store rest of args in an array
	while(token != NULL){
		argv[i] = token;
		token = strtok(NULL, "\t \n");
		++i;
	}	
	
	// store last array position as NULL
	argv[i] = NULL;

	// execute the command
	if(execvp(argv[0], &argv[0]) == -1){
		fprintf(stderr, "Invalid command.\n");
		exit(0);
	}
}
