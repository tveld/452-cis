/* Server Manager
 * CIS 452 - Operating Systems
 * Professor Greg Wolffe
 * Author: Troy Veldhuizen
 */


#define MAXSERVERS 10
#define MAXLINE 80
#define MAXARG 4

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef struct server {
	int pid;					// process id
	int minProcs;			// minimum number of processes
	int maxProcs;			// maximum number of processes
	int numActive;		// number of currently active processes
	char* serverName; // server name
} server;

int serverCount = 0;
server servers [MAXSERVERS];  // array of servers


int findServer(char *serverName){
	int i;
	char *sname = "sname";

	for(i = 0; i < serverCount; ++i){
	
		if(strcmp(servers[i].serverName, serverName) == 0){
			return i;
		}	
 
	}

	return -1;
}

int createServer(int minProcs, int maxProcs, char *serverName){

	if(serverCount < MAXSERVERS){
		
		if(findServer(serverName) == -1){
		
			int pid = fork();
	
			if(pid == 0){													// is server
		
				pause();
	
			} else {															// is server manager
		
						server new;
						new.pid = pid;
						new.minProcs = minProcs;
						new.maxProcs = maxProcs;
						new.serverName = serverName;

						servers[serverCount] = new;
		
						printf("\ncreating server ...");
						printf("\nserver name: %s", servers[serverCount].serverName);
						printf("\nmin processes: %d", servers[serverCount].minProcs);
						printf("\nmax processes: %d\n\n", servers[serverCount].maxProcs);
		
						++serverCount;
		
			}
		} else {
			printf("\nAction aborted. Server name already exists.\n\n");
		}

	} else {

		printf("\nAction aborted. Can not create more than %d servers.\n\n", MAXSERVERS);

	}

}

int abortServer(char* serverName){
	int index = findServer(serverName);
	
	if(index != -1){
		kill(servers[index].pid, SIGKILL);
		servers[index] = 0;
		--serverCount;
	} else {
		printf("\nAction aborted. Server name not found.\n\n");
	}
}

int createProcess(){

}

int abortProcess(){

}

int displayStatus(){

}


int main(){
	int i, first, second;
	char *args[MAXARG];
	char cmd[MAXLINE];
	char *token;

	while(1){
		
		i = 0;

		printf("server controller:  ");
		
		if(strcmp( fgets(cmd, MAXLINE, stdin), "\n") != 0){
		
			token = strtok(cmd, "\t \n");
			
			while(token != NULL){
				args[i] = token;
				token = strtok(NULL, "\t \n");
				++i;
			}

			
	
			// create server
			if(strcmp(args[0], "createServer") == 0){		
				
				if(args[1] != NULL && args[2] != NULL && args[3] != NULL){
					
					
					int minProcs = atoi(args[1]);
					int maxProcs = atoi(args[2]);
					char* serverName = malloc(sizeof(char)* strlen(args[3]));
					strcpy(serverName, args[3]);

					if(minProcs <= 0 || maxProcs <= 0){
						printf("\nInvalid Command. Format for command:\n\n\tcreateServer [minimum processes] [maximum processes] [server-name]\n\n");
						
					} else {
						
						createServer(minProcs, maxProcs, serverName);	
					}

				} else {

					printf("\nInvalid Command. Format for command:\n\n\tcreateServer [minimum processes] [maximum processes] [server-name]\n\n");

				}
				

			// abort server
			} else if(strcmp(args[0], "abortServer") == 0){
					
				abortServer(args[1]);
				
				printf("\nabortServer.\n\n");




			} else if(strcmp(args[0], "createProcess") == 0){
				printf("\ncreateProcess.\n\n");



			} else if(strcmp(args[0], "abortProcess") == 0){
				printf("\nabortProcess.\n\n");


			} else if(strcmp(args[0], "displayStatus") == 0){
				printf("\ndisplayStatus.\n\n");

			} else {

				printf("\nInvalid Command. Possible commands:\n\tcreateServer [minimum process] [maximum process] [server-name]\n\nPlease try again, or use ctrl-c to quit.\n\n");
			}
		}
	}

}
