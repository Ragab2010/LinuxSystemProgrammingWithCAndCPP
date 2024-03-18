#include<iostream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


int main(void){
    char * path = getenv("PATH");
    char * shell = getenv("SHELL");
    if(path){
        cout<<"$PATH="<<path<<endl;
    }
    if(shell){
        cout<<"$shell="<<shell<<endl;
    }
    return 0;
}