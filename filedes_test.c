// Vincent Chau && Kevin Chan
// ECS150 - file descriptor test
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

pid_t pid1, pid2;

int main()
{
	/*
	File-descriptor-test that  demonstrates  that  file  File-descriptor-test
	in  a  parent  and  child  process  have  the  same  meaning  immediately  
	after  fork  returns  but  changes  to  file  descriptors  in  one  process 
	do  not  impact  the  other.
	*/
	printf("File Descriptor Test\n");

    int fd, status;
    		
    // Create a output file
    fd = open("file1.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    

    	switch(fork())
    	{
    		case -1: 
  					perror("Fork Call #1");
					
					exit(1);
    		case 0:
    				pid1 = getpid();

    				write(fd, "I'm the CHILD writing on the same file immediately after fork\n", 63);
					
					write(fd, "Child: I have a copy of my parents file descriptor table\n", 58);
					
					// Change variable fd, the file descriptor after fork.
					// Does not affect parent process, parent still writes to file1.txt 
					fd = open("file2.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);

					// Child writes to file2.txt, while parent writes to file1
					//This shows that their file descriptor tables are independent after fork();
					write(fd, "I'm child and im writing independently\n",40);

        			exit(0);

    		default:
    				wait(&status); // wait until child is done
					
					pid2 = getpid();
					// fd is still pointing to file1 even after child changed variable fd
					// the filedescriptor tables are independent after fork!!!
					write(fd, "I'm the PARENT writing on the same file immediately after fork\n", 64);
    	}

	
}