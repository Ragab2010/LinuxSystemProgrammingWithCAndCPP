/*
*  thread_race_condition_serialize_avoid_by_binary_named_semaphores.cpp: 
*  The main() creates three threads,
*  each thread displays a string in a serialized fashion
*  compile: $ g++ thread_race_condition_serialize_avoid_by_binary_named_semaphores.cpp -lpthread -D_REENTRANT -o thread_race_condition_serialize_avoid_by_binary_named_semaphores
*  usage: $./thread_race_condition_serialize_avoid_by_binary_named_semaphores
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>
#include <semaphore.h>

void * f1(void *);
void * f2(void *);
void * f3(void *);
sem_t semaphore1 , semaphore2;
int main() {

    sem_init(&semaphore1  , 0 , 0);
    sem_init(&semaphore2  , 0 , 0);
    pthread_t t1, t2,t3;
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);
    pthread_create(&t3, NULL, f3, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    printf("\n");

    return 0;
}
//show it like chain (serialization)
void * f1(void * parm){
    sem_wait(&semaphore2);
    printf("Egypt ");
    return NULL;
}    
void * f2(void * parm){
    sem_wait(&semaphore1);
    printf("In ");
    sem_post(&semaphore2);
    return NULL;
}    
void * f3(void * parm){
    printf("Welcome ");
    sem_post(&semaphore1);
    return NULL;
}    
