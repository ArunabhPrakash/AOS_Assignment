#include "writeToFile.h"

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/types.h> 
#include <string.h>


// Function to write data to a file starting from a specified offset
// Input Format: ./a.out write test1.txt 4 "Dandelions"
// Ouptut: Write is performed sucessfully to file test1.txt.

void writeToFile(char* fileName, int offset, char* data) {
    // open file in write only mode
    int fd = open(fileName, O_WRONLY);
    if (fd == -1) {
        perror("Error in opening file: File doesnot exit. Exiting...");
        exit(1);
    }

    // SEEK_SET: relative to the beginning of the file
    // offset: the byte no. read pointer should move to 
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Error seeking file: offset claculation might have exceeded the limits of the file size. Exiting ...");
        close(fd);
        exit(1);
    }

    // Write the data to the file
    int bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Error in writing to file. Exiting ... ");
        close(fd);
        exit(1);
    }

    printf("Write is performed sucessfully to file %s.\n", fileName);
    close(fd);
}
