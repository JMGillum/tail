/**
 * @file tail.c
 * @author Josh Gillum
 * @brief Definition of tail function
 * @version 1.0
 * @date 2024-09-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "tail.h"

/**
 * @brief Either prints the last n lines of a file or starts printing at line n of file.
 * 
 * @param path String of the path to file
 * @param numlines Number of lines to print. Negative number is treated the same as a positive
 * @param startline The line to start at. If -1, will print last numlines lines.
 */
void tail(char* path, int numlines, int startline){

    int fd = open(path,O_RDONLY); // File descriptor for file opened
    if(fd == -1){
        printError("Opening file");
        exit(1);
    }

    char buffer[4097]; // One larger than read size, so null terminator can be placed at the end.
    size_t size = sizeof(char)*4096; // Used to specify how many bytes to read.
    int bytesRead; // Stores the number of bytes actually read.
    int totalLines = 0; // Stores the number of occurences of '\n' in the file
    char last; // Stores the last character of the previous buffer. Used to determine if a newline was printed on the last line.

    // Counts the number of lines in the file.
    while((bytesRead = read(fd,buffer,size)) > 0){
        for(int i = 0; i < bytesRead; ++i){ // Loops through every character, looking for newlines.
            if(buffer[i] == '\n'){ // Increments the number of newlines found
                ++totalLines;
            }
        }
        last = buffer[bytesRead-1]; // Stores the last character read
        // buffer[bytesRead] = '\0';
    }

    if(bytesRead == -1){ // Some sort of error in reading occured
        printError("Reading file");
        close(fd);
        exit(1);
    } else if(last != '\n'){ // Counts last line of file if it isn't terminated by a '\n'
        ++totalLines;
    }


    if(lseek(fd,SEEK_SET,0) < 0){ // Seeks back to the beginning of the file. Return value of -1 indicates error
        printError("Seeking");
        close(fd);
        exit(1);
    }

    int currentLine = 1; // Stores which line is currently being read
    int printing = 0; // Bool indicating whether it is time to start printing
    char* start = NULL; // Starting address of line to print
    int offset = 0; // Number of chars from start of buffer that line starts at.
    if(numlines < 0){ // gets absolute value of numlines.
        numlines = 0 - numlines;
    }
    if(numlines >= totalLines){ // if user wants to print more lines than are in file. Simply set to printing mode.
        printing = 1;
    }
    if(startline == 0 || startline == 1){ // Simply set to printing mode if user wants to start printing on first line.
        printing = 1;
    }
    // Decides when to start printing
    while((bytesRead = read(fd,buffer,size)) > 0){
        if(!printing){
            // Loops through each character in buffer, counting newlines
            for(int i = 0; i < bytesRead; ++i){
                if(buffer[i] == '\n'){
                    ++currentLine;
                    if(currentLine > (totalLines-numlines) || (startline >= 0 && currentLine >= startline)){ // When the current line is equal to the line that printing starts at
                        printing = 1; // Set to printing mode
                        if(i < (bytesRead-1)){ // If newline wasn't the last character in buffer
                            start = &buffer[i+1]; // Point to start of next line
                            offset = i + 1; // Offset is num chars from start to pointer.
                            break;
                        }
                    }
                }
            }
        } else {
            start = buffer; // If simply in printing mode, point to start of buffer and will print whole buffer
        }
        last = buffer[bytesRead-1];
        buffer[bytesRead] = '\0'; // Null terminates buffer

        if(printing == 1 && start != NULL){
            if(offset <= 0){
                write(STDOUT_FILENO,start,bytesRead); // Prints whole buffer, up to the number of bytes read
            } else{
                write(STDOUT_FILENO,start,((bytesRead/sizeof(char))-offset)); // Starts printing at start of newline and prints until end of buffer
            }
            offset = 0;
        }

        
    }

    if(bytesRead == -1){ // Some error occured while reading.
        printError("Reading file");
        close(fd);
        exit(1);
    } else if(last != '\n'){ // Prints newline if needed
        write(STDOUT_FILENO,"\n",1);
    }


    close(fd);

}