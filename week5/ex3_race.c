#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"

#define MAX_CAPACITY 10
#define CONSUMERS 2

typedef struct buffer {
    int *values;
    int capacity;
    int length;
    int consumer_mutex;
    int producer_mutex;
} buffer_t;

buffer_t *create_buffer(int capacity) {
    buffer_t *buf = malloc(sizeof(buffer_t));
    buf->capacity = capacity;
    buf->length = 0;
    buf->consumer_mutex = 1;
    buf->producer_mutex = 0;
    buf->values = malloc(capacity * sizeof(int));
    return buf;
}

void lock_producer(buffer_t* buffer) {
    while (buffer->producer_mutex) {
        // sleep(0.001);
    }
    buffer->producer_mutex = 1;
}
void lock_consumer(buffer_t* buffer) {
    while (buffer->consumer_mutex) {
        // sleep(0.001);
    }
    buffer->consumer_mutex = 1;
}

void unlock_producer(buffer_t* buffer) {
    buffer->producer_mutex = 0;
}
void unlock_consumer(buffer_t* buffer) {
    buffer->consumer_mutex = 0;
}


void consumer(buffer_t *buffer) {
    while (1) {
        // printf("Locking consumer\n");
        lock_consumer(buffer);
        // printf("Locked consumer\n");
        printf("Consumed data with length: %d\n", buffer->length);
        for (int i = 0; i < buffer->length; i++) {
            printf("Data #%d: %d\n", i + 1, buffer->values[i]);
        }
        buffer->length = 0;

        unlock_producer(buffer);
        int time = rand() % 5;
        // usleep(time * 1000);
    }
}

void send(buffer_t *buf, int *values, int length) {
    // printf("Locking\n");
    lock_producer(buf);
    // printf("Locked\n");
    printf("Sending data with length: %d\n", length);
    for (int i = 0; i < length; i++) {
        buf->values[i] = values[i];
        printf("Sending: %d\n", buf->values[i]);
    }
    buf->length = length;
    // printf("Unlocking\n");
    unlock_consumer(buf);
    // printf("Unlocked\n");
}

void producer(buffer_t *buffer) {
    while (1) {
        int length = (rand() % (MAX_CAPACITY - 2)) + 2;
        int *values = malloc(length * sizeof(int));
        for (int i = 0; i < length; i++) {
            values[i] = rand() % 200;
        }
        send(buffer, values, length);
        free(values);
        // usleep(5 * 1000);
        // sleep(5);
    }
}

int main() {
    srand(0);
    // printf("Creating buffer\n");
    buffer_t *buf = create_buffer(MAX_CAPACITY);
  
    // printf("Creating consumers\n");
    pthread_t consumer_threads[CONSUMERS];
    for (int i = 0; i < CONSUMERS; i++) {
        pthread_create(consumer_threads + i, NULL, consumer, buf);
    }

    // printf("Creating producer\n");
    pthread_t producer_thread;
    pthread_create(&producer_thread, NULL, producer, buf);

    pthread_join(producer, NULL);
    // printf("Joined producer\n");
    for (int i = 0; i < CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }
    // printf("Joined consumers\n");
    free(buf->values);
    free(buf);
}