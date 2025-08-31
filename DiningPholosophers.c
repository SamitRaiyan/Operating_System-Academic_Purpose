#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // number of philosophers

sem_t chopstick[N];

void *philosopher(void *arg) {
    int id = *(int *)arg;

    printf("Philosopher %d is thinking...\n", id);
    sleep(1);

    sem_wait(&chopstick[id]);              // take left
    sem_wait(&chopstick[(id+1)%N]);        // take right

    printf("Philosopher %d is eating...\n", id);
    sleep(1);

    sem_post(&chopstick[id]);              // put left
    sem_post(&chopstick[(id+1)%N]);        // put right

    printf("Philosopher %d finished eating.\n", id);
}

int main() {
    pthread_t t[N];
    int id[N];

    for(int i=0;i<N;i++) sem_init(&chopstick[i],0,1);

    for(int i=0;i<N;i++) {
        id[i] = i;
        pthread_create(&t[i],NULL,philosopher,&id[i]);
    }

    for(int i=0;i<N;i++) pthread_join(t[i],NULL);

    return 0;
}