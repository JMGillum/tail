/**
 * @file tail.h
 * @author Josh Gillum
 * @brief Declaration of tail function
 * @version 1.0
 * @date 2024-09-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TAIL_H
#define TAIL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "functions.h"


void tail(char* path, int numlines, int startline);

#endif