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
    auto fd = open("myfifo" , O_RDONLY );
    cout<<"read process ready to receives  msg:"<<endl;
    string buff(100, 0);
    while(ssize_t bytes_read = read(fd, &buff[0], buff.size()) >0) {

        cout << buff.c_str() << endl;
        buff[0]='\0';
    };
    close(fd);
    return 0;
}