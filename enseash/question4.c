//TP Synthese ENSEA in the Shell
//Question 2
//BLARET julien and LABROUSSE Sédrenn on 28/11/24.
//

#include "question4.h"
#include <sys/wait.h>
#include <stdint.h>

void welcome(){
    //Bloc entrée sortie de message et commandes
    char* welcome_message = "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %";


    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
}

void command_input()
{
    while(1)
    {
        int status;
        char command_input[100];
        char prompt[300];
        int rt;
        rt=read(STDIN_FILENO, command_input, 100);
        pid_t pid = fork();
        command_input[rt - 1] = '\0';
        // On remplace le '\n' du enter par le '\0' marquant la fin de la chaîne de caractère
        if(pid == 0 && strcmp(command_input, "exit") != 0)//Fils
        {
            command_execution(command_input);
        }
        else if(pid ==0 && strcmp(command_input, "exit") == 0)
        {
            write(STDOUT_FILENO, "Bye bye", strlen("Bye bye"));
            exit(0);
        }
        else if(pid >0 && strcmp(command_input, "exit") == 0)
        {
            exit(0);
        }
        else if (pid > 0 && strcmp(command_input, "exit") != 0)
        {
            wait(&status);
            if (WIFEXITED(status))
            {
                int signal_number = WTERMSIG(status);
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", signal_number);

                write(STDOUT_FILENO, prompt, strlen(prompt));
            }
            else if (WIFSIGNALED(status))
            {
                int signal_number = WEXITSTATUS(status);
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", signal_number);

                write(STDOUT_FILENO, prompt, strlen(prompt));
            }
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
