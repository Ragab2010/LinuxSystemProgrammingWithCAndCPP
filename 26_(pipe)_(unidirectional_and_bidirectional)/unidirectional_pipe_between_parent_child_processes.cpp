/*
*  Use of pipe between two related processes
*  child is a reader process while parent is a writer process
*/

#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

int main(){
    int fd[2];
    //create pipe
    auto rs = pipe(fd);
    if(rs == -1){
        cerr<<"pipe faild"<<endl;
        return 1;
    }
    auto pid = fork();
    if(pid == 0){
        //child process
        char buf[100];
        auto readByte = read(fd[0] , buf , 100);
        if(readByte == -1 || readByte == 0){
            cout<<"the number of recieved byte = "<<readByte<<endl;
        }
        cout<<buf<<endl;
        
    }else{
        string msg{"this message come from parent process"};
        auto sendByte = write(fd[1] , msg.c_str() , msg.size()+1);
        wait(nullptr);
        cout<<"the parent send :"<<sendByte<<" byte"<<endl;
    }
    return 0;
}