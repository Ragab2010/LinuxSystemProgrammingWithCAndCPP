#include <stdio.h>
#include <pthread.h>
#include <iostream>

int counter = 0;
pthread_mutex_t mutex;
//we can initialize mutex staticly
// pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        pthread_mutex_lock(&mutex);  // Acquire mutex before incrementing
        counter++;
        pthread_mutex_unlock(&mutex);  // Release mutex after incrementing
    }
    return NULL;
}

void* decrement(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        pthread_mutex_lock(&mutex);  // Acquire mutex before decrementing
        counter--;
        pthread_mutex_unlock(&mutex);  // Release mutex after decrementing
    }
    return NULL;
}

int main() {

    int num_iterations = 100000;  // Number of iterations per thread
    std::cout << "two threads:"<<std::endl;
    std::cout<<"   one thread increment: "<< num_iterations<<std::endl;
    std::cout<<"second thread decrement: "<< num_iterations<<std::endl;
    std::cout << "the Correct counter value: 0 "<< std::endl;
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    pthread_create(&thread1, NULL, increment, &num_iterations);
    pthread_create(&thread2, NULL, decrement, &num_iterations);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);  // Destroy the mutex when done

    printf("Final counter value: %d\n", counter);

    return 0;
}
