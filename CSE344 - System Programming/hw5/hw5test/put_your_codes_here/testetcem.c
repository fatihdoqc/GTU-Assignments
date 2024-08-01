#include "utilities.h"

pthread_mutex_t mutex;

struct buffer *buff;
int bufferSize = 10;
int buffIndex = 0;

void init_buff(struct buffer *buff, int *currIndex){
    *currIndex = 0;
    for (int i = 0; i < bufferSize; i++) {
        buff[i].destfd = 5;
    }
}

void main(){

    buff = calloc(bufferSize, sizeof(struct buffer));
    init_buff(buff, &buffIndex);

    printf("dd: %d \n",buff[0].destfd);

    free(buff);

}