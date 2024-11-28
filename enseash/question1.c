//
// Created by julien on 28/11/24.
//
#include"question1.h";

#include <string.h>

void welcome()
{
    char* welcome_message = "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %";
    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
}
