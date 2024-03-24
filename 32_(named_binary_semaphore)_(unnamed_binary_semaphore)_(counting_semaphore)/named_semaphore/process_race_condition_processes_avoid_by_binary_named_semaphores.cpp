

/*
*  process_race_condition_processes_avoid_by_binary_named_semaphores.cpp: The main() creates two threads,
*  allocate shared memory segment for int8_t variable pCounter 
*  allocate shared memory segment for sem_t variable 
*  parent do a fork and child process calls  increment() 
*  parent process calls decrement() and then wait for termination of child
*  Finally main thread displays the value of global variable
*  compile: $ g++ thread_race_condition_processes_avoid_by_binary_unnamed_semaphores.c -o process_race_condition_processes_avoid_by_binary_named_semaphores -lpthread
*  usage: $./process_race_condition_processes_avoid_by_binary_named_semaphores
*/


#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h> // Needed for O_CREAT, O_EXCL
#include <semaphore.h>

using namespace std;

int8_t *pCounter ;  // Global variable
sem_t *pMutex; //semaphore

void* increment(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        sem_wait(pMutex);  // Acquire mutex before incrementing
        (*pCounter)++;  // Potential race condition
        sem_post(pMutex);  // Release mutex after incrementing
    }
    return NULL;
}

void* decrement(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        sem_wait(pMutex);  // Acquire mutex before incrementing
        (*pCounter)--;  // Potential race condition
        sem_post(pMutex);  // Release mutex after incrementing
    }
    return NULL;
}

int main() {
    int num_iterations = 100000;  // Number of iterations per thread
    std::cout << "two threads:"<<std::endl;
    std::cout<<"   one process increment: "<< num_iterations<<std::endl;
    std::cout<<"second process decrement: "<< num_iterations<<std::endl;
    std::cout << "the Correct counter value: 0 "<< std::endl;
    
    //initialize the semaphore 
    /*
    sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    -"\sem":name of the semaphore
    -_CREAT | O_EXCL : mode to create semaphore
    -0666 the permission 
    -(1): the value of the semaphore  (0,1) binary 
    */
    const char * name_of_semaphore ="/semaphore1";
    pMutex = sem_open(name_of_semaphore , O_CREAT | O_EXCL , 0666 , 1);

    //create shared memory 
    key_t myKey = ftok("myfile" , 55);
    int shared_memory_id = shmget(myKey , sizeof(int8_t) ,IPC_CREAT| 0666);
    if(shared_memory_id == -1){
        cerr<<"shared_memory creation failed"<<endl;
        return 1;
    }

    pCounter =(int8_t *) shmat(shared_memory_id , NULL, 0);
    *pCounter =0;

    int cpid= fork();
    if(cpid == 0){
        //child process 
        increment((void *)&num_iterations);
        shmdt(pCounter);
        sem_close(pMutex);
        return 0;
    }else{
        //parent process
        decrement((void *)&num_iterations);
        waitpid(cpid,NULL,0);
        printf("Final counter value: %d\n", *pCounter);
        shmdt(pCounter);
        shmctl(shared_memory_id , IPC_RMID , NULL);
        sem_close(pMutex);
        sem_unlink(name_of_semaphore);
        return 0;
    }

    return 0;
}
