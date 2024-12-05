/**
 * @file functions.c
 * @author Josh Gillum
 * @brief Function definitions for additional misc. functions used for tail.
 * @version 1.0
 * @date 2024-09-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "functions.h"


/**
 * @brief Prints the help message that is displayed when the user does not correctly specify the arguments. Then exits program
 * 
 * @param name Name of the executable.
 */
void printHelp(char* name){
    write(STDOUT_FILENO,name,strlen(name));
    char* format1 = " <file> -n [+]<numlines>\nEx: ";
    write(STDOUT_FILENO,format1,strlen(format1));

    write(STDOUT_FILENO,name,strlen(name));
    char* format2 = " test.txt -n 20\nEx: ";
    write(STDOUT_FILENO,format2,strlen(format2));
    
    write(STDOUT_FILENO,name,strlen(name));
    char* format3 = " test.txt -n +20\nWill print last <numlines> lines of <file>. If \'+\' preceeds <numlines>, will instead start printing at <numlines> line.\n";
    write(STDOUT_FILENO,format3,strlen(format3));

    exit(1);
}

/**
 * @brief Prints an error message, as specified by errno. Then exits program.
 * 
 * @param message String to preceed the error message
 */
void printError(char* message){
    write(STDOUT_FILENO,message,strlen(message)); // Prints specified string
    write(STDOUT_FILENO,": ",2);

    // Prints the error message
    char* error = strerror(errno);
    write(STDOUT_FILENO,error,strlen(error));
    write(STDOUT_FILENO,"\n",1);

    exit(1);
}