// Vincent Chau && Kevin Chan
// ECS150 - fork variable test
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


int main()
{
/*
	Fork-variable-test
	that  demonstrates  that program  variables  in  a  parent  
	and  child  process  have  the  same  values  immediately  
	after  fork  returns  but  are  then  independent  of  each other.
*/

	int variable;

	int status;
	
	ssize_t nread;
	
	if(write(1, "Please Enter an integer variable: ", 35) == -1)
	{
		perror("Write\n");
		exit(1);
	}

	scanf("%d", &variable);

	pid_t pid = fork();
    	
    	switch(pid)
    	{
    		case -1: 
  					perror("Fork Call #1");
					exit(1);
    		case 0:
    				//if child
    				printf("Child: My variable contains: %d\n", variable);
    				
    				// change variable inside child
    				
    				variable = 0;

    				printf("Child: I Changed The Variable: %d\n", variable);

    				exit(0); // exit child ran successfully

    		default:
    				//if parent
    				wait(&status); // wait until child is done

    				// print variable after fork.
    				printf("Parent: My variable contains: %d\n", variable);	
    				
    				// variables are unchanged by child, they are independent.
    				printf("Parent: My variable is still: %d, even though my child independently changed it.\n", variable);
					
    	}



	return 0;
}