#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex;
sem_t resource;
int readers_count = 0;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&resource);
        }
        sem_post(&mutex);

        printf("Reader %d is reading\n", *(int *)arg);
        sleep(1);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&resource);
        }
        sem_post(&mutex);

        sleep(2);
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&resource);

        printf("Writer %d is writing\n", *(int *)arg);
        sleep(1);

        sem_post(&resource);

        sleep(2);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&resource, 0, 1);

    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&resource);

    return 0;
}
