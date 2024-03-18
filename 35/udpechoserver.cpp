/*
*  udpchoclient_connected.cpp: Client program connects to the echo
*  service running on the ubuntuserver having ip 127.0.0.1
*  at port 7, sends a string and receives the same string
*  and display it on stdout
*  compile: gcc udpechoclient_connected.c -o udpechoclient_connected
*  usage: ./udpechoclient_connected <ip> 7
*/

#include<iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>




#define REMOTE_ADRR "127.0.0.1"

using namespace std;

int main(){
    
    //*** STEP-I:  Create UDP socket for the server
    int server_socket_fd = socket(AF_INET ,SOCK_DGRAM , 0 );
    if(server_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 2;
    }

    //*** STEP-II: Populate Socket's DS for remote IP and Port, and
    //***          then bind the server_sockfd with this address
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = htons(45154);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    // int ip_convert_stauts = inet_aton("127.0.0.1" , &server_addr.sin_addr);
    // if(ip_convert_stauts ==0){
    //     cerr<<"ip conversion from decimal to binary network failed "<<endl;
    //     return 3;
    // }
    memset(&(server_addr.sin_zero) , 0 , sizeof(server_addr.sin_zero));
    bind(server_socket_fd , (const struct sockaddr *) &server_addr , sizeof(server_addr));


    //*** STEP-III: Use recvfrom to receive msg from client and 
    //***           use sendto to send back same msg to client
    while(1){
        char buff[128] ={0};
        //receive string from  server socket  
        socklen_t server_addr_len = sizeof(server_addr);
        int n_socket = recvfrom(server_socket_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, &server_addr_len);
        if (n_socket == -1) {
            cerr << "recvfrom failed" << endl;
            return 4;
        }
        //send string from  buff to server socket again
        sendto(server_socket_fd, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, server_addr_len);
    }

    //*** STEP-IV:  Close server socket
    close(server_socket_fd);

    return 0;
}