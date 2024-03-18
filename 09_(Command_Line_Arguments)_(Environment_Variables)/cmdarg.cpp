#include<iostream>
#include <stdlib.h>

using namespace std;

int main(int argc , char **argv){
    string nameOfProgram(argv[0]);
    if(nameOfProgram == "./hello"s){
        cout<<"I'm called by the name hello\n";
    }else {
        cout<<"I'm called by the name cmdarg\n";
    }
    return 0;
}