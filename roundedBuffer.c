#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5   // buffer size (circular)

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    while(1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = 1;   // produce
        in = (in + 1) % SIZE;  // circular movement
        printf("Producing and producing\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }
}

void* consumer(void* arg) {
    while(1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];  // consume
        out = (out + 1) % SIZE;  // circular movement
        printf("Consuming and consuming\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
