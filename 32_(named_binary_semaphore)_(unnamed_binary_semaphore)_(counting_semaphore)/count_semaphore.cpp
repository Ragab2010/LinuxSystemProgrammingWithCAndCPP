#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

// Define a counting semaphore
sem_t sem;

// Thread function
void *thread_function(void *arg) {
    // Wait on the semaphore
    sem_wait(&sem);
    
    // Critical section
    printf("Thread %ld entered the critical section.\n", (long)arg);
    sleep(1); // Simulate some work in the critical section
    printf("Thread %ld exited the critical section.\n", (long)arg);
    
    // Release the semaphore
    sem_post(&sem);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the semaphore with an initial value of 3
    sem_init(&sem, 0, 3);

    // Create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void *)i);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&sem);

    return 0;
}
