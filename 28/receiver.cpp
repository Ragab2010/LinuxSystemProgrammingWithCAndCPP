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
    auto numberByte = msgrcv(qid ,(void *) &my_msg ,my_msg.mtype , 0  , IPC_NOWAIT);
    if(numberByte >0){
        cout<<my_msg.mtext<<endl;
    }else{
        cout<<"there is no massage at msg queue"<<endl;
    }

    return 0;
}