#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include "utilities.h"
#include "log.h"
#include <signal.h>

struct order *orders;
int socketFd = 0;

void sigint_handler() {

    printf("SIGINT Received. Exiting...\n");  

    char *log = "SIGINT Received. Exiting...\n";
    log_it("client_log.log",log);

    free(orders);
    close(socketFd);
    exit(EXIT_SUCCESS);
}

int main(int argc , char *argv[])
{
    if (argc != 6)
    {
        printf("Usage: ./HungryVeryMuch <ip> <port> <numberOfOrders> <p> <q>\n");
        exit(EXIT_FAILURE);
    }

    struct sigaction sa_int;

    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        char *log = "SIGINT SIGACITON\n";
        log_it("client_log.log",log);
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

    // ./Hungry ip port client p q
    char ip[20];
    strcpy(ip, argv[1]);
    int port = atoi(argv[2]);
    int numberOfOrders = atoi(argv[3]);
    int map_p = atoi(argv[4]); // x
    int map_q = atoi(argv[5]); // y

    struct sockaddr_in server_addr;
    char buffer[1024];

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        char *log = "Socket\n";
        log_it("client_log.log",log);
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
        char *log = "Invalid address\n";
        log_it("client_log.log",log);
        perror("invalid address");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    if (connect(socketFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        char *log = "Connect\n";
        log_it("client_log.log",log);
        perror("connect");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    printf(">> PID %d..\n",getpid());

    struct order *orders = (struct order*)malloc(sizeof(struct order) * numberOfOrders);
    struct order initial;
    initial.p = map_p;
    initial.q = map_q;
    initial.pid = getpid();
    initial.orderCount = numberOfOrders;

    send(socketFd, &initial, sizeof(struct order), 0);
    char *log = "Initial struct sent.\n";
    log_it("client_log.log",log);

    srand(time(NULL));
    for (int i = 0; i < numberOfOrders; i++)
    {
        orders[i].x = rand() % map_p;
        orders[i].y = rand() % map_q;
        orders[i].p = map_q;
        orders[i].q = map_q;
        orders[i].pid = getpid();
        orders[i].orderCount = numberOfOrders;

        send(socketFd, &orders[i], sizeof(struct order), 0);
    }

    log = "Orders sent\n";
    log_it("client_log.log",log);
    
    //send(socketFd, response, strlen(response) + 1, 0);

    read(socketFd, buffer, sizeof(buffer));
    printf(">> %s\n",buffer);
    log = "Orders completed.\n";
    log_it("client_log.log",log);

    printf(">> log file written..\n");

    close(socketFd);
    free(orders);
    return 0;
    
}