#include "utilities.h"

sem_t *sem1, *sem2, *seml;
char *cli_addr;

void cleanChilds();

void sigint_handler() {

    printf("\nSIGINT received. Exiting.\n");
    shm_unlink(CON_SEM);

    char sem_name[64];
    sprintf(sem_name,  "sem_1_%d", getpid());
    sem_unlink(sem_name);
    sprintf(sem_name,  "sem_2_%d", getpid());
    sem_unlink(sem_name);
    sprintf(sem_name,  "client_shm_%d", getpid());
    shm_unlink(sem_name);
    cleanChilds();  
    exit(EXIT_SUCCESS);
}

void cleanChilds(){
    int status;
    pid_t pid;
    while((pid = waitpid(-1 , &status, 0)) > 0){
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]){

    if (argc < 2)
    {
        perror("argc");
        exit(EXIT_FAILURE);
    }

    struct sigaction sa_int;

    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

    int fd, fd2;
    char *addr,  buf[1024], command[1024];

    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "server_shm_%d",atoi(argv[1]));
    fd = shm_open(buf, O_RDWR, 0666);
    if(fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd , 0);

    if(addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    close(fd);

    sem_t *con_sem = sem_open(CON_SEM, 0666);
    if(con_sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "Client pid is %d\n",getpid());
    write(STDOUT_FILENO, buf, strlen(buf));

    pid_t clientPid = getpid();
    memcpy(addr, &clientPid, sizeof(pid_t));
    sem_post(con_sem);

    char sem_name[64];
    snprintf(sem_name, sizeof(sem_name), "sem_1_%d", getpid()); // Unique Semaphore to read from shm.
    sem1 = sem_open(sem_name, O_CREAT, 0666, 0);

    snprintf(sem_name, sizeof(sem_name), "sem_2_%d", getpid()); // Unique Semaphore to write to shm.
    sem2 = sem_open(sem_name, O_CREAT, 0666, 0);

    snprintf(sem_name, sizeof(sem_name), "sem_l_%d", getpid()); // Binary semaphore to access shared memory.
    seml = sem_open(sem_name, O_CREAT, 0666, 1);

    write(STDOUT_FILENO,"Waiting for queue...\n", sizeof("Waiting for queue...\n"));
    sem_wait(sem2);
    write(STDOUT_FILENO,"Connection established.\n", sizeof("Connection established.\n"));

    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "client_shm_%d",clientPid);

    fd2 = shm_open(buf, O_RDWR, 0666);
    if (fd2 == -1)
        perror("fd2");
    
    cli_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd2 , 0);
    if (cli_addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }


    while(1){
        char str[1024], *res;

        write(STDOUT_FILENO, ">> Enter command : ", sizeof(">> Enter command : "));
        read(STDIN_FILENO, str, SHM_SIZE);

        write(STDOUT_FILENO, "SSSEM2YI GECTIM\n", sizeof("SSSEM2YI GECTIM\n"));
        memcpy(cli_addr, str, strlen(str));
        sem_post(sem1);  // Signals the shared memory can be read now.

        write(STDOUT_FILENO, ">> Receiving..", sizeof(">> Receiving.."));

        sem_wait(sem2); // Client reads
        write(STDOUT_FILENO, "SEM2YI GECTIM\n", sizeof("SEM2YI GECTIM\n"));
        res = (char*) cli_addr;

        write(STDOUT_FILENO, res, strlen(res));

    }

// -------finito-------
    //sem_post(sem);

    shm_unlink(CON_SEM);

    sprintf(sem_name,  "sem_1_%d", getpid());
    sem_unlink(sem_name);

    sprintf(sem_name,  "sem_2_%d", getpid());
    sem_unlink(sem_name);

    sprintf(sem_name,  "sem_l_%d", getpid());
    sem_unlink(sem_name);

    //sprintf(sem_name,  "client_shm_%d", getpid());
   // shm_unlink(sem_name);

    close(fd);
    close(fd2);
    exit(EXIT_SUCCESS);
    return 0;
}