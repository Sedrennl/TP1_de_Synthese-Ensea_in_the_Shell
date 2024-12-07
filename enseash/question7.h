//
// Created by julien on 07/12/24.
//

#ifndef QUESTION7_H
#define QUESTION7_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

#define MAX_SIZE 6

void welcome(void);
void command_input(void);
void command_execution(char **argv);
int findLessthanPosition(const char str[], char target);
#endif //QUESTION7_H
