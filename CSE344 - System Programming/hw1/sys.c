#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "string.h" // My Custom String Lib
#include <string.h>
#include <signal.h>

void menu();
void createFile(char option[100]);
void addStudent(char* file_name, char* name, char* grade);
void searchStudent(char* file_name, char* name);
void sortAll(char* file_name, int sortOption, int sortOrder);
void showAll(char* file_name);
void listGrades(char* file_name);
void listSome(char* numOfEntries, char* pageNum, char* file_name);
void printFile(char* file_name, int numOfEntries, int pageNum);
void bubbleSort(char arr1[5000][100], char arr2[5000][100], int count, int ascendingFlag);
//void logIt(char *str, int flag);
void cleanChilds();

pid_t childs[100];
int child_num = 0;

void sigint_handler() {
    printf("\nSIGINT received. Killing all child processes...\n");
    cleanChilds();
    exit(0);
}

void cleanChilds(){
    for (int i = 0; i < child_num; i++) {
        kill(childs[i], SIGKILL);
    }
}

int main() 
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sigint_handler;
    sigaction(SIGINT, &sa, NULL);

    menu();
    cleanChilds();
    return 0;
}
void menu(){

    char option[100], inputs[10][100];
    int index = 0;

    printf("Welcome...\n");

    while(1){
        printf("\nType gtuStudentGrades to see the options. Type exit to exit..:\n ");
        int bytes_read = read(STDIN_FILENO, option, sizeof(option) - 1); // -1 to leave room for null terminator
        option[bytes_read - 1] = '\0';

        int i = 0;
        int flag = 0; // There is no " in the input.
        while(i < strln(option)){
            if(option[i] == '\"'){
                flag = 1; // There is " in the input.
            }
            i++;
        }
        
        if(flag == 0){
            if (strcmpp(option, "gtuStudentGrades") == 0)
            {
                printf("\ngtuStudentGrades \"file_name\"\n");
                printf("addStudentGrade \"file_name\" \"Name Surname\" \"grade\"\n");
                printf("searchStudent \"file_name\" \"Name Surname\"\n");
                printf("sortAll \"file_name\" \"0/1\" (0 = Sort Names / 1 = Sort Grades) \"0/1\" (0 = Descending / 1= Ascending)\n");
                printf("showAll \"file_name\"\n");
                printf("listGrades \"file_name\"\n");
                printf("listSome \"number of entries\" \"page number\" \"file_name\"\n\n");
            }
            else if(strcmpp(option, "exit") == 0){
                printf("\nBye!\n");
                cleanChilds();
                exit(0);
            }
            else{
                perror("Bad input");
                continue;
            }
        }
        else{
            
            for (int i = 0; i < 10; i++) // Reset the inputs
            {
                my_memset(inputs[i], 0, sizeof(inputs[i]));
            }
            
            index = 0;
            for (int i = 0; i < strln(option); i++)
            {
                if(i == 0){
                    while(option[i+1] != '\"'){
                        inputs[index][i] = option[i];
                        i++;
                    }
                }

                if(option[i] == '\"'){
                    int k = 0;
                    index++;

                    while(option[i+1] != '\"'){
                        inputs[index][k] = option[i+1];
                        i++;
                        k++;
                        if (i >= strln(option)) break;    
                    }
                    i++;
                    inputs[index][k] = '\0';
                }  
            }

            if (strcmpp(inputs[0], "gtuStudentGrades") == 0)
            {
                if(index > 1){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                
                createFile(inputs[1]);
            }            
            else if(strcmpp(inputs[0], "addStudentGrade") == 0){
                if(index > 3){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                addStudent(inputs[1], inputs[2], inputs[3]);
            }
            else if(strcmpp(inputs[0], "searchStudent") == 0){
                if(index > 2){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                searchStudent(inputs[1], inputs[2]);
            }
            else if(strcmpp(inputs[0], "sortAll") == 0){
                if(index > 3){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                sortAll(inputs[1], atoi(inputs[2]) , atoi(inputs[3]));
            }
            else if(strcmpp(inputs[0], "showAll") == 0){
                if(index > 1){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                showAll(inputs[1]);
            }
            else if(strcmpp(inputs[0], "listGrades") == 0){
                if(index > 1){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                listGrades(inputs[1]);
            }
            else{ // List Some
                if(index > 3){
                    perror("Too many inputs");
                    cleanChilds();
                    exit(0);
                }
                listSome(inputs[1], inputs[2], inputs[3]);
            }
            
        }
    }
}

/*void logIt(char *str, int flag){
    childs[child_num++] = fork();

    if (childs[child_num - 1] == 0)
    {
        int fd = open("myLog.log", O_CREAT | O_WRONLY | O_APPEND, 0666);

        write(fd, str, strln(str));
        
        close(fd);
    }
    else{
        wait(NULL);
    }
    
}*/

void createFile(char file_name[100]){

    childs[child_num] = fork();

    if(childs[child_num++] == 0){
        int fd = open(file_name, O_CREAT , 0666);
        close(fd);
        printf("\nFile %s created.",file_name);
        exit(0);
    }
    else{
        wait(NULL);
    }
    
}

void addStudent(char* file_name, char* name, char* grade){

    childs[child_num++] = fork();

    if(childs[child_num - 1] == 0){
        int fd = open(file_name, O_WRONLY | O_APPEND);

        if (fd < 0)
        {
            perror("Error openning file");
            exit(1);
        }

        write(fd, name, strln(name));
        write(fd, ",",1);
        write(fd, grade, strln(grade));
        write(fd, "\n",1);

        printf("\nStudent added to the file.\n\n");

        close(fd);
        exit(0);
    }
    else{
        wait(NULL);
    }
}

void searchStudent(char* file_name, char* name){

    childs[child_num++] = fork();
    char c;
    int bytes_read, k=0;
    char buffer[1024];

    if(childs[child_num - 1] == 0){
        int fd = open(file_name, O_RDONLY);

        while ((bytes_read = read(fd, &c , 1)) != 0)
        {
            if(c != '\n' && c != EOF){
                buffer[k++] = c;            
            }
            else{
                buffer[k] = '\0';

                char* token = strtokk(buffer, ',');
                if(strcmpp(token, name) == 0){
                    token = strtokk(NULL, ',');
                    printf("\n%-25s%s %s\n\n",name , " |", token);
                }

                k = 0;
            }
            
        }

        if (k > 0) { // Last line
            buffer[k] = '\0'; 

            char* token = strtokk(buffer, ',');
            
            if(strcmpp(token, name) == 0){
                token = strtokk(NULL, ',');
                printf("%s - %s\n", name, token);
            }
        }

        close(fd);
        exit(0);
    }
    else{
        wait(NULL);
    }
}

void sortAll(char* file_name, int sortOption, int sortOrder){

    childs[child_num++] = fork();
    int bytes_read, line_num = 0, k = 0;
    char c, buffer[5000][100], names[5000][100], grades[5000][100];

    if(childs[child_num - 1] == 0){
        int fd = open(file_name, O_RDONLY);

        if (fd < 0)
        {
            perror("Error openning file");
            exit(1);
        }

        while ((bytes_read = read(fd, &c , 1)) != 0)
        {
            if(c != '\n' && c != EOF){
                buffer[line_num][k++] = c;            
            }
            else{
                buffer[line_num][k] = '\0';
                char* token = strtokk(buffer[line_num], ',');
                strcpyy(names[line_num], token);

                token = strtokk(NULL, ',');
                strcpyy(grades[line_num], token);             

                k = 0;
                line_num++;
            }
        }

        if (k > 0) { // Last line
            buffer[line_num][k] = '\0';
            char* token = strtokk(buffer[line_num], ',');
            strcpyy(names[line_num], token);

            token = strtokk(NULL, ',');
            strcpyy(grades[line_num], token);             

            k = 0;
            line_num++;
        }

        if (sortOption == 0) // Sort names
        {
            if (sortOrder == 0) // Descending order.
            {
                bubbleSort(names,grades, line_num, sortOrder); 
            }
            else if(sortOrder == 1){ // Ascending order
                bubbleSort(names,grades, line_num, sortOrder); 
            }
            
        }
        else if (sortOption == 1){ // Sort grades

            if (sortOrder == 0) // Descending order.
            {
                bubbleSort(grades, names,line_num, sortOrder); 
            }
            else if(sortOrder == 1){ // Ascending order
                bubbleSort(grades,names, line_num, sortOrder); 
            }
        }

        printf("\n");
        for (int i = 0; i < 43; i++)
        {
            printf("_");

        }
        printf("\n");

        for (int i = 0; i < line_num; i++)
        {
            printf("%-25s%12s %s %s %s\n",names[i] , " ", "|",grades[i],"|");

        }
        printf("\n");
    
        close(fd);
        exit(0);
    }
    else{
        wait(NULL);
    }
}

void bubbleSort(char arr1[5000][100], char arr2[5000][100], int count, int ascendingFlag) {
    char temp[100];

    if(ascendingFlag == 0){ // Descending order
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (strcmpp(arr1[j], arr1[j + 1]) < 0) {
                    strcpyy(temp, arr1[j]);
                    strcpyy(arr1[j], arr1[j + 1]);
                    strcpyy(arr1[j + 1], temp);

                    strcpyy(temp, arr2[j]);
                    strcpyy(arr2[j], arr2[j + 1]);
                    strcpyy(arr2[j + 1], temp);
                }
            }
        }
    }
    else if(ascendingFlag == 1){ //Ascending order
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (strcmpp(arr1[j], arr1[j + 1]) > 0) {
                    strcpyy(temp, arr1[j]);
                    strcpyy(arr1[j], arr1[j + 1]);
                    strcpyy(arr1[j + 1], temp);

                    strcpyy(temp, arr2[j]);
                    strcpyy(arr2[j], arr2[j + 1]);
                    strcpyy(arr2[j + 1], temp);
                }
            }
        }
    }    
}

void showAll(char* file_name){
    childs[child_num++]= fork();

    if(childs[child_num - 1] == 0){
        printFile(file_name, 5000, 1);
        exit(0);
    }
    else{
        wait(NULL);
    }
}

void listGrades(char* file_name){
    childs[child_num++] = fork();
 
    if(childs[child_num - 1] == 0){
        printFile(file_name, 5, 1);
        exit(0);       
    }
    else{
        wait(NULL);
    }
}

void listSome(char* numOfEntries, char* pageNum, char* file_name){

    childs[child_num++] = fork();

    if (childs[child_num - 1] == 0)
    {
        printFile(file_name, atoi(numOfEntries), atoi(pageNum));
        exit(0);

    }
    else{
        wait(NULL);
    }
}

void printFile(char* file_name, int numOfEntries, int pageNum){

    int bytes_read, entries = 0, k = 0;
    int pagesToListFirst = numOfEntries * (pageNum -1);
    int pagesToListLast = numOfEntries * pageNum ;

    char buffer[100], c;
    int fd = open(file_name, O_RDONLY);

    if (fd < 0)
    {
        perror("Error opening file");
        exit(1);
    }

    printf("\n");
    for (int i = 0; i < 43; i++)
    {
        printf("_");

    }
    printf("\n");

    while ((bytes_read = read(fd, &c , 1)) != 0)
    {
        if(c != '\n' && c != EOF){
            buffer[k++] = c;            
        }
        else{
            buffer[k] = '\0';

            if(entries >= pagesToListFirst && entries < pagesToListLast){
                char* token = strtokk(buffer, ',');
                printf("%-25s%12s%s ",token , " " , "|");

                token = strtokk(NULL, ',');
                printf("%s %s\n", token, "|");
            }         
            
            entries++;
            k = 0;
        }
        
        if(entries >= pagesToListLast) break;
    }

    if (k > 0 && entries < pagesToListLast) { // Last line
        buffer[k] = '\0';

        char* token = strtokk(buffer, ',');
        printf("%-25s%12s%s ",token , " ", "|");

        token = strtokk(NULL, ',');
        printf("%s %s\n", token, "|");
    }
    printf("\n");

    close(fd);
}
