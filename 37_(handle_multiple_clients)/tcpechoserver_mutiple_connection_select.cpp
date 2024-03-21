
/*
*  tcpechoserver_mutiple_connection_select.c: Server programs runs on ubuntu server
*  binds itself to ip localhost and port 54154, 
*  waits for client connections
*  do a multiplexing on all descriptors
*  receives a string from client
*  and will send it back to client
*  usage: ./tcpechoserver_mutiple_connection_select
*/

#include<iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>

#define BACKLOG 10
#define LOCAL_ADDR "127.0.0.1"

using namespace std;

int tcp_echo_rotuine(int client_socket_fd );

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    //*** STEP-I:  Create passive socket for the server
    int server_socket_fd = socket(AF_INET ,SOCK_STREAM , 0 );
    if(server_socket_fd == -1) {
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }
    //*** STEP-II: Create a address structure containing server IP addr
    //***          and port, then bind the server_sockfd with this address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(54154);
    int ip_convert_status = inet_aton(LOCAL_ADDR , &server_addr.sin_addr);
    if(ip_convert_status == 0) {
        cerr<<"ip conversion from decimal to network failed "<<endl;
        return 2;
    }

    memset(&(server_addr.sin_zero) , 0 , sizeof(server_addr.sin_zero));
    int bind_status = bind(server_socket_fd , (const struct sockaddr *) &server_addr , sizeof(server_addr));
    if(bind_status == -1) {
        cerr<<"binding failed "<<endl;
        return 3;
    }

    //*** STEP-IV: Accept a connection, blocks until connection from client is established
    //****         will return a brand new descriptor for comm with this single connection
    int listen_status = listen(server_socket_fd , BACKLOG);
    if(listen_status == -1) {
        cerr<<"listen failed "<<endl;
        return 4;
    }
    //*** STEP-IV: Create descriptor set and use select to monitor the descriptors
    //***           and data 
    fd_set rfds; //data descriptor set
    fd_set afds;//master descriptor list that will contain every new accepted slave socket descriptor
    FD_ZERO(&rfds);//clear all entries from the set rfds
    FD_ZERO(&afds);//clear all entries from the set afds
    FD_SET(server_socket_fd, &afds);//add server sockfd to afds
    int fdmax = getdtablesize();
    while(1){
        memcpy(&rfds, &afds, sizeof(rfds));
    //use select to monitor and select those descriptors in rfds, that are ready
        select(fdmax, &rfds, NULL, NULL, NULL);
    //if server_sockfd  is ready accept the new connection
        if(FD_ISSET(server_socket_fd, &rfds)){ //returns true if server_sockfd is ready
            socklen_t client_addr_len = sizeof(client_addr);
            int client_socket_fd = accept(server_socket_fd , (struct sockaddr *) &client_addr , &client_addr_len);
            if(client_socket_fd == -1) {
                cerr<<"client_socket_fd creation failed "<<endl;
            return 1;
            }
            FD_SET(client_socket_fd, &afds);//for every accepted connection add fd to afds
        }
    //run a loop looking for data descriptor to be read by calling the tcpechod()
        int fd;
        for(fd = 0; fd < fdmax; fd++){
            if(fd != server_socket_fd && FD_ISSET(fd, &rfds))
            if(tcp_echo_rotuine(fd) == 0){
                close(fd);
                FD_CLR(fd, &afds);//remove fd from the set afds
            }
        }//end of for loop
    }//end of while loop

    return 0;
}

int tcp_echo_rotuine(int client_socket_fd ){
        //STEP-V ***** Read from client_socket_fd and write back
            char buf[100];
            int return_value;
            return_value = read(client_socket_fd , buf , 100);
            write(client_socket_fd , buf , return_value);
            return return_value;
}