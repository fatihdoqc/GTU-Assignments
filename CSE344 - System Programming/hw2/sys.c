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

int child_counter = 0, *arr;
volatile sig_atomic_t child_returned = 0;
pid_t child_pids[2];

void cleanChilds();

void sigchld_handler()
{
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        child_returned++;
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
    }

    if (child_returned == 2)
    {
        unlink("myfifo1");
        unlink("myfifo2"); 
        free(arr);
        exit(EXIT_SUCCESS);
    }
}


void sigint_handler() {

    printf("\nSIGINT received. Exiting.\n");
    cleanChilds();  
    unlink("myfifo1");
    unlink("myfifo2");
    free(arr);
    exit(EXIT_SUCCESS);
}

void cleanChilds(){
    int status;
    pid_t pid;
    while((pid = waitpid(-1 , &status, 0)) > 0){
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    if (size > 10) {
        printf("Please enter a number less than or equal to 10.\n");
        return 1;
    }

    arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 101;
    }

    printf("Array: [");
    for (int i = 0; i < size; i++)
    {
        if(i != size -1)
            printf("%d, ",arr[i]);
        else
            printf("%d",arr[i]);
    }
    printf("]\n");

    struct sigaction sa_chld, sa_int;
    
    sa_chld.sa_handler = sigchld_handler;
    sigfillset(&sa_chld.sa_mask);
    sa_chld.sa_flags = 0;

    if (sigaction(SIGCHLD, &sa_chld, NULL) == -1) {
        perror("sigchld sigaction");
        exit(EXIT_FAILURE);
    }

    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

	int fd, fd2;

	char * myfifo1 = "myfifo1";
	char * myfifo2 = "myfifo2";

	if(mkfifo(myfifo1, 0666) == -1){
        perror("FIFO1 : ");
        cleanChilds();
        exit(EXIT_FAILURE);
    }
	if(mkfifo(myfifo2, 0666) == -1){
        perror("FIFO2 : ");
        cleanChilds();
        exit(EXIT_FAILURE);
    }
    
	child_pids[child_counter++] = fork();

    if (child_pids[child_counter - 1] == 0)
    {
        int sum = 0;

        int *arr = (int *)malloc(size * sizeof(int));
        if (arr == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        fd = open(myfifo1, O_RDONLY);
        if(fd == -1){
            perror("Opening FIFO1: ");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if(read(fd, arr, sizeof(int) * 5) < 0){
            perror("Reading from FIFO1 : ");
            close(fd);
            exit(EXIT_FAILURE);
        }    
        close(fd);

        sleep(10);

        for (int i = 0; i < size; i++)
        {
            sum += arr[i];
        }

        fd2 = open(myfifo2, O_WRONLY);
        if(fd2 == -1){
            perror("Opening FIFO2: ");
            close(fd2);
            exit(EXIT_FAILURE);
        }
        if(write(fd2, &sum, sizeof(int)) < 0){
            perror("Writing to FIFO2 : ");
            close(fd2);
            exit(EXIT_FAILURE);
        }
        close(fd2);
        free(arr);
        exit(EXIT_SUCCESS);
    }
    else{

        child_pids[child_counter++] = fork();


        if(child_pids[child_counter - 1] == 0){
            char buffer2[100];
            int mul = 1, sum;

            int *arr2 = (int *)malloc(size * sizeof(int));
            if (arr2 == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            memset(buffer2, 0, sizeof(buffer2));
            fd2 = open(myfifo2, O_RDONLY);
            if(fd2 == -1){
                perror("Opening FIFO2: ");
                close(fd2);
                exit(EXIT_FAILURE);
            }

            if(read(fd2, buffer2, sizeof(buffer2)) < 0 ){
                perror("Reading from FIFO2 : ");
                close(fd2);
                exit(EXIT_FAILURE);
            }

            if(read(fd2, arr2, sizeof(int) * 5) < 0){
                perror("Reading from FIFO2 : ");
                close(fd2);
                exit(EXIT_FAILURE);
            }
            close(fd2);

            if(strcmp(buffer2, "multiply") != 0){
                perror("Command to FIFO2 is incorrect ");
                exit(EXIT_FAILURE);
            }

            sleep(10);

            for (int i = 0; i < size; i++)
            {
                mul *= arr2[i];
            }

            fd2 = open(myfifo2, O_RDONLY);
            if(fd2 == -1){
                perror("Opening FIFO2: ");
                close(fd2);
                exit(EXIT_FAILURE);
            }
            if(read(fd2, &sum , sizeof(int)) < 0){
                perror("Reading from FIFO2 : ");
                close(fd2);
                exit(EXIT_FAILURE);
            }

            close(fd2);

            printf("Output: %d\n", sum + mul);
            free(arr2);
            exit(EXIT_SUCCESS);
        }
        else{
            char buffer[100] = "multiply";

            fd2 = open(myfifo2, O_WRONLY);
            if(fd2 == -1){
                perror("Opening FIFO2: ");
                close(fd2);
                exit(EXIT_FAILURE);
            }

            if(write(fd2, buffer, sizeof(buffer)) < 0){
                perror("Writing to FIFO2 : ");
                close(fd2);
                exit(EXIT_FAILURE);
            }
            if(write(fd2, arr, sizeof(int) * 5) < 0){
                perror("Writing to FIFO2 : ");
                close(fd2);
                exit(EXIT_FAILURE);
            }
            close(fd2);

            fd = open(myfifo1, O_WRONLY);
            if(fd == -1){
                perror("Opening FIFO1: ");
                close(fd);
                cleanChilds();
                exit(EXIT_FAILURE);
            }
            if(write(fd, arr, sizeof(int) * 5) < 0){
                perror("Writing to FIFO1 : ");
                close(fd);
                exit(EXIT_FAILURE);
            }
            close(fd);

            while(1){
                printf("Proceeding...\n");
                sleep(2);
            }
            free(arr);
        }
    }
    free(arr);
	return 0;
}
