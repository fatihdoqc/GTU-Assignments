#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <string.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include "log.h"
#include "utilities.h"
#include "p_inverse.h"
#include <math.h>

#define BUFFER_SIZE 1024
#define OVEN_SIZE 6
#define OVEN_APARATUS_COUNT 3

pthread_mutex_t oven_entry1 = PTHREAD_MUTEX_INITIALIZER; // trylock
pthread_mutex_t oven_entry2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t prep_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t finish_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oven_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t deliver_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t *cooks;
pthread_t *deliveryPersons;
pthread_t manager;
pthread_t *ovens;

sem_t inside_oven, oven_aparatus, cook_sem, del_sem, finish;

int newSocketFd;
int socketFd;
int cookNum, delNum;
int exitCond = 0;
int manager_order_finish = 0;
int cookExitCond = 0;
int insidePideCount = 0;
int toBeDelivered = 0;
int delivering = 0;
int pseudo_inverse;
int pide_p = 10, pide_q = 10;
int speed = 10;

void init_threads();
void join_threads();
void init_socket(char* ip, int port);
void prepare();
void cook_it();
void deliver(int x, int y);

struct order *orders;
int orderCount = 0;
int preparedOrderCount = 0;
struct order *finishedOrders;
int finishedOrderCount = 0;
struct order *deliveryQueue;

void* oven_thread(){
    
    while(exitCond == 0){
        sem_wait(&inside_oven);

        if (exitCond != 0)
            break;

        pthread_mutex_lock(&oven_lock);
        insidePideCount++;
        pthread_mutex_unlock(&oven_lock);

        cook_it();

        pthread_mutex_lock(&oven_lock);
        insidePideCount--;
        pthread_mutex_unlock(&oven_lock);
    }
    return NULL;
}

void* cook_thread(){
    while (preparedOrderCount < orderCount) {
        sem_wait(&cook_sem);

        if (exitCond != 0)
            break;

        prepare();

        while (1) {
            if (pthread_mutex_trylock(&oven_entry1) == 0) {
                // Entry 1 is mine now.
                char *log = "Cook acquired oven entry 1.\n";
                log_it("server_log.log",log); 

                pthread_mutex_lock(&oven_lock);
                if (insidePideCount < OVEN_SIZE) {
                    sem_post(&inside_oven);
                    pthread_mutex_unlock(&oven_lock);
                    pthread_mutex_unlock(&oven_entry1);
                    break;
                }
                pthread_mutex_unlock(&oven_lock);
                pthread_mutex_unlock(&oven_entry1);
                log = "Cook released oven entry 1.\n";
                log_it("server_log.log",log); 

            } else if (pthread_mutex_trylock(&oven_entry2) == 0) {
                // Entry 2 is mine
                char *log = "Cook acquired oven entry 2.\n";
                log_it("server_log.log",log); 

                pthread_mutex_lock(&oven_lock);
                if (insidePideCount < OVEN_SIZE) {
                    sem_post(&inside_oven);
                    pthread_mutex_unlock(&oven_lock);
                    pthread_mutex_unlock(&oven_entry2);
                    break;
                }
                pthread_mutex_unlock(&oven_lock);
                pthread_mutex_unlock(&oven_entry2);
                log = "Cook released oven entry 2.\n";
                log_it("server_log.log",log); 
            }
        }
    }
    return NULL;
}

void prepare(){

    usleep(pseudo_inverse);
    char *log = "Order prepared.\n";
    log_it("server_log.log",log); 
    pthread_mutex_lock(&prep_mutex);
    preparedOrderCount++;
    pthread_mutex_unlock(&prep_mutex);

}

void cook_it(){
    sem_wait(&oven_aparatus);
    sem_post(&oven_aparatus);

    usleep(pseudo_inverse / 2);
    char *log = "Order cooked.\n";
    log_it("server_log.log",log); 

    pthread_mutex_lock(&finish_mutex);

    finishedOrders[finishedOrderCount] = orders[finishedOrderCount];
    finishedOrderCount++;
    if (finishedOrderCount == orderCount){
        log = "Cooking orders is finished.\n";
        log_it("server_log.log",log); 

        manager_order_finish = 1;
    }
    
    sem_post(&finish);
    pthread_mutex_unlock(&finish_mutex);

}

