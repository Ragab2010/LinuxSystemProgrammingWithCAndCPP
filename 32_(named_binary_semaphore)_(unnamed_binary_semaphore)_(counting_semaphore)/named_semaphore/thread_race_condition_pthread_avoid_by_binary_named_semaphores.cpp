
/*
*  thread_race_condition_pthread_avoid_by_binary_named_semaphores.cpp: The main() creates two threads,
*  one thread execute increment() and other execute decrement()
*  both functions operate on a shared global variable (counter)
*  after achieving lock using mutex variable
*  Finally main thread displays the value of global variable
*  compile: $ g++ thread_race_condition_pthread_avoid_by_binary_named_semaphores.cpp -o thread_race_condition_pthread_avoid_by_binary_named_semaphores -lpthread
*  usage: $./thread_race_condition_pthread_avoid_by_binary_named_semaphores 
*/

#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

int counter = 0;
sem_t *pMutex;
//we can initialize mutex staticly
// pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        sem_wait(pMutex);  // Acquire mutex before incrementing
        counter++;
        sem_post(pMutex);  // Release mutex after incrementing
    }
    return NULL;
}

void* decrement(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        sem_wait(pMutex);  // Acquire mutex before incrementing
        counter--;
        sem_post(pMutex);  // Release mutex after incrementing
    }
    return NULL;
}

int main() {

    int num_iterations = 100000;  // Number of iterations per thread
    std::cout << "two threads:"<<std::endl;
    std::cout<<"   one thread increment: "<< num_iterations<<std::endl;
    std::cout<<"second thread decrement: "<< num_iterations<<std::endl;
    std::cout << "the Correct counter value: 0 "<< std::endl;
    /*
    sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    -"\sem":name of the semaphore
    -O_CREAT: mode to create semaphore
    -0666 the permission 
    -(1): the value of the semaphore  (0,1) binary 
    */
    const char * name_of_semaphore ="/semaphore1";
    pMutex = sem_open(name_of_semaphore , O_CREAT , 0666 ,1);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment, &num_iterations);
    pthread_create(&thread2, NULL, decrement, &num_iterations);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //close the semaphore
    sem_close(pMutex);
    //remove the semphore
    sem_unlink(name_of_semaphore);

    printf("Final counter value: %d\n", counter);

    return 0;
}
