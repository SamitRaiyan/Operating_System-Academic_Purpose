#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, rw_mutex;
int read_count = 0;
int data = 0; // shared data

void *reader(void *arg) {
    int id = *(int *)arg;
    for(int i=0; i<3; i++) {  // every reader reads 3 times
        sem_wait(&mutex);
        read_count++;
        if(read_count == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);

        printf("Reader %d is reading while writer is blocked, data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if(read_count == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for(int i=0; i<3; i++) {  // every writer writes 3 times
        sem_wait(&rw_mutex);
        data++;
        printf("Writer %d is writing while reader is blocked, data = %d\n", id, data);
        sleep(1);
        sem_post(&rw_mutex);
    }
}


int main() {
    pthread_t r[5], w[2];
    int id[5] = {1,2,3,4,5};
    int wid[2] = {1,2};

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&r[0], NULL, reader, &id[0]);
    pthread_create(&r[1], NULL, reader, &id[1]);
    pthread_create(&w[1], NULL, writer, &wid[1]);
    pthread_create(&r[2], NULL, reader, &id[2]);

    for(int i=0; i<2; i++) pthread_join(w[i], NULL);
    for(int i=0; i<3; i++) pthread_join(r[i], NULL);

    return 0;
}
