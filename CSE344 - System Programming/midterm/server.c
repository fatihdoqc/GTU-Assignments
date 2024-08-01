#include "utilities.h"

#define CLI_SEM "max_client_semaphore"

volatile sig_atomic_t child_returned = 0;
int client_num = 0;
struct client *clients;
int maxClient = 0, maxClientQueue = 0;
sem_t *sem1, *sem2;
char *cli_addr;
pid_t parent_pid;

void cleanChilds();
int doCommand(char *string, char *dir_name);
void helpCommand();
void quitCommand();
void readFCommand(char *string);
int countNewlines(char *str, int line);
void listCommand(char *dir_name);
void writeFCommand(char *string);
void append_to_line(const char *file_name, int line_number,char *text);
void uploadCommand(char *string, char *server);
void downloadCommand(char *string, char *server);
void killServer();

void sigint_handler() {

    char sem_name[64];
    printf("\nSIGINT received. Exiting.\n");
    sem_unlink(CON_SEM);
    sem_unlink(CLI_SEM);
    sprintf(sem_name, "server_shm_%d",getpid());
    shm_unlink(sem_name); 

    for (int i = 0; i < maxClientQueue; i++)
    {
        char buf[SHM_SIZE];
        snprintf(buf, sizeof(buf), "sem_1_%d", clients[i].client_pid);
        sem_unlink(buf);

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "sem_2_%d", clients[i].client_pid);
        sem_unlink(buf);

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "client_shm_%d", clients[i].client_pid);
        shm_unlink(buf);

        kill(clients[i].client_pid, SIGINT);
    }
    
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

    if (argc < 3)
    {
        perror("Wrong usage! Correct usage : neHosServer <dirname> <max. #ofClients>");
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

    parent_pid = getpid();
    int fd, fd2;
    maxClient = atoi(argv[2]);
    maxClientQueue = maxClient * 2;

    char* addr;
    char buf[1024];
    struct stat st;

    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "Dir: %s\n", argv[1]);
    write(STDOUT_FILENO, buf, strlen(buf));

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
            perror("ftruncate");

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
            sprintf(buf, "Client PID %d connected as \"client%d\"\n", clients[curr_cli_index].client_pid, curr_cli_index);
            write(STDOUT_FILENO, buf, strlen(buf));

            sem_post(sem2);  

            while(1){
                char *buf;

                sem_wait(sem1);
                buf = (char *) cli_addr;

                write(STDOUT_FILENO, "Command from client: ", strlen("Command from client: "));
                write(STDOUT_FILENO, buf, strlen(buf));
                write(STDOUT_FILENO,"\n", 1);

                //read(STDIN_FILENO, str, sizeof(str));

                int ret = doCommand(buf, argv[1]);
                if(ret == 1){
                    break;
                }
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

int doCommand(char *string, char *dir_name){

    if(strcmp(string, "help") == 0){
        helpCommand();
    }
    else if(strcmp(string, "quit") == 0){
        quitCommand();
        return 1;
    }
    else if(strstr(string, "readF") != NULL){
        readFCommand(string);
    }
    else if(strcmp(string, "list") == 0){
        listCommand(dir_name);
    }
    else if(strstr(string, "writeF") != NULL){
        writeFCommand(string);
    }
    else if(strstr(string, "upload") != NULL){
        uploadCommand(string, dir_name);
    }
    else if(strstr(string, "download") != NULL){
        downloadCommand(string, dir_name);
    }
    else if(strcmp(string, "killServer") == 0){
        killServer();
        return 1;
    }
    return 0;
}
void downloadCommand(char *string, char *server){
    char *token = strtok(string, " "); // download
    token = strtok(NULL, " "); // file_name

    struct stat file_info;
    char source[SHM_SIZE], *file_name = token, buffer[SHM_SIZE];
    sprintf(source, "%s/%s",server, file_name);

    if (stat(file_name, &file_info) == 0) // if exist, delete. because we will overwrite.
        unlink(file_name);    

    int source_fd = open(source, O_RDONLY);
    if (source_fd == -1)
    {
        char err[] = "\n>> File doesn't exist..\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, err, sizeof(err));
        sem_post(sem2);
        return;
    }
    flock(source_fd, LOCK_EX);

    int dest_fd = open(file_name, O_WRONLY | O_CREAT, 0666), bytes_read;
    flock(dest_fd, LOCK_EX);
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        write(dest_fd, buffer, bytes_read);
    }

    flock(source_fd, LOCK_UN);
    flock(dest_fd, LOCK_UN);

    close(source_fd);
    close(dest_fd);
    char str[] = "\n>> File downloaded successfully\n";
    memset(cli_addr, '\0', strlen(cli_addr)+1);
    memcpy(cli_addr, str, sizeof(str));
    sem_post(sem2);
}

