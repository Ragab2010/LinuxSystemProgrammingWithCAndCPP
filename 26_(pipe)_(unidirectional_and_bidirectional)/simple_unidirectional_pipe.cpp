/*
*  A hello world program on pipe
*  shows the usage of a pipe withing a single process
*/
#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>


using namespace std;

int main(){
    int fd[2]; 
    //pipe
    auto rv = pipe(fd);
    if(rv == -1){
        cerr<<"pipe failed"<<endl;
        return 1;
    }
    string msgString{"Hello , world! (Using pipe)"};
    cout<<"here we going to write for pipe string :"<<msgString<<endl;
    ssize_t write(int fd, const void *buf, size_t count);
    //write to pipe
    auto chWrite = write(fd[1] , msgString.c_str() , msgString.size()+1);

    cout<<"here we going to read for pipe:"<<endl;
    //read from pipe
    string recievedMsg(50 , 0);
    auto chRead = read(fd[0] ,&recievedMsg[0] , recievedMsg.size() );
    //display the data on stdout
    recievedMsg.shrink_to_fit();
    cout<<recievedMsg<<endl;
    //write(1 , recievedMsg.c_str() , recievedMsg.size());
    while(1);
    return 0;
}