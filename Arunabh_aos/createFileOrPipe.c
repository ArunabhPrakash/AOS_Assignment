#include "createFileOrPipe.h"

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <string.h>

// Input: ./a.out create file ~/file1.txt 0666, we creating in root so we get all permissions,if mounted path then permissions snatched
// Output: file /home/ritika/file1.txt 438File created successfully.

// Input: ./a.out create pipe ~/demoPipe 0666
// Output: pipe /home/ritika/demoPipe 438Pipe created successfully.

void createFileOrPipe(char* choice, char *filename, int permissions)
{
    printf("%s %s %d",choice, filename, permissions);
    if(strcmp(choice, "file")){
        umask(0); // for ubuntu mounting, prevent slashing of rights
        int fd = creat(filename, permissions);
        if (fd == -1) {
            printf("Error creating file");
            exit(1);
        }
        printf("File created successfully.\n");
        close(fd);
    }
     
    if(strcmp(choice, "pipe")){
        int fd = mknod(filename,  S_IFIFO | permissions, 0); // 0 for device no.In the given code snippet, S_IFIFO is used as a flag in the mknod function to specify the type of the file being created as a FIFO (First-In-First-Out) special file.
        //A FIFO file, also known as a named pipe, is a special type of file that allows interprocess communication (IPC) between two or more processes.
        if (fd == -1) {
            perror("mknod");
            printf("Error creating Pipe\n");
            exit(1);
        }
        printf("Pipe created successfully.\n");
        close(fd);
    }
        
}