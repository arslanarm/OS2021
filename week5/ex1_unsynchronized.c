#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

void worker(int *i) {
    printf("Hello its thread %d\n", *i);
    printf("Exit Thread %d\n", *i);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Please enter N as a programm argument\n");
        return 1;
    }
    int n;
    sscanf(argv[1], "%d", &n);
    pthread_t* threads = malloc(n * sizeof(pthread_t));
    int *args = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Created Thread %d\n", i);
        args[i] = i;
        pthread_create(threads + i, NULL, (void * (*)(void *))worker, args + i);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(args);
    return 0;
}
