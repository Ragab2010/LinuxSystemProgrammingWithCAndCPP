#include<iostream>
#include <unistd.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

int main(){
    int fd_parent_send[2];
    int fd_chiled_received[2];
    //create pipe
    auto rs_send = pipe(fd_parent_send);
    auto rs_received = pipe(fd_chiled_received);
    if(rs_send == -1 || rs_received == -1){
        cerr<<"pipe faild"<<endl;
        return 1;
    }
    auto pid = fork();
    if(pid == 0){
        //child process
        close(fd_chiled_received[1]);//close the write pipe at child recieved
        close(fd_parent_send[0]);   //close the read pipe at parent send 
        char buf[100];
        auto readByte = read(fd_chiled_received[0] , buf , 100);
        if(readByte == -1 || readByte == 0){
            cout<<"the number of recieved byte = "<<readByte<<endl;
        }
        cout<<buf<<endl;
        // cout<<"the child process recieved : "<<<<" byte"
        string msgFromChild {"the child process recieved : "s +to_string(readByte)+" Byte this is msg come from child process" };
        auto sendByte = write(fd_parent_send[1] , msgFromChild.c_str() , msgFromChild.size()+1);
        
    }else{
        //parent  process
        close(fd_chiled_received[0]);//close the read pipe at child recieved
        close(fd_parent_send[1]);   //close the write pipe at parent send 
        string msg{"this message come from parent process"};
        auto sendByte = write(fd_chiled_received[1] , msg.c_str() , msg.size()+1);
        char buf[100];
        auto readByte = read(fd_parent_send[0] , buf , 100);
        cout<<buf<<endl;
        // wait(nullptr);
        // cout<<"the parent send :"<<sendByte<<" byte"<<endl;
    }
    return 0;
}