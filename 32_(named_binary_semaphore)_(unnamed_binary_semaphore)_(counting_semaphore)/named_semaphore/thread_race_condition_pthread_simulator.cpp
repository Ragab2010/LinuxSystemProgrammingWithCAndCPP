
/*
*  thread_race_condition_pthread_simulator.cpp: The main() creates two threads,
*  one thread execute increment() and other execute decrement()
*  both functions operate on a shared global variable (counter)
*  Finally main thread displays the value of global variable
*  compile: $ g++ thread_race_condition_pthread_simulator.cpp -o thread_race_condition_pthread_simulator -lpthread
*  usage: $./thread_race_condition_pthread_simulator 
*/
#include <stdio.h>
#include <pthread.h>
#include <iostream>
int counter = 0;  // Global variable

void* increment(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        counter++;  // Potential race condition
    }
    return NULL;
}

void* decrement(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        counter--;  // Potential race condition
    }
    return NULL;
}

int main() {

    pthread_t thread1, thread2;
    int num_iterations = 100000;  // Number of iterations per thread
    std::cout << "two threads:"<<std::endl;
    std::cout<<"   one thread increment: "<< num_iterations<<std::endl;
    std::cout<<"second thread decrement: "<< num_iterations<<std::endl;
    std::cout << "the Correct counter value: 0 "<< std::endl;
    pthread_create(&thread1, NULL, increment, &num_iterations);
    pthread_create(&thread2, NULL, decrement, &num_iterations);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", counter);

    return 0;
}
