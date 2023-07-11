#include <stdio.h>   
#include <stdlib.h>  
#include <unistd.h> 
#include <fcntl.h>  
#include <sys/types.h>  
#include <string.h>  

// including all the defined functions used
#include "createFileOrPipe.h"
#include "readFromFile.h"
#include "writeToFile.h"
#include "displayStats.h"
#include "copyFile.h"
#include "communication.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: Insufficient arguments passed. Required: %s createFile [todo] [arguments]\n", argv[0]);//remove createfile
        return 0;
    }

    char* todo = argv[1];

    if (strcmp(todo, "create") == 0) {   // Create a file
        if (argc < 5) {
            printf("Error: Insufficient arguments passed. Required: %s create [file/pipe] [name] [permissions]\n", argv[0]);//correct order choice,name,permissions 
            return 0;
        }
        char* choice = argv[2]; 
        char* name = argv[3];
        int permissions = strtol(argv[4], NULL, 8); // strtol to convert string to mode and 8: Number Base (Octal format: '0666')
        createFileOrPipe(choice, name, permissions);
    }

    else if (strcmp(todo, "read") == 0) {
        if (argc < 5) {
            printf("Error: Insufficient arguments passed. Required: %s read [file_name] [offset] [amount_to_read]\n", argv[0]);
            return 0;
        }

        char* fileName = argv[2];
        int offset = atoi(argv[3]);
        int amountToRead = atoi(argv[4]);
        readFromFile(fileName, offset, amountToRead);
    }

    else if (strcmp(todo, "write") == 0) {
        if (argc < 5) {
            printf("Error: Insufficient arguments passed. Required: %s write <file_name] [offset] [data]\n", argv[0]);
            return 0;
        }

        char* fileName = argv[2];
        int offset = atoi(argv[3]);
        char* data = argv[4];
        writeToFile(fileName, offset, data);
    }

    else if (strcmp(todo, "displayStats") == 0) {
        if (argc < 3) {
            printf("Error: Insufficient arguments passed. Required: %s displayStats [file_name]\n", argv[0]);
            return 0;
        }
        char* fileName = argv[2];
        displayStats(fileName);
    }

    else if (strcmp(todo, "copy") == 0) {
        if (argc < 4) {
            printf("Error: Insufficient arguments passed. Required: %s copy [source_file] [destination_file]\n", argv[0]);//copy
            return 0;
        }

        char* sourceFile = argv[2];
        char* destinationFile = argv[3];
        copyFile(sourceFile, destinationFile);
    }

    else if (strcmp(todo, "communication") == 0) {
        if (argc < 4) {
            printf("Error: Insufficient arguments passed. Required: %s communication [pipe_name] [mode] //if_write_mode[msg]\n", argv[0]);
            return 0;
        }

        char* pipeName = argv[2];
        int mode = atoi(argv[3]);
        char* message = "";
            
        if (mode == O_WRONLY) {//already defined by headerfile wronly:1, rdonly:0 (checked)
            if (argc < 5) {
                printf("Error: Insufficient arguments passed. Required: %s communication [pipe_name] [mode] [message]\n", argv[0]);
            }
            message = argv[4];
        }
        communication(pipeName, mode, message);
    }
    
    return 0;
}
