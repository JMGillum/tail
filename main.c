/**
 * @file main.c
 * @author Josh Gillum
 * @brief C implementation of the tail command.
 * @version 1.0
 * @date 2024-09-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tail.h"
#include "functions.h"


int main(int argc, char** argv) {

    // Ensures arguments are of the correct format.
    if((argc >= 3 && (strcmp(argv[2],"-n") != 0)) || argc != 4){
        printHelp(argv[0]);
    }

    int negative = 0; // Bool value for whether '-' has been detected in numlines argument
    int positive = 0; // Same as negative but for '+'
    char current; // Stores the current character in the array

    // Loops through every character in numlines argument and ensures it is the proper format.
    for(int index = 0; argv[3][index] != '\0'; ++index){
        current = argv[3][index];
        if(current == '+'){
            if(negative || positive){ // Ensures that only one '+' or '-' can occur in the whole string
                printHelp(argv[0]);
            } else {
                positive = 1;
            }
        } else if(current == '-'){
            if(negative || positive){ // Ensures that only one '+' or '-' can occur in the whole string
                printHelp(argv[0]);
            } else {
                negative = 1;
            }
        } else if(!isdigit(current)){ // Ensures that all characters are digits
            printHelp(argv[0]);
        }
    }

    int numlines = atoi(argv[3]); // Returns -1 if value is too large to be stored in datatype.
    if(numlines == -1 && !negative){
        char* error = "line number is too large.\n";
        write(STDIN_FILENO,error,strlen(error));
        exit(1);
    }
    char* path = argv[1];
    if(positive){ // If '+' is detected, print all lines after and including numlines
        tail(path,0,numlines);
    } else { // Otherwise, print last numlines lines.
        tail(path,numlines,-1);
    }


    return 0;
}

