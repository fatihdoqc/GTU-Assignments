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

int main(int argc , char *argv[])
{
    // ./Hungry ip port client p q
    char ip[20];
    strcpy(ip, argv[1]);
    int port = atoi(argv[2]);
    int numberOfOrders = atoi(argv[3]);
    int map_p = atoi(argv[4]); // x
    int map_q = atoi(argv[5]); // y

    printf("%s %d %d %d %d\n",ip, port, numberOfOrders, map_p, map_q);

    int socketFd = 0;
    struct sockaddr_in server_addr;
    char buffer[1024];

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
        perror("invalid address");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    if (connect(socketFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    struct order *orders = (struct order*)malloc(sizeof(struct order*) * numberOfOrders);
    struct order initial;
    initial.p = map_p;
    initial.q = map_q;
    initial.pid = getpid();
    initial.orderCount = numberOfOrders;

    send(socketFd, &initial, sizeof(struct order), 0);

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
    
    //send(socketFd, response, strlen(response) + 1, 0);

    read(socketFd, buffer, sizeof(buffer));
    printf("Server said: %s\n",buffer);

    close(socketFd);
    return 0;
    
}