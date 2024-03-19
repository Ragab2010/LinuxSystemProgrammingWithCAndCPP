#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include<iostream>
using namespace std;
int main() {
    int fd1 , fd2;
    fd1 = open("dup_txtfile.txt" , O_RDONLY);
    if(fd1 == -1){
        return 1;
    }
    fd2 = dup(fd1);
    char a , b ;
    read(fd1 , &a , 1);
    cout<<a<<endl;
    read(fd2 , &b , 1);
    cout<<b<<endl;
    return 0;
}
