#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *createThreadFunction(void *arg) {
    printf("This is a created thread.\n");
    pthread_exit(NULL);
}
void *joinThreadFunction(void *arg) {
    printf("This is a thread to join.\n");
    pthread_exit(NULL);
}
void *equalThreadFunction(void *arg) {
    printf("This is a thread.\n");
    pthread_exit(NULL);
}
void *exitThreadFunction(void *arg) {
    printf("This is a thread exiting with value 42.\n");
    pthread_exit((void *)42);
}
int main() {
    pthread_t createThread, joinThread, equalThread, exitThread;
    void *returnValue;
    if (pthread_create(&createThread, NULL, createThreadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }
    if (pthread_create(&joinThread, NULL, joinThreadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread to join.\n");
        return 1;
    }
    if (pthread_join(joinThread, NULL) != 0) {
        fprintf(stderr, "Error joining thread.\n");
        return 1;
    }
    if (pthread_create(&equalThread, NULL, equalThreadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread for equality check.\n");
        return 1;
    }
    pthread_t equalThread2;
    if (pthread_create(&equalThread2, NULL, equalThreadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating another thread for equality check.\n");
        return 1;
    }
    if (pthread_equal(equalThread, equalThread2)) {
        printf("Threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }
    pthread_join(equalThread, NULL);
    pthread_join(equalThread2, NULL);
    if (pthread_create(&exitThread, NULL, exitThreadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread for exit with a value.\n");
        return 1;
    }
    if (pthread_join(exitThread, &returnValue) != 0) {
        fprintf(stderr, "Error joining thread with exit value.\n");
        return 1;
    }
    printf("Thread returned: %ld\n", (long)returnValue);
    printf("Main thread exiting.\n");
    return 0;
}
