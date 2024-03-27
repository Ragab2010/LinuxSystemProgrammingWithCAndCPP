

/*
*  thread_race_condition_processes_avoid_by_binary_unnamed_semaphores.cpp: The main() creates two process,
*  allocate shared memory segment for int8_t variable pCounter 
*  allocate shared memory segment for sem_t variable 
*  parent do a fork and child process calls  increment() 
*  parent process calls decrement() and then wait for termination of child
*  Finally main thread displays the value of global variable
*  compile: $ g++ thread_race_condition_processes_avoid_by_binary_unnamed_semaphores.c -o thread_race_condition_processes_avoid_by_binary_unnamed_semaphores -lpthread
*  usage: $./thread_race_condition_processes_avoid_by_binary_unnamed_semaphores
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
    
   //mutex variable should be located in shared memory

    int shared_memory_semaphore_id = shmget(IPC_PRIVATE , sizeof(sem_t) , IPC_CREAT | 0666);
    if(shared_memory_semaphore_id == -1){
        cerr << "Shared memory creation failed for semaphore variable" << endl;
        return 1;
    }
    //atatch the semaphore to the address space of the process 
    pMutex = (sem_t*) shmat(shared_memory_semaphore_id , NULL , 0);

    //initialize the semaphore 
    /*
    sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    -pMutex:the sem_t pointer variable 
    - 0: the semaphore will shared between threads , if great than 1 will shared between process
    -(1): the value of the semaphore  (0,1) binary 
    */
    int semaphore_status = sem_init(pMutex,1 , 1);
    if(semaphore_status == -1){
        cerr << "Semaphore initialization failed" << endl;
        return 2;
    }
    

    // Create shared memory for counter

    int shared_memory_count_id = shmget(IPC_PRIVATE , sizeof(int8_t) ,IPC_CREAT| 0666);
    if(shared_memory_count_id == -1){
        cerr << "Shared memory creation failed for counter variable" << endl;
        return 3;
    }
    //attach the counter variable 
    pCounter =(int8_t *) shmat(shared_memory_count_id , NULL, 0);
    *pCounter =0;

    int cpid= fork();
    if(cpid == 0){
        //child process 
        increment((void *)&num_iterations);
        shmdt(pCounter);
        shmdt(pMutex);
        return 0;
    } else if (cpid > 0){
        //parent process
        decrement((void *)&num_iterations);
        waitpid(cpid,NULL,0);
        printf("Final counter value: %d\n", *pCounter);
        shmdt(pCounter);
        shmdt(pMutex);
        shmctl(shared_memory_count_id , IPC_RMID , NULL);
        shmctl(shared_memory_semaphore_id , IPC_RMID , NULL);
        sem_close(pMutex);
        sem_destroy(pMutex);
        return 0;
    } else {
        // Fork failed
        cerr << "Fork failed" << endl;
        return 3;
    }

}
