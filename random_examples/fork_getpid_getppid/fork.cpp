#include <iostream>
#include <sys/types.h>
#include <unistd.h>



using namespace std;


int main(){
    cout<<"my old PID="<<getpid()<<'\n';
    getchar();

    if(int recPid =fork(); recPid == 0){
        cout<<"iam the child  , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
    }else if (recPid >0){
        cout<<"iam the parent , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
    }else{
        cout<<"Fork failed"<<'\n';
    }
    return 0;
}