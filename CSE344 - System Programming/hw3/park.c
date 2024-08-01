#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>

#define MAX_AUTOMOBILES 8
#define MAX_PICKUPS 4
#define TOTAL_CAR_NUM 30

sem_t newAutomobile, inChargeforAutomobile;
sem_t newPickup, inChargeforPickup;
sem_t lock;

int mFree_automobile = MAX_AUTOMOBILES;
int mFree_pickup = MAX_PICKUPS;
int mAutomobile_main = 0;
int mPickup_main = 0;

void *automobileOwner() {
    sem_wait(&lock);
    if (mFree_automobile > 0) {
        sem_post(&newAutomobile);
        mFree_automobile--;

        printf("Automobile came to the temporary parking lot. Remaining spots in temporary lot for automobiles: %d\n", mFree_automobile);

        sem_post(&inChargeforAutomobile);
    } else {
        printf("No parking space available for automobiles. Owner is leaving.\n");
    }
    sem_post(&lock);
    return NULL;
}

void *pickupOwner() {
    sem_wait(&lock);
    if (mFree_pickup > 0) {
        sem_post(&newPickup);
        mFree_pickup--;

        printf("Pickup came to the temporary parking lot. Remaining spots in temporary lot for pickups: %d\n", mFree_pickup);

        sem_post(&inChargeforPickup);
    } else {
        printf("No parking space available for pickups. Owner is leaving.\n");
    }
    sem_post(&lock);
    return NULL;
}

void *automobileAttendant() {
    while (1) {
        sem_wait(&inChargeforAutomobile);

        sem_wait(&lock);
        if (mAutomobile_main < MAX_AUTOMOBILES) {
            mFree_automobile++;
            mAutomobile_main++;
            printf("Automobile Valet: Automobile attendant is moving the car. Spots available in main lot: %d\n", MAX_AUTOMOBILES - mAutomobile_main);
        } else {
            printf("Automobile Valet: No parking space in main lot for automobiles.\n");
        }
        sem_post(&lock);
    }
    return NULL;
}

void *pickupAttendant() {
    while (1) {
        sem_wait(&inChargeforPickup);
        
        sem_wait(&lock);
        if (mPickup_main < MAX_PICKUPS) {
            mFree_pickup++;
            mPickup_main++;
            printf("Pickup Valet: Pickup attendant is moving the pickup. Spots available in main lot: %d\n", MAX_PICKUPS - mPickup_main);
        } else {
            printf("Pickup Valet: No parking space in main lot for pickups.\n");
        }        
        sem_post(&lock);
    }
    return NULL;
}

void sigint_handler() {

    printf("\nSIGINT received. Exiting.\n");
    sem_destroy(&newAutomobile);
    sem_destroy(&inChargeforAutomobile);
    sem_destroy(&newPickup);
    sem_destroy(&inChargeforPickup);
    sem_destroy(&lock);
    exit(EXIT_SUCCESS);
}

int main() {
    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sigfillset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigint sigaction");
        exit(EXIT_FAILURE);
    }

    sem_init(&newAutomobile, 0, 0);
    sem_init(&newPickup, 0, 0);
    sem_init(&inChargeforAutomobile, 0, 0);
    sem_init(&inChargeforPickup, 0, 0);
    sem_init(&lock, 0, 1);

    pthread_t owners[TOTAL_CAR_NUM], attendants[2];
    int vehicleTypes[TOTAL_CAR_NUM];

    srand(time(NULL));

    for (int i = 0; i < TOTAL_CAR_NUM; i++) { // 1 for Automobiles, 2 for Pickups
        vehicleTypes[i] = rand() % 2 + 1;
    }

    pthread_create(&attendants[0], NULL, automobileAttendant, NULL);
    pthread_create(&attendants[1], NULL, pickupAttendant, NULL);

    for (int i = 0; i < TOTAL_CAR_NUM; i++) {
        if (vehicleTypes[i] == 1) {
            pthread_create(&owners[i], NULL, automobileOwner, NULL);
        } else {
            pthread_create(&owners[i], NULL, pickupOwner, NULL);
        }
    }

    for (int i = 0; i < TOTAL_CAR_NUM; i++) {
        pthread_join(owners[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_cancel(attendants[i]); // It is safer to impelement like that.
        pthread_join(attendants[i], NULL);
    }

    sem_destroy(&newAutomobile);
    sem_destroy(&inChargeforAutomobile);
    sem_destroy(&newPickup);
    sem_destroy(&inChargeforPickup);
    sem_destroy(&lock);

    return 0;
}
