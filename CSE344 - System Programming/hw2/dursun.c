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

	char * myfifo1 = "/tmp/myfifo1";
	char * myfifo2 = "/tmp/myfifo2";

	mkfifo(myfifo1, 0666);
	mkfifo(myfifo2, 0666);
    
	pid_t child = fork();

    if (child == 0)
    {
        int arr[5], sum = 0;

        fd = open(myfifo1, O_RDONLY);
        read(fd, arr, sizeof(int) * 5);
        close(fd);

        for (int i = 0; i < 5; i++)
        {
            sum += arr[i];
        }

        printf("Summ: %d\n", sum);

        fd2 = open(myfifo2, O_WRONLY);
        write(fd2, &sum, sizeof(int));
        close(fd2);

        exit(EXIT_SUCCESS);

    }
    else{

        pid_t child2 = fork();

        if(child2 == 0){
            char buffer2[100];
            int arr[5], mul = 1, sum;

            memset(buffer2, 0, sizeof(buffer2));
            fd2 = open(myfifo2, O_RDONLY);

            read(fd2, buffer2, sizeof(buffer2));
            read(fd2, arr, sizeof(int) * 5);
            close(fd2);

            printf("Message from parent: %s\n",buffer2);
            printf("Arr: %d---%d\n",arr[0], arr[1]);

            for (int i = 0; i < 5; i++)
            {
                mul *= arr[i];
            }
            printf("multip: %d\n",mul);
            

            fd2 = open(myfifo2, O_RDONLY);
            read(fd2, &sum , sizeof(int));
            close(fd2);

            printf("sum child2: %d\n",sum);
            exit(EXIT_SUCCESS);
        }
        else{
            char buffer[100] = "multiply";
            int arr[5] = {1,2,3,4,5};

            fd2 = open(myfifo2, O_WRONLY);
            write(fd2, buffer, sizeof(buffer));
            write(fd2, arr, sizeof(int) * 5);
            close(fd2);

            fd = open(myfifo1, O_WRONLY);
            write(fd, arr, sizeof(int) * 5);
            close(fd);

            waitpid(child, NULL , 0);
            waitpid(child2, NULL, 0);
        }
    }
    
    unlink(myfifo1);
    unlink(myfifo2);

	return 0;
}
