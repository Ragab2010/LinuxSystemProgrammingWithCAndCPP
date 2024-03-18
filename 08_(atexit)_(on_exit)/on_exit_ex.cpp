#include<iostream>
#include <stdlib.h>

using namespace std;
void exit_handler(int status , void * arg){
    cout<<"Exit_handler with status: "<<status <<endl;
}

int main(){
    on_exit(exit_handler , nullptr);
    cout<<"Main is done\n";
    exit(55);
}