/*
*  A program that simulate following shell command
*  cat f1.txt | wc -l
*/
#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
perform this command line :cat f1.txt | wc
*/
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
        if(dup2(fd[0] , STDIN_FILENO) == -1){
            perror("dup2 STDOUT faild");
            return 1;
        }
        close(fd[1]);
        execlp("wc" , "mywc" , nullptr);
        
    }else{
        //parent  process
        if(dup2(fd[1] , STDOUT_FILENO) == -1){
            perror("dup2 STDOUT faild");
            return 1;
        }
        close(fd[0]);
        execlp("cat" , "mycat" , "f1.txt" , nullptr);
    }
    return 0;
}