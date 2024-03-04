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
        //child process //zombie process
        cout<<"Iam the Orphan child  , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
        exit(0); //==return 0;
        //the child process terminate normally but the parent doesn't  read the return status (0)

    }else if (recPid >0){
        //parent process
        cout<<"Iam Running parent , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
        //the parent still running but it doesn't  read the return status of child process
        /*
        int status; 
        wait(&status);
        */
        while(1);
    }else{
        cout<<"Fork failed"<<'\n';
    }

    return 0;
}