void* manager_thread(){

    for (int i = 0; i < orderCount; i++)
    {
        sem_post(&cook_sem); // Here is the order, cook it.
    }

    char *log = "All cooks awakened.\n";
    log_it("server_log.log",log); 

    while(manager_order_finish == 0){
        sem_wait(&finish);
        pthread_mutex_lock(&deliver_mutex);
        deliveryQueue[toBeDelivered] = orders[toBeDelivered];
        toBeDelivered++;
        pthread_mutex_unlock(&deliver_mutex);
        sem_post(&del_sem);
        // send it to delivery
    }

    sem_wait(&finish); // Wait for the last delivery
    log = "Delivering finished. Exiting gracefully.\n";
    log_it("server_log.log",log); 

    exitCond = 1;
    for (int i = 0; i < OVEN_SIZE; i++)
    {
        sem_post(&inside_oven); // wake up and exit.
    }
    for (int i = 0; i < cookNum; i++)
    {
        sem_post(&cook_sem); // wake up and exit.
    }
    for (int i = 0; i < delNum; i++)
    {
        sem_post(&del_sem); // wake up and exit.
    }
    
    return NULL;
}

void* delivery_thread(){

    int package_x = 0, package_y = 0;

    while (exitCond == 0)
    {
        sem_wait(&del_sem);

        if (exitCond != 0)
            break;
        
        pthread_mutex_lock(&deliver_mutex);

        if (toBeDelivered > 0 && delivering < orderCount)
        {
            package_x = deliveryQueue[delivering].x;
            package_y = deliveryQueue[delivering].y;
            delivering++;
        }

        pthread_mutex_unlock(&deliver_mutex);

        deliver(package_x, package_y);

        pthread_mutex_lock(&deliver_mutex);
        if (delivering == orderCount)
        {
            sem_post(&finish);
            pthread_mutex_unlock(&deliver_mutex);
            break;
        }
        pthread_mutex_unlock(&deliver_mutex);
    }
    
    return NULL;
}

void deliver(int x, int y){
    int goTime = (abs(pide_p - x) / speed) + (abs(pide_q - y) / speed);
    usleep(goTime * 1000000); // GO TO DELIVER
    char *log = "Order delivered.\n";
    log_it("server_log.log",log); 

    usleep(goTime * 1000000); // RETURN TO PIDE
    log = "Delivery person returned to the pideshop.\n";
    log_it("server_log.log",log); 
}

