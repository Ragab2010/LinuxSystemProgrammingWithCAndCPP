#include <iostream>
#include <sys/types.h>
#include <unistd.h>



using namespace std;


int main(){
    cout<<"my old PID="<<getpid()<<'\n';
    getchar();
    char * new_argv[] ={ nullptr};
    char * new_envp[] ={nullptr};

    if(int recPid =fork(); recPid == 0){
        cout<<"iam the child  , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
        int err= execve("/usr/bin/ls" ,new_argv , new_envp );
        if (err ==-1){
            cout<<"there is an erro at execve system call"<<'\n';
        }
    }else if (recPid >0){
        cout<<"iam the parent , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
    }else{
        cout<<"Fork failed"<<'\n';
    }
    return 0;
}