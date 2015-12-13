//Vincent Chau && Kevin Chan
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>

pid_t pid1, pid2, pid;
int count = 0;

void signal_handler(int sig) //used as a handler
{
	pid_t pid = getpid();
	if(pid == pid1) {
		printf("Count is %d, my pid is %d\n\n", count, getpid());
		count = 0;
	} 
		
	if(pid == pid2){
		printf("Count is %d, my pid is %d\n\n", count, getpid());
		count = 0;
	} 
	
}

void reset()
{
		int count = 0;
}

void parent()
{
	for(count;count<5;count++){
	sleep(1); //sleeps for a second
	kill(0,SIGALRM);
	}
	
	kill(pid1, SIGKILL); // when done, kill signal to all processes 
	kill(pid2, SIGKILL);
}

int main()
{
	static struct sigaction pact,oact;
	pact.sa_handler = signal_handler; //set up action for sig_hand
	sigfillset(&(pact.sa_mask)); //signal is blocked when the sign_hand is being executed
	sigaction(SIGALRM, &pact, &oact); //change action by sig_hand on SIGALRM
	if(sigaction(SIGALRM, &pact,NULL) == -1 && sigaction(SIGALRM, &oact,NULL) == -1){
		perror("Can't handle SIGALRM \n"); //check should never get here
		}
		
	switch(pid = fork())
	{
		case -1: //error
			perror("Fork call #1");
			exit(1);
		case 0: 
			pid1 = getpid(); //child 1
			while(1)
			{
				count++; //keep incrementing count for child 1
			}
			break;
		default:
			switch(pid = fork()){
			case -1: //error
					perror("Fork Call #2");
					exit(1);
			case 0:
				pid2 = getpid(); //child 2
				while(1)
				{
					count++; //keep incrementing count for child 2
				}
				break;
			default:
				parent();	
			}	
	}
	return 0;
}