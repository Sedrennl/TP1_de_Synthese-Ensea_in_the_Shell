//TP Synthese ENSEA in the Shell
//Question 1
//Blaret julien and LABROUSSE Sédrenn on 28/11/24.
//
#include"question1.h";

#define WELCOME_MESSAGE "Welcome to the ENSEA Shell\nTo exit, type 'exit'\nenseash %"

void welcome(){
    //Input-output block for messages and commands
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}
