#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigchld_handler(int signum) {
    int status;
    pid_t pid;
    // Reap all terminated child processes
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Handle terminated child process
        printf("Child process %d terminated\n", pid);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler; // Set the handler function
    sa.sa_flags = SA_RESTART; // Restart interrupted system calls
    sigemptyset(&sa.sa_mask); // Clear the signal mask

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Create a child process
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("Child process executing...\n");
        sleep(2); // Simulate some work
        printf("Child process exiting...\n");
        exit(0);
    } else if (pid > 0) {
        // Parent process
        printf("Parent process waiting...\n");
        sleep(5); // Parent process waits for child to finish
        printf("Parent process exiting...\n");
    } else {
        // Error
        perror("fork");
        exit(1);
    }

    return 0;
}
