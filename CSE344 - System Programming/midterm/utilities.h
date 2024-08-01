#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <dirent.h>
#include <sys/file.h>

#define CON_SEM "connection_semaphore"
#define MEM_SEM "memory_semaphore"
#define SHM_SIZE 1024

struct client{
    pid_t child_pid;
    pid_t client_pid;
};

#endif /* UTILITIES_H */