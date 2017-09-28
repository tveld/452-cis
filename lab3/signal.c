/*
 * Signal Handling
 * Lab 3
 * CS 452
 * Professor: Greg Wolffe
 * Authors: Jordan Ward, Troy Veldhuizen
 * Date: 09/16/16
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig_num);

int main()
{
	int child_pid = 0;
	int parent_pid = getpid();
	
	child_pid = fork();

	if(child_pid == 0){								// is child
		
		while(1){	
			if(rand() % 2){	
				kill(parent_pid, SIGUSR1);
			} else {
				kill(parent_pid, SIGUSR2);
			}
			
			sleep(1);
		}

	}	else{														// is parent

		signal(SIGINT, handle_signal);
		signal(SIGUSR1, handle_signal);
		signal(SIGUSR2, handle_signal);
	
		while(1){
			printf("waiting ...\t");
			fflush(stdout);
			pause();	
		}

	}

} // end main

void handle_signal(int sig_num)
{

	if(sig_num == SIGINT){
		printf(" received.  That's it, I'm shutting you down...\n");
		fflush(stdout);
		exit(1);
	}

	if(sig_num == SIGUSR1){
		printf("received a SIGUSR1 signal\n");
		fflush(stdout);
	}

	if(sig_num == SIGUSR2){
		printf("recieved a SIGUSR2 signal\n");
		fflush(stdout);
	}

}
