#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



using namespace std;


int main(){
    int pipefd[2];
    int myPipe = pipe(pipefd);
    if ( myPipe < 0){
        cerr<<"there an error at pipe creation "<<endl;
    }
    auto cpid = fork();
    switch(cpid){
        case -1:
        cerr<<"zeft"<<endl; 
        break; 
            
        case 0 :
            cout<<"chiled"<<endl;
            char buff[256];
            ::read(pipefd[0] , buff , 255);
            cout<<buff<<endl;
            break;
            
        default:
            sleep(3);
            cout<<"parent"<<endl;
            ::write(pipefd[1] , "msg_from_parent"s.data() ,  "msg_from_parent"s.size()+1);
            // std::this_thread::sleep_for(5ms);
            wait(nullptr);
            break;
    }
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}