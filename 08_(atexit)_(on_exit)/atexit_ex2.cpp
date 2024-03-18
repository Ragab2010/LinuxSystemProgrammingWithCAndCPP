#include<iostream>
#include <stdlib.h>

using namespace std;
void exit_handler1(){
    cout<<"Exit_handler1"<<endl;
}
void exit_handler2(){
    cout<<"Exit_handler2"<<endl;
}
void exit_handler3(){
    cout<<"Exit_handler3"<<endl;
}
int main(){
    atexit(exit_handler1);
    atexit(exit_handler2);
    atexit(exit_handler3);
    cout<<"Main is done\n";
    exit(0);
}