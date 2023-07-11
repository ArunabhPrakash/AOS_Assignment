#include "copyFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to copy the content of a source file to a destination file using a pipe
// Input: ./a.out copy test1.txt test2.txt
// Output: Data copied from test1.txt to test2.txt successfully

void copyFile(char* sourceFile, char* destinationFile) {
    // Array to store the two file descriptors: pipefd[0] for reading, pipefd[1] for writing
    int pipefd[2];

    // Attempt to create a pipe
    if (pipe(pipefd) == -1) {
        perror("Error in creating pipe. Exiting...");
        exit(1);
    }

    int pid = fork();// for one process to read and one to write
    if (pid == -1) {
        perror("Error in fork() command.");
        exit(1);
    } else if (pid == 0) {
        // Child Process: Read from the source file and write to the pipe

        close(pipefd[0]);  // Close the read end of the pipe, when created pipe is open

        int sourcefd = open(sourceFile, O_RDONLY);
        if (sourcefd == -1) {
            perror("Error in opening the source file. Exiting...");
            exit(1);
        }

        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(sourcefd, buffer, sizeof(buffer))) > 0) {
            int bytesWritten = write(pipefd[1], buffer, bytesRead);
            if (bytesWritten == -1) {
                perror("Error in writing to the pipe. Exiting...");
                close(sourcefd);
                close(pipefd[1]);
                exit(1);
            }
        }

        close(sourcefd);
        close(pipefd[1]);  // Close the write end of the pipe
        exit(0);
    } else {
        // Parent process: Read from the pipe and write to the destination file

        close(pipefd[1]);  // Close the unused write end of the pipe

        int destinationfd = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (destinationfd == -1) {
            perror("Error in opening the destination file");
            exit(1);
        }

        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            int bytesWritten = write(destinationfd, buffer, bytesRead);
            if (bytesWritten == -1) {
                perror("Error writing to the destination file");
                close(destinationfd);
                close(pipefd[0]);
                exit(1);
            }
        }

        close(destinationfd);
        close(pipefd[0]);
        wait(NULL);  // Wait for the child process to finish

        printf("Data copied from %s to %s successfully\n", sourceFile, destinationFile);
    }
}

