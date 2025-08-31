#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5   // buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;   // semaphores
pthread_mutex_t mutex;

void* producer(void* arg) {
    while(1) {
        sem_wait(&empty);              // wait for empty slot
        pthread_mutex_lock(&mutex);    // lock critical section

        buffer[in] = 1; // produce item
        in = (in + 1) % SIZE;
        printf("Producing and producing\n");

        pthread_mutex_unlock(&mutex);  // unlock
        sem_post(&full);               // signal full

        sleep(1); // slow down output
    }
}

void* consumer(void* arg) {
    while(1) {
        sem_wait(&full);               // wait for full slot
        pthread_mutex_lock(&mutex);    // lock critical section

        int item = buffer[out]; // consume item
        out = (out + 1) % SIZE;
        printf("Consuming and consuming\n");

        pthread_mutex_unlock(&mutex);  // unlock
        sem_post(&empty);              // signal empty

        sleep(1); // slow down output
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);  // initially all slots empty
    sem_init(&full, 0, 0);      // initially no item
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
// This code implements the Producer-Consumer problem using semaphores and mutexes in C.