#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int counter = 0;
pthread_mutex_t mutex;
void *incrementCounter(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);

        counter++;
        printf("Thread %d: Counter value: %d\n", *(int *)arg, counter);

        pthread_mutex_unlock(&mutex);

        usleep(1000);
    }

    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;

    int threadArg1 = 1;
    int threadArg2 = 2;

    pthread_create(&thread1, NULL, incrementCounter, (void *)&threadArg1);
    pthread_create(&thread2, NULL, incrementCounter, (void *)&threadArg2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    pthread_mutex_destroy(&mutex);

    return 0;
}
