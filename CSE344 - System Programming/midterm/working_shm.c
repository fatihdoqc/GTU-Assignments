//server:
    /*int fd;
    char *addr;

    fd = shm_open("deneme", O_RDWR | O_CREAT, 0666);
    if(fd == -1)
        perror("shm_open");

    if(ftruncate(fd, SHM_SIZE) == -1)
        perror("fruntace");

    addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(addr == MAP_FAILED)
        perror("addr");

    if (close(fd) == -1)
    {
        perror("close");
    }

    write(STDOUT_FILENO, "Copying" , sizeof("Copying"));
    memcpy(addr, "message", sizeof("message"));

    sleep(5);

    // Unmap and unlink shared memory
    //shm_unlink("deneme");

    exit(EXIT_SUCCESS);*/

// client 

/* #include <stdio.h>
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

#define SHM_SIZE 1024

int main(){

    int fd;
    char *addr;

    fd = shm_open("deneme", O_RDONLY, 0);

    addr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, fd , 0);

    close(fd);

    write(STDOUT_FILENO, addr, SHM_SIZE);
    exit(EXIT_SUCCESS);
    return 0;
}
*/

/*
// semaphore oluştur her client için, max client sayısı 2 şimdilik
    // her client geldiğinde forkla 

    /*
        char sem_name[64];
        snprintf(sem_name, “sem_%d”, pid);
        sem_t *sem = sem_open(sem_name, O_CREAT, 0666);
    */
   

   /*
   #include "utilities.h"

#define CLI_SEM "max_client_semaphore"

volatile sig_atomic_t child_returned = 0;
int client_num = 0;
struct client clients[MAX_CLIENT_QUEUE];


void cleanChilds();

void sigchld_handler()
{
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
}


void sigint_handler() {

    printf("\nSIGINT received. Exiting.\n");
    cleanChilds();  
    sem_unlink(CON_SEM);
    sem_unlink(CLI_SEM);
    shm_unlink("sh_memory"); 
       
    exit(EXIT_SUCCESS);
}

void cleanChilds(){
    int status;
    pid_t pid;
    while((pid = waitpid(-1 , &status, 0)) > 0){
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
    }
}

int main(){

    struct sigaction sa_chld, sa_int;
    
    /*sa_chld.sa_handler = sigchld_handler;
    sigfillset(&sa_chld.sa_mask);
    sa_chld.sa_flags = 0;

    if (sigaction(SIGCHLD, &sa_chld, NULL) == -1) {
        perror("sigchld sigaction");
        exit(EXIT_FAILURE);
    }*/

    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

    int fd;
    char* addr;
    char buf[256];

    fd = shm_open("sh_memory", O_RDWR | O_CREAT, 0666);
    if(fd == -1)
        perror("shm_open");

    if(ftruncate(fd, SHM_SIZE) == -1)
        perror("fruntace");

    addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_t * con_sem = sem_open(CON_SEM, O_CREAT, 0666, 0);
    sem_t * max_cli_sem = sem_open(CLI_SEM, O_CREAT, 0666, MAX_CLIENT);

    printf("Waiting for clients...\n");
    while (1) {
        sem_wait(con_sem);
        int curr_cli_index = client_num;
        client_num = (client_num + 1) % MAX_CLIENT_QUEUE; // increment the client number if exceeds the max queue, go to head.

        clients[curr_cli_index].client_pid = *((pid_t *) addr);
        int temp_value;
        sem_getvalue(max_cli_sem, &temp_value);

        if(temp_value == 0){
            memset(buf, 0 , sizeof(buf));
            sprintf(buf, "Connection request PID %d... Queue full.\n", clients[curr_cli_index].client_pid);
            write(STDOUT_FILENO, buf, strlen(buf));
        }
        sem_wait(max_cli_sem);

        pid_t pid = fork();

        clients[curr_cli_index].child_pid = pid;

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            char sem_name[64];
            snprintf(sem_name, sizeof(sem_name), "sem_%d", clients[curr_cli_index].client_pid);
            sem_t *sem = sem_open(sem_name, 0);

            sem_post(sem);  

            memset(buf, 0 , sizeof(buf));
            sprintf(buf, "Client PID %d connected as client%d\n", clients[curr_cli_index].client_pid, curr_cli_index);
            write(STDOUT_FILENO, buf, strlen(buf));

            sleep(1);
            
            sem_wait(sem);

            memset(buf, 0 , sizeof(buf));
            sprintf(buf, "Client%d disconnected.\n",curr_cli_index);   
            write(STDOUT_FILENO, buf, strlen(buf));

            sem_post(max_cli_sem);  

            exit(EXIT_SUCCESS);
        } 
    }
    
    /*
        printf("Waiting for clients...\n");
    sem_wait(con_sem);
    client_pids[client_num++] = *((pid_t *) addr);
    printf("Client PID %d connected as client%d\n",client_pids[client_num-1],client_num);
            */
    sem_close(con_sem);
    sem_close(max_cli_sem);
    return 0;
}

   */