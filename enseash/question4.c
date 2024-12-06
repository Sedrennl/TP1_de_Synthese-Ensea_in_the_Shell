//TP Synthese ENSEA in the Shell
//Question 4
//BLARET julien and LABROUSSE Sédrenn on 28/11/24.
//

#include "question4.h"
#include <sys/wait.h>
#include <stdint.h>

#define BUFFER_SIZE 100         // Maximum size for user input
#define WELCOME_MESSAGE "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %"
#define EXIT_MESSAGE "Bye bye"  // Message displayed when exiting the shell
#define PROMPT "enseash %"      // Prompt displayed after each command
#define ERROR_MESSAGE "ERROR\n" // Message displayed when a command fails

// Display the welcome message to the user
void welcome(){
    // Input-output block for messages and commands
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

// Main loop to read user input and execute commands
void command_input(){
    while(1){
        int status;                       // To store the child process status
        char command_input[BUFFER_SIZE];  // Buffer to store the user command
        int rt;                           // Return value of read()
        char prompt[300];                 // Size prompt
        
        // Read user input from the standard input
        rt=read(STDIN_FILENO, command_input, BUFFER_SIZE);

        // Create a new process for the command
        pid_t pid = fork();

        // Replace the '\n' from the Enter key with '\0' to mark the end of the string
        command_input[rt - 1] = '\0';

        // Check if we are in the child process and the command is not "exit"
        if(pid == 0 && strcmp(command_input, "exit") != 0){
            command_execution(command_input);
        }
        // Check if we are in the child process and the command is "exit"
        else if(pid ==0 && strcmp(command_input, "exit") == 0){
            write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE)); 
            exit(0); // Terminate the child process
        }

        // Check if we are in the parent process and the command is "exit"
        else if(pid >0 && strcmp(command_input, "exit") == 0){
            exit(0); // Terminate the parent process
        }
        // Parent process handling normal commands
        else if (pid > 0 && strcmp(command_input, "exit") != 0){
            wait(&status);// Wait for the child process to finish

            // If the child process exited normally
            if (WIFEXITED(status)){
                int exit_code = WEXITSTATUS(status); // Retrieve the exit code
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", exit_code); // Build dynamic prompt
                write(STDOUT_FILENO, prompt, strlen(prompt)); // Display the prompt
            }

            // If the child process was terminated by a signal    
            else if (WIFSIGNALED(status)){
                 int signal_number = WTERMSIG(status); // Retrieve the signal number
                snprintf(prompt, sizeof(prompt), "enseash [sign:%d] %% ", signal_number); // Build dynamic prompt
                write(STDOUT_FILENO, prompt, strlen(prompt)); // Display the prompt
            }
        }
    }
}

// Execute the given command in the child process
void command_execution(char *command_input){
    int text_size = 0;
    char buffer[BUFFER_SIZE];
    if(-1 == execlp(command_input, command_input, (char *)NULL)){
        write(STDOUT_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
    }
    exit(0);// Terminate the child process
}
