#ifndef CREATE_H
#define CREATE_H
#include <sys/types.h>
void createFileOrPipe(char* choice, char *filename, int permissions);
#endif
/*
#ifndef CREATE_H: This line checks whether the macro symbol CREATE_H has not been defined previously. If CREATE_H has not been defined, the code within the #ifndef block will be included.

#define CREATE_H: This line defines the macro symbol CREATE_H. By defining this symbol, subsequent inclusions of the same header file will be able to identify that it has already been included once.
*/