void uploadCommand(char *string, char *server){
    char *token = strtok(string, " "); // upload
    token = strtok(NULL, " "); // file_name

    struct stat file_info;
    char *file_name = token, buffer[SHM_SIZE];
    char dest[SHM_SIZE];
    sprintf(dest, "%s/%s", server, file_name);

    if (stat(dest, &file_info) == 0) // if exist, delete. because we will overwrite.
        unlink(dest);

    int source_fd = open(file_name, O_RDONLY), bytes_read;

    if (source_fd == -1)
    {
        char err[] = "\n>> File doesn't exist..\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, err, sizeof(err));
        sem_post(sem2);
        return;
    }
    flock(source_fd, LOCK_EX);
    
    int dest_fd = open(dest, O_WRONLY | O_CREAT, 0666);
    flock(dest_fd, LOCK_EX);

    while ((bytes_read = read(source_fd, buffer, SHM_SIZE)) > 0)
    {
        write(dest_fd, buffer, strlen(buffer));
    }

    flock(source_fd, LOCK_UN);
    flock(dest_fd, LOCK_UN);

    char str[] = "\n>> File uploaded successfully\n";
    memset(cli_addr, '\0', strlen(cli_addr)+1);
    memcpy(cli_addr, str, sizeof(str));
    sem_post(sem2);

}

void helpCommand(){
    char str[] = "\n\nAvailable comments are :help, list, readF, writeT, upload, download, archServer,quit, killServer\n\n";
    memset(cli_addr, '\0', strlen(cli_addr)+1);
    memcpy(cli_addr, str, sizeof(str));
    sem_post(sem2);
}

void quitCommand(){
    char str[] = "quit";
    memset(cli_addr, '\0', strlen(cli_addr)+1);
    memcpy(cli_addr, str, sizeof(str));
    sem_post(sem2);
}

void writeFCommand(char *string){
    char *token = strtok(string, " "); // writeF
    char *file_name, *desired_str = calloc(SHM_SIZE, sizeof(char));

    int line;
    
    token = strtok(NULL, " "); // file_name
    file_name = token;

    int fd = open(file_name, O_RDONLY | O_CREAT, 0666) , total_bytes = 0;
    if(fd == -1){
        char err[] = "Cannot open file.\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, err, sizeof(err));
        sem_post(sem2);
        return;
    }

    token = strtok(NULL, " "); // line # or string
    if (strstr(token, "\"") != NULL) // contains "
    {
        // No Line number given.
        strcpy(desired_str, "\n");
        strcat(desired_str, &token[1]);
        total_bytes = strlen(desired_str);
        token = strtok(NULL, " "); // line # or string

        while(token != NULL){ // string extraction
            if (total_bytes >= SHM_SIZE - 10)
            {
                desired_str = realloc(desired_str, total_bytes + SHM_SIZE + 2); // 2 for comma and null terminator
            }
            
            if (strstr(token, "\"") != NULL){ // contains closing quotatiton
                char* closing_quote = strchr(token, '"');
                *closing_quote = '\0';

                strcat(desired_str, " ");
                strcat(desired_str, token);
                total_bytes += strlen(token) + 1;
                break;
            }

            strcat(desired_str, " ");
            strcat(desired_str, token);
            total_bytes += strlen(token) + 1;

            token = strtok(NULL, " ");            
        }

        close(fd);
        append_to_line(file_name, -1, desired_str);
        
        char str[] = ">> Writing to file is successful..\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, str, sizeof(str));
        sem_post(sem2);
        free(desired_str);
    }
    else{ // There is line#
        line = atoi(token);

        token = strtok(NULL, " "); // line # or string
        if (strstr(token, "\"") != NULL) // contains "
        {
            // No Line number given.
            if (line != 1)
            {
                strcpy(desired_str, "\n");
            }
            
            strcat(desired_str, &token[1]);
            total_bytes = strlen(desired_str);
            token = strtok(NULL, " "); // line # or string

            while(token != NULL){ // string extraction
                if (total_bytes >= SHM_SIZE - 10)
                {
                    desired_str = realloc(desired_str, total_bytes + SHM_SIZE + 2); // 2 for comma and null terminator
                }
                
                if (strstr(token, "\"") != NULL){ // contains closing quotatiton
                    char* closing_quote = strchr(token, '"');
                    *closing_quote = '\0';

                    strcat(desired_str, " ");
                    strcat(desired_str, token);
                    total_bytes += strlen(token) + 1;
                    break;
                }

                strcat(desired_str, " ");
                strcat(desired_str, token);
                total_bytes += strlen(token) + 1;

                token = strtok(NULL, " ");            
            }
        }

        write(STDOUT_FILENO, &line, sizeof(int));

        if (line == 1)
        {
            strcat(desired_str, "\n");
        }

        close(fd);
        append_to_line(file_name, line, desired_str);

        char str[] = ">> Writing to file is successful..\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, str, sizeof(str));
        sem_post(sem2);
        free(desired_str);
    }    
}

