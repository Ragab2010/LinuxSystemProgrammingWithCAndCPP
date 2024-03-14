#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;

int main(){
    //  int mknod(const char *pathname, mode_t mode, dev_t dev);
    mknod("/tmp/pipe_for_teacher_sends" ,S_IFIFO |0666 , 0 );
    mkfifo("/tmp/pipe_for_teacher_receives" , 0666);

    auto fd_read = open("/tmp/pipe_for_teacher_sends" , O_RDONLY );
    auto fd_write = open("/tmp/pipe_for_teacher_receives" , O_WRONLY );

    //receive the string from student 
    string buff(100,0);
    read(fd_read , &buff[0] , buff.size());
    cout<<buff.c_str()<<endl;

    string msgFromStudent {"Okey Teacher , I going to do my homework"};
    //send the msgFromTeacher to student
    write(fd_write , msgFromStudent.c_str() , msgFromStudent.size()+1);

    close(fd_write);
    close(fd_read);
    //remove fifos now that we are done using them
    if(unlink("/tmp/pipe_for_teacher_sends") <0){
        perror("Client unlink pipe_for_teacher_sends");
        return 1;
    }
    if(unlink("/tmp/pipe_for_teacher_receives") <0){
        perror("Client unlink pipe_for_teacher_receives");
        return 1;
    }
    return 0;
}