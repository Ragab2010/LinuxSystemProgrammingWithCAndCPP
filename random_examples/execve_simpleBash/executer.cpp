#include <iostream>
#include <sys/types.h>
#include <unistd.h>



using namespace std;

// extern int errno;

int main(int argc , char * argv[]){

    char * new_argv[] ={ nullptr};
    char * new_envp[] ={nullptr};

    execve(argv[1] ,new_argv , new_envp );
    // if (errno ==-1){
    //     cout<<"there is an erro at execve system call"<<'\n';
    // }

    return errno;
    // return 0;
}