void append_to_line(const char *file_name, int line_number,char *text) {

    char buffer[SHM_SIZE], copy_file[256];
    int org_fd = open(file_name, O_RDWR), bytes_read, line_count = 0, bytes_written = 0, size = strlen(text);

    sprintf(copy_file,"%s_temp",file_name);
    int cpy_fd = open(copy_file, O_WRONLY | O_CREAT, 0666);

    flock(org_fd, LOCK_EX);

    while( (bytes_read = read(org_fd, buffer, 1)) > 0){
        if(buffer[0] == '\n'){
            line_count++;
        }

        if (line_count == line_number - 1)
        {
            while (bytes_written < size) {
                int bytes_to_write = (size - bytes_written < SHM_SIZE) ? (size - bytes_written) : SHM_SIZE;
                write(cpy_fd, text + bytes_written, bytes_to_write);
                bytes_written += bytes_to_write;
            }
            line_count++;
            write(cpy_fd, buffer, 1);
        }
        else{
            write(cpy_fd, buffer, 1);
        }
    }

    if (line_count < line_number - 1 || line_number == -1)
    {
        while (bytes_written < size) {
            int bytes_to_write = (size - bytes_written < SHM_SIZE) ? (size - bytes_written) : SHM_SIZE;
            write(cpy_fd, text + bytes_written, bytes_to_write);
            bytes_written += bytes_to_write;
        }
    }

    unlink(file_name);
    unlink(copy_file);
    rename(copy_file, file_name);

    flock(org_fd, LOCK_UN);

    close(org_fd);
    close(cpy_fd);
    
}

