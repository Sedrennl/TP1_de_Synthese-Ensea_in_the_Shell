//
// Created by julien on 28/11/24.
//

#include "question2.h"

void welcome(){
    //Bloc entrée sortie de message et commandes
    char* welcome_message = "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %";


    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
}

void command_input()
{
    char* command_input;
    read(0, &command_input, sizeof command_input);
    pid_t pid = fork();
    if(pid == 0)
    {
        execlp("ls", "ls", "-l", (char*) NULL);
    }

}
