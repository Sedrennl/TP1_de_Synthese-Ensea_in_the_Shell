//TP Synthese ENSEA in the Shell
//Question 2
//BLARET julien and LABROUSSE Sédrenn on 28/11/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#ifndef QUESTION2_H
#define QUESTION2_H
#endif //QUESTION2_H
#define MAX_SIZE 6
void welcome(void);
void command_input(void);
void command_execution(char *command_input);
