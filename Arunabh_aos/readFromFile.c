#include "readFromFile.h"

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/types.h> 
#include <sys/stat.h> 

// Function to read data from a file starting from a specified offset and of a specified size
// Input Format: ./a.out read test1.txt 5 20
// Output: File data read from file: e all of the things,

void readFromFile(char* fileName, int offset, int size) {
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror("Error in opening file: File doesnot exit. Exiting... ");//perror shows standard errors
        exit(1);					
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Error seeking file: offset claculation might have exceeded the limits of the file size. Exiting ...");
        close(fd);
        exit(1);					
    }

    char* buffer = (char*)malloc(size+1);     // allocate memory of size: amount to read
    int bytesRead = read(fd, buffer, size);  // read data from a file 
    if (bytesRead == -1) {
        perror("Error reading from file");
        close(fd);
        free(buffer);  
        exit(1);
    }
    buffer[bytesRead] = '\0';   // add a null character at the end
    printf("File data read from file: %s\n", buffer);

    close(fd);
    free(buffer); 
}
