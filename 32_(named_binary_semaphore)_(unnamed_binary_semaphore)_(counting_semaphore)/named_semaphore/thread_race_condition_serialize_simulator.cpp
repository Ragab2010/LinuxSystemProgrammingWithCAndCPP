/*
*  thread_race_condition_serialize_simulator.cpp: The main() creates three threads,
*  each thread displays a string in a random fashion
*  compile: $ g++ thread_race_condition_serialize_simulator.cpp -lpthread -D_REENTRANT -o thread_race_condition_serialize_simulator
*  usage: $./thread_race_condition_serialize_simulator
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void * f1(void *);
void * f2(void *);
void * f3(void *);
int main() {
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
void * f1(void * parm){
    printf(" Egypt");
    return NULL;
}    
void * f2(void * parm){
    printf(" In");
    return NULL;
}    
void * f3(void * parm){
    printf(" Welcome ");
    return NULL;
}    