void sigint_handler() {

    printf("SIGINT Received. Exiting...\n"); 

    exitCond = 1;

    for (int i = 0; i < cookNum; i++)
    {
        sem_post(&cook_sem);
    }

    for (int i = 0; i < OVEN_SIZE; i++)
    {
        sem_post(&inside_oven);
    }
    
    
    join_threads();
    char *log = "SIGINT Received. Exiting...\n";
    log_it("server_log.log",log);

    free(deliveryQueue);
    free(finishedOrders);
    free(ovens);
    free(orders);
    free(cooks);
    free(deliveryPersons);
    close(socketFd);
    close(newSocketFd);
    sem_close(&oven_aparatus);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Usage: ./PideShop <ip> <port> <cookSize> <deliverySize> <speed>\n");
        exit(EXIT_FAILURE);
    }
    
    char ip[20];
    strcpy(ip, argv[1]);
    int port = atoi(argv[2]);
    cookNum = atoi(argv[3]);
    delNum = atoi(argv[4]);
    speed = atoi(argv[5]);

    struct sigaction sa_int;

    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

    pseudo_inverse = p_inverse();

    sem_init(&oven_aparatus, 0, OVEN_APARATUS_COUNT); // 3
    sem_init(&cook_sem, 0, 0);
    sem_init(&del_sem, 0, 0);
    sem_init(&inside_oven, 0, 0); // 6
    sem_init(&finish, 0, 0);
    
    init_socket(ip, port);

    struct order initial;
    read(newSocketFd, &initial, sizeof(struct order));

    pide_p = initial.p;
    pide_q = initial.q;
    orderCount = initial.orderCount;

    orders = (struct order*)malloc(sizeof(struct order) * orderCount);
    finishedOrders = (struct order*)malloc(sizeof(struct order) * orderCount);
    deliveryQueue = (struct order*)malloc(sizeof(struct order) * orderCount);

    printf(">> %d new customers.. Serving\n",orderCount);
    char *log = (char*)malloc(100);
    sprintf(log, "%d new customers..\n",orderCount);
    log_it("server_log.log",log); 

    for (int i = 0; i < orderCount; i++)
    {
        read(newSocketFd, &orders[i], sizeof(struct order));
    }
    
    init_threads();
    join_threads();

    printf(">> Done serving client @ XXX PID %d\n",initial.pid);
    sprintf(log, "Done serving client @ XXX PID %d\n",initial.pid);
    log_it("server_log.log",log); 
    free(log);

    char *response = "All customers served.\0";
    send(newSocketFd, response, strlen(response) + 1, 0);

    free(deliveryQueue);
    free(orders);
    free(finishedOrders);
    free(ovens);
    free(cooks);
    free(deliveryPersons);
    close(newSocketFd);
    close(socketFd);   
    sem_close(&oven_aparatus);
    return 0;
}

void init_socket(char* ip, int port){
    int opt = 1;
    struct sockaddr_in address;
    
    socketFd = socket(AF_INET , SOCK_STREAM, 0);

    if (socketFd == -1)
    {
        char *log = "Socket open failed\n";
        log_it("server_log.log",log); 
        perror("Socket open failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
    {
        char *log = "Error: setsocketopt\n";
        log_it("server_log.log",log); 
        perror("set socketopt");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip);

    if (bind(socketFd, (struct sockaddr *)&address , sizeof(address)) < 0)
    {
        char *log = "Bind failed\n";
        log_it("server_log.log",log); 
        perror("bind");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    if (listen(socketFd, 3) < 0){
        char *log = "Listen failed\n";
        log_it("server_log.log",log); 
        perror("listen");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    char *log = "Socket initialized.\n";
    log_it("server_log.log",log);    

    printf(">> PideShop active waiting for connection\n");
    int addrlen = sizeof(address);
    if((newSocketFd = accept(socketFd, (struct sockaddr *)&address , (socklen_t*)&addrlen)) < 0){
        char *log = "Accept failed\n";
        log_it("server_log.log",log); 
        perror("accept");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
}

void init_threads(){
    cooks = (pthread_t*)malloc(cookNum * sizeof(pthread_t));
    deliveryPersons = (pthread_t*)malloc(delNum * sizeof(pthread_t));
    ovens = (pthread_t*)malloc(OVEN_SIZE * sizeof(pthread_t));

    pthread_create(&manager, NULL, manager_thread, NULL);

    for (int i = 0; i < OVEN_SIZE; i++)
    {
        pthread_create(&ovens[i], NULL, oven_thread, NULL);
    }

    for (int i = 0; i < cookNum; i++)
    {
        pthread_create(&cooks[i], NULL, cook_thread, NULL);
    }
    
    for (int i = 0; i < delNum; i++)
    {
        pthread_create(&deliveryPersons[i], NULL, delivery_thread, NULL);
    }
    
    

    char *log = "Threads initialized.\n";
    log_it("server_log.log",log);

}

void join_threads(){
    for (int i = 0; i < OVEN_SIZE; i++)
    {
        pthread_join(ovens[i], NULL);
    }
    for (int i = 0; i < cookNum; i++)
    {
        pthread_join(cooks[i], NULL);
    }

    for (int i = 0; i < delNum; i++)
    {
        pthread_join(deliveryPersons[i], NULL);
    }

    pthread_join(manager, NULL);

    char *log = "Threads joined.\n";
    log_it("server_log.log",log);
}