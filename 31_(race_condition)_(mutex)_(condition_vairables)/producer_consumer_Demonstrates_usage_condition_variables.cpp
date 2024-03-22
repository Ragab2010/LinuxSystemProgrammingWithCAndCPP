/*
Explanation:

The code defines a fixed-size buffer, buffer, to hold produced items.
Two threads, producer and consumer, are created.
mutex protects access to the buffer and shared variables (in, out, and count).
empty signals the consumer when the buffer becomes empty.
full signals the producer when there's space in the buffer.
The producer thread:
Acquires the mutex.
Waits on empty if the buffer is full.
Produces an item and updates buffer indices and count.
Signals full to wake up the consumer.
Releases the mutex.
The consumer thread:
Acquires the mutex.
Waits on full if the buffer is empty.
Consumes an item and updates buffer indices and count.
Signals empty to wake up the producer.
Releases the mutex.
Benefits of Condition Variables:

Synchronization: They help coordinate thread execution based on specific conditions.
Waiting Efficiency: Threads can wait efficiently while other threads modify shared data.
Flexibility: They allow for more granular control over thread wakeup strategies (e.g., broadcast vs. single wakeup).

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t empty, full;

void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }

        // Produce an item
        buffer[in] = rand() % 100;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produced: %d\n", buffer[in - 1]);
        sleep(1);
        // Signal consumer if buffer is no longer empty
        pthread_cond_signal(&full);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is empty
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        // Consume an item
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumed: %d\n", item);
        sleep(1);
        // Signal producer if buffer has space
        pthread_cond_signal(&empty);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    printf("the Buffer size is:%d\n" , BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}
