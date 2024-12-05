//TP Synthese ENSEA in the Shell
//Question 1
//Blaret julien and LABROUSSE Sédrenn on 28/11/24.
//
#include"question1.h";



void welcome()
{
    //Input-output block for messages and commands
    char* welcome_message = "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %";
    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
}
