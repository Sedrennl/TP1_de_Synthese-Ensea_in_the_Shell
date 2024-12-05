//TP Synthese ENSEA in the Shell
//Question 2
//BLARET julien and LABROUSSE Sédrenn on 28/11/24.
//

#include "question2.h"
#include <sys/wait.h>
#include <stdint.h>

#define BUFFER_SIZE 100         // Maximum input size
#define WELCOME_MESSAGE "Welcome to the ENSEA Shell\nTo exit, type 'exit'\nenseash %"
#define ERROR_MESSAGE "ERROR\n"

// Display a welcome message to the user
void welcome(){
    // Input-output block for messages and commands
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

// Main loop for reading and executing user commands
void command_input(){   
    while(1){
        int status;                        // To store the child process status
        char command_input[BUFFER_SIZE];  // Buffer to store the user command
        int rt;                           // Return value of read()

        // Read user input from the standard input
        rt=read(STDIN_FILENO, command_input, BUFFER_SIZE);

        // Create a new process for the command
        pid_t pid = fork();

        // Replace the '\n' from the Enter key with '\0' to mark the end of the string
        command_input[rt - 1] = '\0';
       
        if(pid == 0){
            // In the child process: execute the command
            command_execution(command_input);
        }
        else{
            // In the parent process: wait for the child process to finish
            wait(&status);
            // Display the prompt again after the command is executed
            write(STDOUT_FILENO, "enseash %", strlen("enseash %"));
        }
    }
}

// Execute the user command using execlp
void command_execution(char *command_input){
    int text_size = 0;
    char buffer[BUFFER_SIZE];

    // If the command fails, display an error message
    if(-1 == execlp(command_input, command_input, (char *)NULL)){
        write(STDOUT_FILENO,"ERROR_MESSAGE",strlen("ERROR_MESSAGE"));
    }
    // Terminate the child process after execution
    exit(0);
}
