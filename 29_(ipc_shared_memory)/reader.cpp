/*
*  Program gets the id of an existing shared memory region,
*  attach it to its adress space
*  read the data and display it on stdout
*  detach the memory segment and deletes it
*  usage: ./reader
*/

#include<iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/ipc.h>
#include <sys/shm.h>



using namespace std;

int main(){
    //genenrate key for shared_memory 
    auto mykey = ftok("./myfile" , 55);
    //return the id of  shared_memory with size 1024 and permission 0666 
    /*
    The first parameter specifies the unique number (called a key) identifying the shared segment. 
    The second parameter is the size of the shared segment e.g. 1024 bytes or 2048 bytes. 
    The third parameter specifies the permissions on the shared segment. 
    return : On success, the shmget() function returns a valid identifier while on failure it returns -1.
    */
    auto shared_memory_id =shmget(mykey , 1024 , IPC_CREAT | 0666);
    if(shared_memory_id == -1){
        cerr<<"shared_memory creation failed"<<endl;
        return 1;
    }
    /*attach shared_memory to this process(writer process) 
    -shmat function system call for  attach shared_memory to this process(writer process)  , 
    -(shared_memory_id) the id of the shared_memory it comes from shmget system call  
    -(nullptr) To choose the  kernel  select  the attached address of shared_memory at the address space of this process (writer process ) , 
    -The third parameter is ‘0’ if the second parameter is NULL, otherwise, the value is specified by SHM_RND.
    */
    char *  shared_memory_ptr = (char *)shmat(shared_memory_id , nullptr , 0);
    
    //read at the shared_memory 
    string output_string_from_shared_memory(100 , 0);
    strcpy(&output_string_from_shared_memory[0] , shared_memory_ptr);
    cout<< output_string_from_shared_memory<<endl;

    //deach this process from shared_memory
    //shmdt take one argument (the address of the shared_memory)
    shmdt(shared_memory_ptr);

    //destroy the shared memory 
    /*
    -first argument  for shared_memory_id
    -second argument  is IPC_RMID for delete the shared memory 
    -third argument  is kep as  NULL for delete the shared memory 
    */
    shmctl(shared_memory_id , IPC_RMID ,nullptr );

    return 0;
}