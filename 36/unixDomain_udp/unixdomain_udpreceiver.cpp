/*
*  unixdomain_udpreceiver.cpp: Creates a UNIX domain datagram socket
*  and then reads a string from this socket
*  written by the the sender program
*  and displays it on stdout
*  compile: gcc unixdomain_udpreceiver.c -o unixdomain_udpreceiver
*  usage: ./unixdomain_udpreceiver 
*/

#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>




using namespace std;

int main(){
    //STEP-0 *****Remove any old sockets and create  socket
    unlink("./socketfile");
    //*** STEP-I:  Create UNIX Domain UDP socket  fpr revciver
    int server_socket_fd = socket(AF_UNIX ,SOCK_DGRAM , 0 );
    if(server_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }

//STEP-II ****Populate socket's DS for the sockaddr_un type by giving the filename and then bind server_sockfd with this file

    struct sockaddr_un server_addr;
    server_addr.sun_family=AF_UNIX;
    strcpy(server_addr.sun_path, "./socketfile");

    int connect_status = bind(server_socket_fd , (const struct sockaddr *) &server_addr , sizeof(server_addr));
    if(connect_status == -1){
        cerr<<"connect creation failed "<<endl;
        return 2;
    }

    //*** STEP-III: Use recvfrom to receive msg from client
    char buff[128] ={0};
    socklen_t server_addr_len = sizeof(server_addr);
    int n_socket = recvfrom(server_socket_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, &server_addr_len);
    if (n_socket == -1) {
        cerr << "recvfrom failed" << endl;
        return 4;
    }
    cout<<"the Message is :"<<buff<<endl;

    //*** STEP-IV:  Close server socket
    close(server_socket_fd);

    return 0;
}