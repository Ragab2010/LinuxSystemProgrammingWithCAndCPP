
/*
*  Program creates a named pipe, myfifo and
*  opens it in write mode and 
*  gets input from user and continuously writes in myfifo
*  usage: ./write_process
*/

#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>


using namespace std;

int main(){
    //  int mknod(const char *pathname, mode_t mode, dev_t dev);
    mknod("myfifo" ,S_IFIFO |0666 , 0 );
    cout<<"writer process ready to sends msgs:"<<endl;
    auto fd = open("myfifo" , O_WRONLY );
    while(cin){
        string buff;
        getline(cin , buff);
        write(fd , buff.c_str() , buff.size()+1);
    }
    close(fd);
    return 0;
}