//TP Synthese ENSEA in the Shell
//Question 2
//BLARET julien and LABROUSSE Sédrenn on 06/12/24.
//

#include "question5.h"
#include <sys/wait.h>
#include <stdint.h>

#define BUFFER_SIZE 100         // Maximum size for user input
#define WELCOME_MESSAGE "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %"
#define DIVISION_NS 1000000    // Division factor for execution time ns
#define DIVISION_S 1000        // Division factor for execution time s


// Display the welcome message to the user
void welcome(){
    // Input-output block for messages and commands
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

void command_input(){
    while(1)
    {
        int status;                       // To store the child process status
        char command_input[BUFFER_SIZE];  // Buffer to store the user command
        int rt;                           // Return value of read()
        char prompt[300];                 // Size prompt

        // Structures to store the start and stop times for execution measurement
        struct timespec tbegin, tstop;
        
        // Read user input from the standard input
        rt=read(STDIN_FILENO, command_input, BUFFER_SIZE);

        // Record the start time before the command execution
        clock_gettime(CLOCK_REALTIME, &tbegin);
        
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
            write(STDOUT_FILENO, "Bye bye", strlen("Bye bye"));
            exit(0);
        }

        // Check if we are in the parent process and the command is "exit"
        else if(pid >0 && strcmp(command_input, "exit") == 0){
            exit(0);
        }
            
        // Parent process handling normal commands
        else if (pid > 0 && strcmp(command_input, "exit") != 0){
            wait(&status);// Wait for the child process to finish
            
            clock_gettime(CLOCK_REALTIME, &tstop);
            
            // If the child process exited normally
            if (WIFEXITED(status)){
                int signal_number = WEXITSTATUS(status);// Retrieve the exit code of the child process

                // Calculate execution time in milliseconds
                long execution_time = (tstop.tv_nsec - tbegin.tv_nsec); // Difference in nanoseconds
                execution_time /= DIVISION_NS; // Convert nanoseconds to milliseconds
                execution_time += (tstop.tv_sec - tbegin.tv_sec) * DIVISION_S; // Add seconds converted to milliseconds
                
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d|%ldms] %% ", signal_number,execution_time);// Build dynamic prompt
                write(STDOUT_FILENO, prompt, strlen(prompt));// Display the prompt
            }

            // If the child process was terminated by a signal    
            else if (WIFSIGNALED(status)){
                int signal_number = WTERMSIG(status);
                
                // Calculate execution time in milliseconds
                long execution_time = (tstop.tv_nsec - tbegin.tv_nsec); // Difference in nanoseconds
                execution_time /= DIVISION_NS; // Convert nanoseconds to milliseconds
                execution_time += (tstop.tv_sec - tbegin.tv_sec) * DIVISION_S; // Add seconds converted to milliseconds
                
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d|%ldms] %% ", signal_number,execution_time);// Build dynamic prompt
                write(STDOUT_FILENO, prompt, strlen(prompt));// Display the prompt
            }
        }
    }
}

// Execute the given command in the child process
void command_execution(char *command_input){
    if(-1 == execlp(command_input, command_input, (char *)NULL)){
        write(STDOUT_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
    }
    exit(0);// Terminate the child process
}