void listCommand(char *dir_name){

    DIR *dr = opendir(dir_name);
    int isEmpty = 1;

    if (dr == NULL) {
        char err[] = "Couldn't open server directory.\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, err, sizeof(err));
        sem_post(sem2);
        return;
    }

    struct dirent *entry;
    char *file_names = NULL;
    size_t total_length = 0;

    while ((entry = readdir(dr)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            isEmpty = 0; // Directory is not empty

            size_t entry_length = strlen(entry->d_name);
            file_names = realloc(file_names, total_length + entry_length + 2); // 2 for comma and null terminator

            if (file_names == NULL) {
                char err[] = "Couldn't allocate memory.\n";
                memset(cli_addr, '\0', strlen(cli_addr)+1);
                memcpy(cli_addr, err, sizeof(err));
                sem_post(sem2);
                closedir(dr);
            }
            strcat(file_names, entry->d_name);
            strcat(file_names, "\n");
            total_length += entry_length + 2;
        }
    }

    if (isEmpty)
    {
        char str[] = "\n>> Server directory is empty..\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, str, sizeof(str));
        sem_post(sem2);
    }
    else{
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, file_names, strlen(file_names));
        sem_post(sem2);
    }
    
    free(file_names); 
}
void readFCommand(char *string){
    int line;
    char *str = string, *file_name, buffer[SHM_SIZE];
    char *token = strtok(str, " "); // readF
    token = strtok(NULL, " "); // file_name
    file_name = token;

    if (token == NULL)
    {
        char err[] = "Bad usage.\n";
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, err, sizeof(err));
        sem_post(sem2);
        return;
    }

    token = strtok(NULL, " ");  // line_num

    if (token == NULL)  // Read whole file
    {
        int fd = open(file_name, O_RDONLY, 0666) , bytes_read = 0;
        if(fd == -1){
            char err[] = "Bad file name.\n";
            memset(cli_addr, '\0', strlen(cli_addr)+1);
            memcpy(cli_addr, err, sizeof(err));
            sem_post(sem2);
        }
        else{
            flock(fd, LOCK_EX);

            while( (bytes_read = read(fd, buffer, SHM_SIZE)) > 0){
                memset(cli_addr, '\0', strlen(cli_addr)+1);
                memcpy(cli_addr, buffer, sizeof(buffer));
                sem_post(sem2);
                sem_wait(sem1);
                memset(buffer, 0, sizeof(buffer));
            }
            flock(fd, LOCK_UN);
        }

            strcpy(buffer, "End");
            memset(cli_addr, '\0', strlen(cli_addr)+1);
            memcpy(cli_addr, buffer, sizeof(buffer));
            sem_post(sem2);
            close(fd);
    }
    else { // Read the #th line
        line = atoi(token);

        int fd = open(file_name, O_RDONLY, 0666) , bytes_read = 0, line_count = 0;
        char response[SHM_SIZE];
        memset(response, 0, sizeof(response));

        if(fd == -1){
            char err[] = "Bad file name.\n";
            memset(cli_addr, '\0', strlen(cli_addr)+1);
            memcpy(cli_addr, err, sizeof(err));
            sem_post(sem2);
        }
        else{
            flock(fd, LOCK_EX);

            while ((bytes_read = read(fd, buffer, 1)) > 0) {
                if(line == 1){
                    response[strlen(response)] = buffer[0];

                    while ((bytes_read = read(fd, buffer, 1)) > 0) {
                        if (buffer[0] == '\n') {
                            break;
                        }
                        response[strlen(response)] = buffer[0];
                    }
                    response[strlen(response)] = '\0'; // Null terminate response
                    write(STDOUT_FILENO, response, strlen(response));

                    //read(STDIN_FILENO, str, sizeof(str));
                    memset(cli_addr, '\0', strlen(cli_addr)+1);
                    memcpy(cli_addr, response, sizeof(response));
                    sem_post(sem2);
                    sem_wait(sem1);
                    break;
                }
                if (buffer[0] == '\n') {
                    line_count++;
                    if (line_count + 1 == line) {
                        while ((bytes_read = read(fd, buffer, 1)) > 0) {
                            if (buffer[0] == '\n') {
                                break;
                            }
                            response[strlen(response)] = buffer[0];
                        }
                        response[strlen(response)] = '\0'; // Null terminate response
                        write(STDOUT_FILENO, response, strlen(response));

                        //read(STDIN_FILENO, str, sizeof(str));
                        memset(cli_addr, '\0', strlen(cli_addr)+1);
                        memcpy(cli_addr, response, sizeof(response));
                        sem_post(sem2);
                        sem_wait(sem1);
                        break;
                    }
                }
            }
            flock(fd, LOCK_UN);
        }
        
        strcpy(buffer, "End");
        memset(cli_addr, '\0', strlen(cli_addr)+1);
        memcpy(cli_addr, buffer, sizeof(buffer));
        sem_post(sem2);
        close(fd);
    }
}

void killServer(){
    char str[] = "kill";
    memset(cli_addr, '\0', strlen(cli_addr)+1);
    memcpy(cli_addr, str, sizeof(str));
    sem_post(sem2);

    kill(parent_pid, SIGINT);
}
