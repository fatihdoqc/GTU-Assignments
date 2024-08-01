#include "utilities.h"

void open_files_in_dest(char source[256], char dest[256]);

int threadNum = 0;
struct buffer *buff;
int bufferSize = -1;
int head, tail;
int exitCond = 0;
int totalBytes = 0;
int totalFiles = 0;
int totalFolders = 0;
int totalFIFOs = 0;
int totalSymbolic = 0;
int bufferIndex = 0;
int sigint_received = 0;
int workerNum = 0;

pthread_mutex_t mutex;
sem_t empty, full;

pthread_t managerThd;
struct manager_thread_params *params;
pthread_t *workerThds = NULL;

void* threadEx(){

    char buffer[1024];
    int bytes_read;

    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if ((tail == head && exitCond == 1) || sigint_received == 1 )
        {
            close(buff[tail].destfd);
            close(buff[tail].sourcefd);
            pthread_mutex_unlock(&mutex);
            break;
        }

        while ((bytes_read = read(buff[tail].sourcefd, buffer, sizeof(buffer) - 1)) > 0)
        {
            write(buff[tail].destfd, buffer, bytes_read);
            totalBytes += bytes_read;
        }

        close(buff[tail].destfd);
        close(buff[tail].sourcefd);

        tail = (tail + 1) % bufferSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  
    }

    return NULL;
}

void* manager_func(void *args){
    struct manager_thread_params *params = args;

    open_files_in_dest(params->destination, params->source);
    
    pthread_mutex_lock(&mutex);
    exitCond = 1;
    for (int i = 0; i < bufferSize; i++)
    {
        sem_post(&full);
    }
    
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void open_files_in_dest(char source[256], char dest[256]){

    DIR *dir;
    struct stat info;
    struct dirent *entry;

    char new_source[1024];
    char new_dest[1024];

    if (stat(dest, &info) == -1 ) {
        mkdir(dest, 0777);
    }

    dir = opendir(source);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(new_source, sizeof(new_source), "%s/%s", source, entry->d_name);
        snprintf(new_dest, sizeof(new_dest), "%s/%s", dest, entry->d_name);

        if (stat(new_source, &info) != 0) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(info.st_mode)) {
            if (stat(new_dest, &info) == -1 ) {
                mkdir(new_dest, 0777);
            }
            totalFolders++;
            open_files_in_dest(new_source, new_dest);
        }
        else {
            if (S_ISFIFO(info.st_mode)) {
                totalFIFOs++;
            } else if (S_ISLNK(info.st_mode)) {
                totalSymbolic++;
            } else { // Regular File.
                totalFiles++;
            }

            int fd = open(new_dest, O_CREAT | O_TRUNC | O_WRONLY, 0777);
            int fd2 = open(new_source, O_RDONLY, 0777);

            sem_wait(&empty);
            pthread_mutex_lock(&mutex); // LOCK
            
            strcpy(buff[head].dest_name, new_dest);
            strcpy(buff[head].source_name, new_source);
            buff[head].destfd = fd;
            buff[head].sourcefd = fd2;

            head = (head + 1) % bufferSize;

            pthread_mutex_unlock(&mutex); // UNLOCK

            sem_post(&full);

            //printf("%s\n", new_dest);
        }
    }
    closedir(dir);    
}

void print_elapsed_time(struct timeval start, struct timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;

    if (microseconds < 0) {
        seconds -= 1;
        microseconds += 1000000;
    }

    long minutes = seconds / 60;
    seconds = seconds % 60;
    long milliseconds = microseconds / 1000;

    printf("TOTAL TIME: %02ld:%02ld.%03ld (min:sec.mili)\n", minutes, seconds, milliseconds);
}

void sigint_handler() {
    printf("\nSIGINT received. Exiting.\n");
    sigint_received = 1;

    free(workerThds);
    free(buff);
    free(params);
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
        
    
    struct timeval start, end;
    gettimeofday(&start, NULL);

    struct sigaction sa_int;

    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

    // Accepts buffer size, number of workers, and source/destination directories as command-line arguments.
    if (argc < 5 || argc > 5){
        printf("Bad input. Usage: ./MWCp <bufferSize> <numberOfWorkers> <SourceDir> <DestDir>\n");
        exit(EXIT_FAILURE);
    }

    workerNum = atoi(argv[2]);

    bufferSize = atoi(argv[1]);

    buff = calloc(bufferSize, sizeof(struct buffer));
    head = 0; 
    tail = 0;

    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);
    // Initialize workers and manager.

    workerThds = calloc(workerNum, sizeof(pthread_t));

    params = calloc(1, sizeof(struct manager_thread_params));
    strcpy(params->destination, argv[3]);
    strcpy(params->source, argv[4]);


    pthread_create(&managerThd, NULL, manager_func, params);

    for (int i = 0; i < workerNum; i++)
    {
        pthread_create(&workerThds[i], NULL, threadEx, NULL);
    }

    for (int i = 0; i < workerNum; i++)
    {
        pthread_join(workerThds[i], NULL);
    }

    pthread_join(managerThd, NULL);

    printf("\n---------------STATISTICS--------------------\n");
    printf("Consumers: %d - Buffer Size: %d\n", workerNum,bufferSize);
    printf("Number of Regular File: %d\n",totalFiles);
    printf("Number of FIFO File: %d\n",totalFIFOs);
    printf("Number of Directory: %d\n",totalFolders); 
    printf("Number of Symbolic Links: %d\n",totalSymbolic); 
    printf("TOTAL BYTES COPIED: %d\n",totalBytes);

    gettimeofday(&end, NULL);
    print_elapsed_time(start, end);

    free(workerThds);
    free(params);
    free(buff);
    return 0;
    
}