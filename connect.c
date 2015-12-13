// Vincent Chau & Kevin Chan
// ECS150 - connect pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <string.h>
#define BUFSIZE 1024

int status, pid ,fd1[2], fd2[2], fd3[2]; 

pid_t pid1, pid2, pid3;

static char buf[BUFSIZE], buf2[BUFSIZE];


//The  first  process  should  prompt  the  user  for  a  string,  
//print  it,  and  then  send  it  to  the  second  process. 
void firstProcess()
{
	// Process one prompt
	printf("Please Enter String: ");
	int k = 0;

	for(k = 0; k < sizeof(buf); k++)
	{
		scanf("%c", &buf[k]);
		buf2[k] = buf[k];
		if(buf[k] == '\n')
			break;
	}
	
	buf[k] = '\0';
	
	buf2[k] = '\0';

	sleep(1);

	printf("Process 1(PID: %d) \n", getpid());

	// close read from file1
	close(fd1[0]); 
	
	// write to process 2
	write(fd1[1], buf, strlen(buf));

	// close write process 3
	close(fd3[1]);

	read(fd3[0], buf, BUFSIZE);

	// concatenate strings
	printf("Concatenate Strings: ");

	printf("%s", buf2);
	
	printf("%s\n", buf);

	// wait for process 2
	waitpid(pid, &status, 0);

	int cmp;
	cmp =strcmp(buf2, buf); // compare function

	printf("(Process 1) After Strcmp: %d\n", cmp);

	printf("Process 1 - Terminate\n");

}
void secondProcess()
{
	sleep(8);
	printf("Process 2(PID: %d)\n", getpid());

	// close process 1 write
	close(fd1[1]);
	
	// read from process 1
	read(fd1[0], buf, BUFSIZE);

	// reverse string
	char temp;

	int j = 0;
	for (j = 0; j < ((strlen(buf)-1) / 2) + 1; j++)
	{
		temp = buf[j];
		buf[j] = buf[(strlen(buf)-1) - j];
		buf[(strlen(buf)-1) - j] = temp;
	}
	
	printf("(Process 2) Reverse: %s\n", buf);

	// close process 3 read
	close(fd2[0]);

	// write down to process 3 
	write(fd2[1], buf, strlen(buf));


	// wait for process 3
	waitpid(pid, &status, 0);

	// 	ADDED: write process 1
	close(fd3[1]);
	
	read(fd3[0], buf, BUFSIZE);

	printf("Process 2 - Terminate\n");

	exit(0);

}
void thirdProcess()
{
	sleep(10);
	printf("Process 3(PID: %d)\n", getpid());
	
	//close process 2 write
	close(fd2[1]);
	
	// read from process 2
	read(fd2[0], buf, BUFSIZE);

	// change to uppercase
	int i = 0;

	for(i = 0; i<strlen(buf); i++)
	{
		if(buf[i] <= 122 && buf[i] >= 97)
			buf[i] = buf[i] - 32;
	}

	printf("(Process 3) Uppercase: %s\n", buf);

	// close process3 read
	close(fd3[0]);       

	write(fd3[1], buf, strlen(buf));

	printf("Process 3 - Terminate\n");
	
	exit(0);

}

int main(int argc, char **argv)
{

	if(pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1)
	{
		perror("Pipe Call\n");
		exit(1);
	}

	switch(pid = fork())
	{
		case -1:
			perror("Fork Call #1");
			exit(2);
		
		case 0:
			switch(pid = fork())
			{
				case -1:
					perror("Fork Call #2");
					exit(1);
				case 0:
					thirdProcess();
				default:
					secondProcess();
							
			}

		default:
			firstProcess();

	}


	return 0;
}