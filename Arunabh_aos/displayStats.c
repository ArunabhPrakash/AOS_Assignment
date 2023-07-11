#include "displayStats.h"

#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h> 

// Function to display file statistics including owner, permissions, inode, and timestamps
// Input Format: ./a.out displayStats test1.txt
// Output: 
// File Statistics Information for file 'test1.txt':
// Owner: 1000
// Permissions: 100777
// Inode: 8725724279012053
// Last Access Time: Tue Jul  4 19:07:46 2023
// Last Modification Time: Tue Jul  4 19:07:46 2023
// Last Status Change Time: Tue Jul  4 19:07:46 2023

void displayStats(char* fileName) {
    struct stat fileStats;
    if (stat(fileName, &fileStats) == -1) {
        perror("Error in getting file stats");
        exit(1);
    }

    printf("File Statistics Information for file '%s':\n", fileName);
    printf("Owner: %d\n", fileStats.st_uid);//int
    printf("Permissions: %o\n", fileStats.st_mode);//octal
    printf("Inode: %lu\n", fileStats.st_ino);//unsigned long
    printf("Last Access Time: %s", ctime(&fileStats.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStats.st_mtime));
    printf("Last Status Change Time: %s", ctime(&fileStats.st_ctime));
}
