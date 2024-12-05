// TP Synthesis ENSEA in the Shell
// Question 2
// BLARET Julien and LABROUSSE Sédrenn on 28/11/24.

#include "question2.h"
#include <sys/wait.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100         // Maximum input size
#define WELCOME_MESSAGE "Welcome to the ENSEA Shell\nTo exit, type 'exit'\nenseash %"
#define ERROR_MESSAGE "ERROR\n"

// Function prototypes
void welcome();
void command_input();
void command_execution(char *command_input);
void handle_error(const char *message);

void welcome() {
    // Input-output block for messages and commands
    if (write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE)) == -1) {
        handle_error("Failed to write welcome message.");
    }
}

void command_input() {
    char command_input[BUFFER_SIZE];

    while (1) {
        int status;
        pid_t pid;
        int rt;

        // Read user input
        rt = read(STDIN_FILENO, command_input, BUFFER_SIZE);
        if (rt <= 0) {
            handle_error("Failed to read user input or EOF detected.");
            break;
        }

        // Replace the '\n' from the Enter key with '\0' to mark the end of the string
        command_input[rt - 1] = '\0';

        // Create a new process
        pid = fork();
        if (pid == -1) {
            handle_error("Fork failed.");
            continue;
        }

        if (pid == 0) {
            // Child process: Execute the command
            command_execution(command_input);
        } else {
            // Parent process: Wait for child and retrieve its exit status
            if (wait(&status) == -1) {
                handle_error("Wait failed.");
            }

            // Display dynamic prompt with exit code
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                char prompt[BUFFER_SIZE];
                snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", exit_code);
                write(STDOUT_FILENO, prompt, strlen(prompt));
            } else {
                write(STDOUT_FILENO, "enseash %", strlen("enseash %"));
            }
        }
    }
}

void command_execution(char *command_input) {
    // Execute the command using execlp
    if (execlp(command_input, command_input, (char *)NULL) == -1) {
        write(STDOUT_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
        exit(EXIT_FAILURE);
    }
}

void handle_error(const char *message) {
    // Print error message and exit the program
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    welcome();
    command_input();
    return 0;
}
