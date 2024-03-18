#include<iostream>
#include <unistd.h>
using namespace std;

extern char **environ; 

int main(void){
    for(int i = 0 ; environ[i] !=nullptr ; i++){
        cout<<"environ["<<i<<"]="<<environ[i]<<'\n';
    }
    return 0;
}