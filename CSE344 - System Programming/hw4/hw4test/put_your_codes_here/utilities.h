#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <string.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

struct manager_thread_params{
    char source[256];
    char destination[256];
};

struct buffer{
    int sourcefd;
    int destfd;
    char source_name[256];
    char dest_name[256];
};

#endif