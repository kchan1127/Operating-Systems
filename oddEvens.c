// Vincent Chau & Kevin Chan
// ECS150 - odd_then_evens Lab 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#define BUFSIZE 1024	

int main(int argc, const char **argv)
{

	int fd;
	
	ssize_t nread, nread2;
	
	char buf[BUFSIZE], let;
	
	if((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error: Couldn't open %s\n", argv[1]);
		exit(1);
	}

	//store into buffer
	if((nread = read(fd, buf, sizeof(buf)) > 0));

	//reset position
	lseek(fd, 0 , SEEK_SET);

	//filter lines
	int lineCount = 0, letterCount = 0, index[BUFSIZE];

	//read again to locate \n's since read takes in garbage values
	while((nread2 = read(fd, &let, 1)) > 0)
	{
		// find lines and store to index array
		if(let == '\n')
		{
			index[lineCount] = letterCount; 
			lineCount++; 
		}

			letterCount++; 
	}

	int k = 0, l = 0, p = 0;
	
	for(p = 0; p<index[0]; p++) // Print Line 0
	
		printf("%c", buf[p]);


	for(l = 0; l<lineCount-1; l++) // Find & Print Odd
	
		if(l % 2 == 1) 
 	
 			for(k = index[l]; k < index[l+1]; k++)
 	
 				printf("%c", buf[k]);


	int i = 0, j = 0;
	
	for(j = 0; j<lineCount-1; j++) // Find & Print Even
	
		if(j % 2 == 0) 
 	
 			for(i = index[j]; i < index[j+1]; i++)
 	
 				printf("%c", buf[i]);
	
	printf("\n");	
	
	close(fd); // close filedes
	
	return 0;	
}
	