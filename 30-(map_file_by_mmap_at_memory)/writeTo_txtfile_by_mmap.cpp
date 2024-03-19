/*
*  Program mmaps an entire file in its address space
*  and then write some more txt in that memory mapped region
*  usage: ./writeTo_txtfile_by_mmap
*/
#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring>




using namespace std;

int main(){
    //open f1.txt
    auto fd = open("./f2.txt" , O_RDWR | O_CREAT);
    if(fd == -1){
        cerr<<"there is an problem  with opening txt file "<<endl;
        return 1; 
    }

    //stretch the file size to 100 byte to can map it at memory 
    int file_size = lseek(fd ,100, SEEK_END);
    write(fd, "", 1);
    //memory map the file content
    /*
    The first parameter (nullptr) To choose the  kernel  select  the  address of memory map at the address space of this process 
    
    */
    char * file_ptr =(char *) mmap(nullptr , file_size , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0);
    if(file_ptr == nullptr){
        cerr<<"mmap creation failed"<<endl;
        return 1;
    }

    string input_string;
    cout<<"write the date that past to txt file:"<<endl;
    getline(cin , input_string);
    // copy(input_string.begin() , input_string.end() , file_ptr);
    strcpy(file_ptr , input_string.c_str());

    //sync it 
    msync(file_ptr , file_size , MS_SYNC);
    //Need to free the mapped memory 
    munmap(file_ptr, file_size);
    //munmap does not close the file discriptor, so we need to do that
    close(fd);

    return 0;
}