//TP Synthese ENSEA in the Shell
//Question 2
//BLARET julien and LABROUSSE Sédrenn on 28/11/24.
//

#include "question2.h"
#include <sys/wait.h>
#include <stdint.h>

void welcome(){
    //Input-output block for messages and commands
    char* welcome_message = "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %";


    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
}

void command_input()
{   while(1)
    {
        int status;
        char command_input[100];
        int rt;
        rt=read(STDIN_FILENO, command_input, 100);
        pid_t pid = fork();
        command_input[rt - 1] = '\0';
        // Replace the '\n' from the Enter key with '\0' to mark the end of the string
        if(pid == 0)
        {
            command_execution(command_input);
        }
        else
        {
            wait(&status);
            write(STDOUT_FILENO, "enseash %", strlen("enseash %"));
        }
    }
}

void command_execution(char *command_input)
{
    int text_size = 0;
    char buffer[100];
    if(-1 == execlp(command_input, command_input, (char *)NULL)){
        write(STDOUT_FILENO,"ERROR\n",strlen("ERROR\n"));
    }
    exit(0);
}
