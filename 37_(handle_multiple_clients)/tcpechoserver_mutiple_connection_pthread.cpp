/*
*  tcpechoserver_mutiple_connection_pthread.cpp: Server programs runs on ubuntu server
*  binds itself to ip localhost and port 54154, 
*  waits for client connections
*  for each client create a thread
*  receives a string from client
*  and will send it back to client
*  usage: ./tcpechoserver_mutiple_connection_fork
*/
#include<iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define BACKLOG 10
#define LOCAL_ADDR "127.0.0.1"

using namespace std;

void *tcp_echo_routine(void *);

int main() {
    struct sockaddr_in server_addr, client_addr;
    int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd == -1) {
        cerr << "server_socket_fd creation failed " << endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(54154);
    int ip_convert_status = inet_aton(LOCAL_ADDR, &server_addr.sin_addr);
    if (ip_convert_status == 0) {
        cerr << "ip conversion from decimal to network failed " << endl;
        return 2;
    }

    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
    int bind_status = bind(server_socket_fd, (const struct sockaddr *) &server_addr, sizeof(server_addr));
    if (bind_status == -1) {
        cerr << "binding failed " << endl;
        return 3;
    }

    int listen_status = listen(server_socket_fd, BACKLOG);
    if (listen_status == -1) {
        cerr << "listen failed " << endl;
        return 4;
    }

    while (1) {
        cout << "\nServer waiting for client connection..." << endl;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket_fd = accept(server_socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_socket_fd == -1) {
            cerr << "client_socket_fd creation failed " << endl;
            return 1;
        }

        pthread_t ti_client;
        if (pthread_create(&ti_client, nullptr, tcp_echo_routine, (void *) &client_socket_fd) != 0) {
            cerr << "Failed to create thread" << endl;
            close(client_socket_fd); // Close the client socket if thread creation fails
        } else {
            pthread_detach(ti_client);
        }
    }

    close(server_socket_fd); // Close the server socket before exiting
    return 0;
}

void *tcp_echo_routine(void *arg_client_socket_fd) {
    int client_socket_fd = *((int *) arg_client_socket_fd);
    cout << "\n********* CLIENT CONNECTION ESTABLISHED ********" << endl;

    char buf[100];
    int return_value;
    while ((return_value = read(client_socket_fd, buf, 100)) > 0) {
        write(client_socket_fd, buf, return_value);
    }

    close(client_socket_fd);
    cout << "\n********* CLIENT CONNECTION TERMINATED ********" << endl;
    pthread_exit(nullptr);
}
