/*
*  Program creates a shared memory region,
*  gets a string from user and write that to 
*  the shared memory region
*  detach the shared memory and exits
*  usage: ./writer
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
    //create shared_memory with size 1024 and permission 0666 
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
    
    //write at the shared_memory 
    string input_string;
    cout<<"Enter the message that will write to shared memory:"<<endl;
    getline(cin ,input_string );
    std::copy(begin(input_string) , end(input_string) , shared_memory_ptr);
    // strcpy(shared_memory_ptr , input_string.c_str());

    //deach this process from shared_memory
    //shmdt take one argument (the address of the shared_memory)
    shmdt(shared_memory_ptr);

    return 0;
}