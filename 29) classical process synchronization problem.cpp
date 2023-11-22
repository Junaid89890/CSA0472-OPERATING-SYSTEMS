#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int itemCount = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
void produce() {
    pthread_mutex_lock(&mutex);
    while (itemCount == BUFFER_SIZE) {
        pthread_cond_wait(&empty, &mutex);
    }
    int item = rand() % 100;
    buffer[itemCount++] = item;
    printf("Produced: %d\n", item);
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
}
void consume() {
    pthread_mutex_lock(&mutex);
    while (itemCount == 0) {
        pthread_cond_wait(&full, &mutex);
    }
    int item = buffer[--itemCount];
    printf("Consumed: %d\n", item);
    pthread_cond_signal(&empty);

    pthread_mutex_unlock(&mutex);
}
void *producer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        produce();
        usleep(100000);  
    }
    pthread_exit(NULL);
}
void *consumer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        consume();
        usleep(150000);  
    }
    pthread_exit(NULL);
}
int main() {
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
    return 0;
}
