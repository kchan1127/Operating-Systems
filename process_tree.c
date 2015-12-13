//Vincent Chau && Kevin Chan
//ECS150 P1 process_tree
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void processTree(int level)
{
	int status;
  	int leftchild = 0, rightchild = 0;
		
	//Base Case, Depth = 0
	if(level==0)
		return;

	//Create Processes
	leftchild = fork();		

	if(leftchild==0) 
	{	
		
		printf("My Process Identifier is: %d\n", getpid());
		
		//Recursive call
		processTree(level-1);
		
	} 
	else if (leftchild > 0) 
	{	
		int status;
		rightchild = fork();
		
		//Recursive call
		if(rightchild == 0)
			processTree(level-1);
		
	} 
	else 
	{
		perror("Fork Error\n") ;
		exit(1);		
	}

}



int main(int argc, char **argv) 
{
	//int status;
	int n = atoi(argv[1]);
	
	processTree(n);	

  	sleep(3);
  
  	return 0;
}	
