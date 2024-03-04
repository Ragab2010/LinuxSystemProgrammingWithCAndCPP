#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



using namespace std;


int main(){
    auto cpid = fork();
    switch(cpid){
        case -1:
        cerr<<"zeft"<<endl; 
        break; 
            
        case 0 :
            cout<<"chiled"<<endl;
            break;
            
        default:
            // std::this_thread::sleep_for(5ms);
            sleep(3);
            cout<<"parent"<<endl;
            wait(nullptr);
            break;
    }
    return 0;
}