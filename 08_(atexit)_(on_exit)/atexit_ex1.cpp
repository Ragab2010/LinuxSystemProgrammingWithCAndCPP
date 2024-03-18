#include<iostream>
#include <stdlib.h>

using namespace std;
void exit_handler(){
    cout<<"Exit_handler"<<endl;
}
int main(){
    atexit(exit_handler);
    cout<<"Main is done\n";
    return 0;
}