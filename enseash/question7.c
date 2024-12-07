// TP Synthesis ENSEA in the Shell
// Question 7
// BLARET Julien and LABROUSSE Sédrenn on 06/12/24.

#include "question7.h"
#include <sys/wait.h>
#include <stdint.h>

#define BUFFER_SIZE 100         // Maximum input size
#define WELCOME_MESSAGE "Bienvenue dans le shell ENSEA \n\r Pour quitter, tapez 'exit' \n\r enseash %"
#define ERROR_MESSAGE "ERROR\n" // Error message for failed commands
#define DIVISION_NS 1000000     // Convert nanoseconds to milliseconds
#define DIVISION_S 1000         // Convert seconds to milliseconds
#define MAX_ARGUMENTS_NUMBER 10 // Maximum number of arguments

// Display the welcome message
void welcome() {
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}

// Main loop: process user input and execute commands
void command_input() {
    while (1) {
        int status;                        // Child process status
        char command_input[BUFFER_SIZE];  // Buffer for user input
        int rt;                           // Read return value
        char prompt[300];                 // Buffer for the dynamic prompt
        struct timespec tbegin, tstop;    // Start and stop times for execution measurement

        rt = read(STDIN_FILENO, command_input, BUFFER_SIZE); // Read user input
        command_input[rt - 1] = '\0'; // Replace '\n' with '\0'

        // Tokenize the input to split it into arguments
        char *argv[MAX_ARGUMENTS_NUMBER];
        char *token = strtok(command_input, " ");
        int argc = 0;
        while (token != NULL) {
            argv[argc++] = token; // Store arguments in argv
            token = strtok(NULL, " ");
        }

        clock_gettime(CLOCK_REALTIME, &tbegin); // Start execution timer

        pid_t pid = fork(); // Create a child process

        if (pid == 0) { // Child process
            if (strcmp(command_input, "exit") == 0) { // Handle "exit"
                write(STDOUT_FILENO, "Bye bye", strlen("Bye bye"));
                exit(0);
            }
            command_execution(argv); // Execute the command
        } else if (pid > 0) { // Parent process
            if (strcmp(command_input, "exit") == 0) {
                exit(0); // Exit the shell
            }

            wait(&status); // Wait for the child process to complete
            clock_gettime(CLOCK_REALTIME, &tstop); // Stop execution timer

            // Calculate execution time in milliseconds
            long execution_time = (tstop.tv_nsec - tbegin.tv_nsec) / DIVISION_NS;
            execution_time += (tstop.tv_sec - tbegin.tv_sec) * DIVISION_S;

            if (WIFEXITED(status)) { // Normal exit
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d|%ldms] %% ", WEXITSTATUS(status), execution_time);
            } else if (WIFSIGNALED(status)) { // Exit due to signal
                snprintf(prompt, sizeof(prompt), "enseash [sign:%d|%ldms] %% ", WTERMSIG(status), execution_time);
            }
            write(STDOUT_FILENO, prompt, strlen(prompt)); // Display the prompt
        }
    }
}

// Find the position of a specific token in the argument list
int findCharPosition(char *str[], const char *target) {
    for (int i = 0; i < MAX_ARGUMENTS_NUMBER; i++) {
        if (str[i] == target) {
            return i; // Return the position if found
        }
    }
    return -1; // Return -1 if not found
}

// Execute a command in the child process
void command_execution(char **argv) {
    int inRedirectPosition = findCharPosition(argv, "<");  // Check for input redirection
    int outRedirectPosition = findCharPosition(argv, ">"); // Check for output redirection

    if (inRedirectPosition == -1 && outRedirectPosition == -1) { // No redirection
        if (execvp(argv[0], argv) == -1) {
            write(STDOUT_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
            exit(0);
        }
    } else if (inRedirectPosition == -1) { // Handle output redirection
        char *stdout_redirect_filename = argv[outRedirectPosition + 1];
        int fd_output = creat(stdout_redirect_filename, S_IWUSR | S_IRWXG);
        dup2(fd_output, STDOUT_FILENO); // Redirect stdout to the file
        close(fd_output); // Close the file descriptor
        argv[outRedirectPosition] = NULL; // Remove redirection operator from arguments
        if (execvp(argv[0], argv) == -1) {
            write(STDOUT_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
        }
    }
}
