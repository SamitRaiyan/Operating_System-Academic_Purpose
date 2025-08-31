#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3   // waiting chairs

sem_t barberReady, customerReady, accessSeats;
int freeSeats = CHAIRS;

void *barber(void *arg) {
    while (1) {
        sem_wait(&customerReady);     // wait for a customer
        sem_wait(&accessSeats);
        freeSeats++;                  // customer sits in barber chair
        sem_post(&barberReady);
        sem_post(&accessSeats);

        printf("Barber is cutting hair...\n");
        sleep(2); // cutting time
        printf("Barber finished haircut.\n");
    }
}

void *customer(void *arg) {
    int id = *(int *)arg;
    sem_wait(&accessSeats);
    if (freeSeats > 0) {
        freeSeats--;
        printf("Customer %d is waiting.\n", id);
        sem_post(&customerReady);
        sem_post(&accessSeats);
        sem_wait(&barberReady);
        printf("Customer %d is getting a haircut.\n", id);
    } else {
        printf("Customer %d found no free chair and left.\n", id);
        sem_post(&accessSeats);
    }
}

int main() {
    pthread_t b, c[10];
    int id[10];

    sem_init(&barberReady, 0, 0);
    sem_init(&customerReady, 0, 0);
    sem_init(&accessSeats, 0, 1);

    pthread_create(&b, NULL, barber, NULL);

    for (int i = 0; i < 10; i++) {
        id[i] = i + 1;
        sleep(1); // customers arrive with delay
        pthread_create(&c[i], NULL, customer, &id[i]);
    }

    pthread_join(b, NULL);
    for (int i = 0; i < 10; i++) pthread_join(c[i], NULL);

    return 0;
}
