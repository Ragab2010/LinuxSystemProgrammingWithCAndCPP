#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



using namespace std;


int main(){

    int recPid =fork();
    if( recPid == 0){
        //child process //orphan process
        cout<<"Iam the Orphan child  , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
        while(1);
        return 0;

    }else if (recPid >0){
        //parent process
        cout<<"Iam Terminating parent , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
        //the parent terminate before  read the return status of child process
        /*
        int status; 
        wait(&status);
        */
        exit(0); //== return 0;
    }else{
        cout<<"Fork failed"<<'\n';
    }

    return 0;
}