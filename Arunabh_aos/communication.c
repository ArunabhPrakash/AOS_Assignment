#include "communication.h"

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <string.h>

// Function to create a named pipe for communication between two processes
// input: ./a.out communication ~/myPipe 0
// output: Successfully written data in /home/ritika/myPipe!, writing msg is one sending msg

// input: ./a.out communication ~/myPipe 1 "This is a message for reading process"
// output: Data read from the pipe: This is a message for reading process

void communication(char* pipeName, int mode, char* message) {  

	if(mode == O_RDONLY){//not in infinite loop cause giving problem
		// process with mode == 0 will open named pipe for reading

		int fd = open(pipeName, O_RDONLY);
		if (fd == -1){
			printf("Error opening named pipe for reading. Exiting...\n");
			exit(1);
		}
//      sucessfully opened
		char buffer[1024];
        int bytesRead;

		bytesRead = read(fd, buffer, 1024);

		if (bytesRead == -1) {
            perror("Error in reading from named pipe. Exiting...");
            close(fd);
            exit(1);
        }

		printf("Received message is: %s\n", buffer);
		close(fd);
	}
	else if(mode == O_WRONLY){
		int fd = open(pipeName, O_WRONLY);
		if (fd == -1) {
            perror("Error in openeing named pipe. Exiting ...");
            exit(1);
        }

        int bytesWritten = write(fd, message, strlen(message));

        if (bytesWritten == -1) {
            perror("Error in writing to named pipe. Exiting ...");
            close(fd);
            exit(1);
        }

        printf("Successfully written data in %s!", pipeName);
		close(fd);
	}
}

