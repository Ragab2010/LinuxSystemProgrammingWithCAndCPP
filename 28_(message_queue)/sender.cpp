/*
*  Program creates a message queue,
*  sends two messages in that queue and terminate
*  usage: ./sender
*/

#include<iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>




using namespace std;
#define SIZE 512
struct msgBuf{
    long mtype;
    char mtext[SIZE];
};

int main(){
    //generate the key 
    key_t mykey = ftok("./myfile" , 55) ;
    //create the msg queue
    auto qid= msgget(mykey , IPC_CREAT | 0666 );
    if(qid == -1){
        perror("massage queue creation faild");
        return 1;
    }
    //create node for msg queue struct 
    struct msgBuf my_msg;
    my_msg.mtype=100;
    strcpy(my_msg.mtext , "this is the first time to use msg_queue\n");
    //send first msg to msg queue
    auto sendStatus = msgsnd(qid ,(void *) &my_msg ,my_msg.mtype , 0 );
//send the second msg to msg queue

    my_msg.mtype=200;
    strcpy(my_msg.mtext , "this is the second massage for msg_queue\n");
    //send first msg to msg queue
    sendStatus = msgsnd(qid ,(void *) &my_msg ,my_msg.mtype , 0 );
    return 0;
}