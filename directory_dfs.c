//Vincent Chau && Kevin Chan
//ECS150 P1
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define curDir "."
#define prevDir ".."

void getSpaces(int depth)
{
	if(depth == 0)
	{
		printf("    ");
	}
	int i;
	for(i = 0; i < depth * 4; i++)
		printf(" ");
	
}
void dfsDirectory(char *directory ,char *keyFile ,int depth)
{
    DIR *dPtr;

    struct dirent *d;

    // Open directory
    if((dPtr = opendir(directory)) == NULL) 
    {
        fprintf(stderr,"Error on opening directory: %s\n", directory);
        exit(1);
    }

    // Change to next directory
    chdir(directory);

    struct stat sb;
    
    while((d = readdir(dPtr))) 
    {
    	// Check status of path for symbolic links
        if(lstat(d->d_name,&sb) == -1)
        {
        	perror("lstat\n");
        	exit(2);
        }
        // Base case:
        if(strcmp(d->d_name, keyFile) == 0)
    	{
    		
    		getSpaces(depth);
    		printf("%s/\n", keyFile);
    		exit(1);
    	} 

    	// If found directory
        if(S_ISDIR(sb.st_mode)) 
        {
        	// Prevent loop / going back
			if(strcmp(curDir,d->d_name) == 0 || strcmp(prevDir,d->d_name) == 0)
					continue; 

   			getSpaces(depth);
				
			printf("%s/\n", d->d_name);
         	
         	// Recursive call
         	dfsDirectory(d->d_name, keyFile, depth+1);
        }
        else
    		
    		getSpaces(depth);
    		
    		printf("%s\n", d->d_name);
    
    } // end while
    
    // Change Directory 
    chdir(prevDir);

    closedir(dPtr);

}
int main(int argc, char* argv[])
{

	if(argv[1] == NULL)
	{
		printf("Please enter a starting directory\n");
		exit(1);
	}
	if(argv[2] == NULL)
	{
		printf("Please enter a key file\n");
		exit(1);
	}

    dfsDirectory(argv[1], argv[2], 0);
    
    // Goes here if not found
    printf("NOT FOUND\n");

	
	return 0;
}