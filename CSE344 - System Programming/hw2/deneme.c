#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int fd, fd2;
    char buffer[100];

	char * myfifo1 = "/tmp/myfifo1";
	char * myfifo2 = "/tmp/myfifo2";

	mkfifo(myfifo1, 0666);
	mkfifo(myfifo2, 0666);
    
	pid_t child = fork();

    if (child == 0)
    {

        int arr[5], sum = 0, buf_int;

        memset(buffer, 0, sizeof(buffer));
        fd = open(myfifo1, O_RDONLY);
        read(fd, arr, sizeof(int) * 5);

        for (int i = 0; i < 5; i++)
        {
            sum += arr[i];
        }

        printf("Summ: %d\n", sum);
        
        printf("Message from parent: %d\n",arr[2]);
        close(fd);

        fd = open(myfifo1, O_WRONLY);

        write(fd, "Hello Parent!" , sizeof("Hello Parent!"));
        close(fd);

        fd2 = open(myfifo2, O_WRONLY);

        write(fd2, arr, sizeof(int) * 5);
        close(fd2);

        memset(buffer, 0, sizeof(buffer));
        fd2 = open(myfifo2, O_RDONLY);

        read(fd2, &buf_int, sizeof(int));
        printf("Message from Child2: %d\n",buf_int);
        close(fd2);
        exit(EXIT_SUCCESS);

    }
    else{
        fd = open(myfifo1, O_WRONLY);

        int arr[5] = {1,2,3,4,5};

        write(fd, arr, sizeof(int) * 5);
        close(fd);

        fd = open(myfifo1, O_RDONLY);

        read(fd, buffer, sizeof(buffer));
        printf("Message from child1: %s\n", buffer);
        close(fd);

        pid_t child2 = fork();

        if(child2 == 0){
            char buffer2[100];
            int arr[5], mul = 1;

            memset(buffer2, 0, sizeof(buffer2));
            fd2 = open(myfifo2, O_RDONLY);

            read(fd2, arr, sizeof(int) * 5);
            printf("Message from child1: %d\n",arr[2]);
            close(fd2);

            for (int i = 0; i < 5; i++)
            {
                mul *= arr[i];
            }
            printf("multip: %d\n",mul);
            

            fd2 = open(myfifo2, O_WRONLY);

            write(fd2, &mul, sizeof(int));
            close(fd2);
            exit(EXIT_SUCCESS);
        }
        else{
            waitpid(child2, NULL, 0);
        }

        waitpid(child, NULL , 0);
    }
    
	return 0;
}
