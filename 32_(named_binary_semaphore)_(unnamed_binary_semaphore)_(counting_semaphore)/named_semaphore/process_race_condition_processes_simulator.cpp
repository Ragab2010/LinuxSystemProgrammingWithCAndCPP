
/*
*  process_race_condition_processes_simulator.cpp: The main() creates two process,
*  allocate shared memory segment for int8_t variable pCounter 
*  parent do a fork and child process calls  increment() 
*  parent process calls decrement() and then wait for termination of child
*  Finally main thread displays the value of global variable
*  compile: $ g++ process_race_condition_processes_simulator.c -o process_race_condition_processes_simulator -lpthread
*  usage: $./process_race_condition_processes_simulator
*/


#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int8_t *pCounter ;  // Global variable

void* increment(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
       (*pCounter)++;  // Potential race condition
    }
    return NULL;
}

void* decrement(void* arg) {
    int num_iterations = *(int *)arg;  // Number of iterations per thread
    for (int i= 0; i < num_iterations; i++) {
        (*pCounter)--;  // Potential race condition
    }
    return NULL;
}

int main() {
    int num_iterations = 100000;  // Number of iterations per thread
    std::cout << "two threads:"<<std::endl;
    std::cout<<"   one process increment: "<< num_iterations<<std::endl;
    std::cout<<"second process decrement: "<< num_iterations<<std::endl;
    std::cout << "the Correct counter value: 0 "<< std::endl;
    //create shared memory 
    key_t myKey = ftok("myfile" , 55);
    int shared_memory_id = shmget(myKey , 8 ,IPC_CREAT| 0666);
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
        return 0;
    }else{
        //parent process
        decrement((void *)&num_iterations);
        waitpid(cpid,NULL,0);
        printf("Final counter value: %d\n", *pCounter);
        shmdt(pCounter);
        shmctl(shared_memory_id , IPC_RMID , NULL);
        return 0;
    }

    return 0;
}
