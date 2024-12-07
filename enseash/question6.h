//TP Synthese ENSEA in the Shell
//Question 5
//BLARET julien and LABROUSSE Sédrenn on 06/12/24.
//

#ifndef QUESTION6_H
#define QUESTION6_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define MAX_SIZE 6

void welcome(void);
void command_input(void);
void command_execution(char **argv);

#endif //QUESTION6_H