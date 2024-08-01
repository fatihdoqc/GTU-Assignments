#include "utilities.h"

#define CLI_SEM "max_client_semaphore"

volatile sig_atomic_t child_returned = 0;
int client_num = 0;
struct client *clients;

sem_t *sem1, *sem2, *seml;
char *cli_addr;

void cleanChilds();
int doCommand(char *string);
void helpCommand();

void sigchld_handler()
{
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
}


void sigint_handler() {

    char sem_name[64];
    printf("\nSIGINT received. Exiting.\n");
    cleanChilds();  
    sem_unlink(CON_SEM);
    sem_unlink(CLI_SEM);
    sprintf(sem_name, "server_shm_%d",getpid());
    shm_unlink(sem_name); 
       
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

    if (argc < 3)
    {
        perror("Wrong usage! Correct usage : neHosServer <dirname> <max. #ofClients>");
        exit(EXIT_FAILURE);
    }

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


    

    int fd, fd2, maxClient = atoi(argv[2]),
        maxClientQueue = maxClient * 2;
    char* addr;
    char buf[1024], buf2[1024];
    struct stat st;

    clients = (struct client*) calloc(maxClient, sizeof(struct client));
    if (stat(argv[1], &st) == -1) {
        if(mkdir(argv[1], 0700) != 0){
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    }

    DIR *dir = NULL;
    dir = opendir(argv[1]);
    if(dir == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "server_shm_%d",getpid());
    fd = shm_open(buf, O_RDWR | O_CREAT, 0666);
    if(fd == -1)
        perror("shm_open");

    if(ftruncate(fd, SHM_SIZE) == -1)
        perror("ftruncate");

    addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_t * con_sem = sem_open(CON_SEM, O_CREAT, 0666, 0);
    sem_t * max_cli_sem = sem_open(CLI_SEM, O_CREAT, 0666, maxClient);

    sprintf(buf, ">> Server Started PID %d…\n",getpid());
    write(STDOUT_FILENO, buf, sizeof(buf));
    write(STDOUT_FILENO,"Waiting for clients...\n", sizeof("Waiting for clients...\n"));
    while (1) {
        sem_wait(con_sem); // down the semaphore to access server shared memory.
        int curr_cli_index = client_num;
        client_num = (client_num + 1) % maxClientQueue; // increment the client number if exceeds the max queue, go to head.

        clients[curr_cli_index].client_pid = *((pid_t *) addr);

        memset(buf, 0 , sizeof(buf));
        sprintf(buf, "client_shm_%d",clients[curr_cli_index].client_pid);

        fd2 = shm_open(buf, O_RDWR | O_CREAT, 0666);

        if(ftruncate(fd2, SHM_SIZE + 1) == -1)
            perror("fruntace");

        cli_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);

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

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "sem_1_%d", clients[curr_cli_index].client_pid); // client reads
            sem1 = sem_open(buf, 0666);

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "sem_2_%d", clients[curr_cli_index].client_pid); // client writes
            sem2 = sem_open(buf, 0666);

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "sem_l_%d", clients[curr_cli_index].client_pid); // client writes
            seml = sem_open(buf, 0666);

            memset(buf, 0 , sizeof(buf));
            sprintf(buf, "Client PID %d connected as \"client%d\"\n", clients[curr_cli_index].client_pid, curr_cli_index);
            write(STDOUT_FILENO, buf, strlen(buf));

            sem_post(sem2);  
            char *str;

            while(1){
                char *buf;

                sem_wait(sem1);
                write(STDOUT_FILENO, "SEM1YI GECTIM\n", sizeof("SEM1YI GECTIM\n"));


                buf = (char *) cli_addr;

                write(STDOUT_FILENO, buf, strlen(buf));


                /*int ret = doCommand(str);
                if(ret == 1){
                    break;
                }*/

                char res[] = "response.";

                write(STDOUT_FILENO, "SSSEM1YI GECTIM\n", sizeof("SSSEM1YI GECTIM\n"));
                
                memcpy(cli_addr, res, sizeof(res));
                sem_post(sem2);  // Signals the shared memory can be read now.
                //free(str);
            }

            sprintf(buf, "client%d disconnected..\n",curr_cli_index);
            write(STDOUT_FILENO, buf, strlen(buf));

            sem_post(max_cli_sem); 

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "sem_1_%d", clients[curr_cli_index].client_pid);
            sem_unlink(buf);

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "sem_2_%d", clients[curr_cli_index].client_pid);
            sem_unlink(buf);

            
            close(fd);
            close(fd2);
            exit(EXIT_SUCCESS);
        } 
    }

    close(fd);
    close(fd2);
    sem_close(con_sem);
    sem_close(max_cli_sem);
    return 0;
}

/*int doCommand(char *string){

    if(strcmp(string, "help") == 0){
        helpCommand();
        return 0;
    }
    else if(strcmp(string, "quit") == 0){
        return 1;
    }
    return 0;
}*/

/*void helpCommand(){
    char *str = "\n\nAvailable comments are :help, list, readF, writeT, upload, download, archServer,quit, killServer\n";
    send(str);
}*/
