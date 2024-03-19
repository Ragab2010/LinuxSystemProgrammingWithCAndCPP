/*
*  Program creates two named pipes, pipe_for_teacher_sends and pipe_for_teacher_receives
*  reads from pipe_for_teacher_receives and then writes to the pipe_for_teacher_sends
*  usage: ./teacher_process
*/

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
    //remove the old FIFO
    unlink("/tmp/pipe_for_teacher_sends");
    unlink("/tmp/pipe_for_teacher_receives");
    //create the new FIFO
    mknod("/tmp/pipe_for_teacher_sends" ,S_IFIFO |0666 , 0 );
    auto rv = mkfifo("/tmp/pipe_for_teacher_receives" , 0666);
    if(rv == -1){
        unlink("/tmp/pipe_for_teacher_sends");
        perror("mkfifo failed");
        return 1;
	}

    auto fd_write = open("/tmp/pipe_for_teacher_sends" , O_WRONLY );
    auto fd_read = open("/tmp/pipe_for_teacher_receives" , O_RDONLY );
    string msgFromTeacher {"message from teacher: Do your Homework , Okey"};
    //send the msgFromTeacher to student
    write(fd_write , msgFromTeacher.c_str() , msgFromTeacher.size()+1);
    //receive the string from student 
    //sleep(20);
    string buff(100,0);
    read(fd_read , &buff[0] , buff.size());
    cout<<buff.c_str()<<endl;

    close(fd_write);
    close(fd_read);
    return 0;
}