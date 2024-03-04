#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string>
#include<iostream>
using namespace std;
int main() {
    string word;
    getline(cin , word , '\n');
    cout<<word<<endl;
    auto fd1 = open("/etc/passwd" , O_RDONLY);
    if(fd1 == -1){
        return 1;
    }
    dup2(fd1 , 0);
    char buf[50];
    read(fd1 ,buf , 50 );
    cout<<buf<<endl;
    return 0;
}
