#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



using namespace std;


int main(){
    cout<<"my old PID="<<getpid()<<'\n';
    getchar();
    while(1){
        string readProgram{};
        string ProgramName{};
        cout<<"ready to run program:>";
        getline(cin , ProgramName , '\n');
        if(ProgramName.length() == 0){
            continue;
        }
        if(int recPid =fork(); recPid == 0){
            //child process
            char * new_argv[] ={ nullptr};
            char * new_envp[] ={nullptr};
            int err= execve(ProgramName.c_str() ,new_argv , new_envp );
            if (err ==-1){
                cout<<"there is an erro at execve system call"<<'\n';
                return -1;
            }
            return 0;

        }else if (recPid >0){
            //parent process
            cout<<"iam the parent , my PID+="<<getpid()<<"while my PPID"<<getppid()<<'\n';
            int status; 
            wait(&status);
            cout<<"the status is :"<<status<<endl;
            cout<<"the exit status is :"<<WEXITSTATUS(status)<<endl;

        }else{
            cout<<"Fork failed"<<'\n';
        }
    }

    return 0;
}