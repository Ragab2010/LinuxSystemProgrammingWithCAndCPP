/*
*  tcpechoserver.cpp: Server programs runs on ubuntu server
*  binds itself to ip localhost and port 54154, 
*  waits for client connections
*  receives a string from client
*  and will send it back to client
*  compile: g++ tcpechoserver.c -o tcpechoserver
*  usage: ./tcpechoserver
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



//how many pending connections queue  will hold
#define BACKLOG 10 //the size of the pending queue for pending connections
#define LOCAL_ADRR "127.0.0.1"

using namespace std;

int main(){

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    //*** STEP-I:  Create passive socket for the server
    int server_socket_fd = socket(AF_INET ,SOCK_STREAM , 0 );
    if(server_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }

    //*** STEP-II: Create a address structure containing server IP addr
    //***          and port, then bind the server_sockfd with this address
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = htons(54154);
    int ip_convert_stauts = inet_aton(LOCAL_ADRR , &server_addr.sin_addr);
    if(ip_convert_stauts ==0){
        cerr<<"ip conversion from decimal to network failed "<<endl;
        return 2;
    }
    memset(&(server_addr.sin_zero) , 0 , sizeof(server_addr.sin_zero));
    int bind_status = bind(server_socket_fd , (const struct sockaddr *) &server_addr , sizeof(server_addr));
    if(ip_convert_stauts == -1){
        cerr<<"binding failed "<<endl;
        return 3;
    }

    //*** STEP-IV: Accept a connection, blocks until connection from client is established
    //****         will return a brand new descriptor for comm with this single connection
    int listen_stauts = listen(server_socket_fd , BACKLOG);
    if(listen_stauts ==-1){
        cerr<<"listen failed "<<endl;
        return 4;
    }
    while(1){
        cout<<"\nServer waiting for client connection..."<<endl;
        //*** STEP-IV: Accept a connection, blocks until connection from client is established
        //****         will return a brand new descriptor for comm with this single connection
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sockt_fd = accept(server_socket_fd , (struct sockaddr *) &client_addr , &client_addr_len);
        if(client_sockt_fd == -1){
            cerr<<"client_sockt_fd creation failed "<<endl;
            return 1;
        }
        cout<<"\n********* CLIENT CONNECTION ESTABLISHED ********"<<endl;
        //STEP-V ***** Read from sockfd and write back
        char buf[100];
        int return_value;
        while(return_value = read(client_sockt_fd , buf , 100)){
            write(client_sockt_fd , buf , return_value);
        }
        //STEP-VI ***** close client_sockt_fd when client send nothing or close()
        close(client_sockt_fd);
        cout<<"\n********* CLIENT CONNECTION TERMINATED ********"<<endl;

    }



    return 0;
}