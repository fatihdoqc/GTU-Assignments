#include "log.h"

int fd;

void log_it(char* logname, char* str){

    time_t current_time;
    struct tm *local_time;
    char time_string[1024]; 

    current_time = time(NULL);

    local_time = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%d/%m/%y %H:%M:%S   ", local_time);
    strcat(time_string, str);

    fd = open(logname, O_CREAT | O_WRONLY | O_APPEND , 0666);
    write(fd, time_string, strlen(time_string));
    close(fd);
}