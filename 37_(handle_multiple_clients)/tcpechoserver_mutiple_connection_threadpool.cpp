
/*
*  tcpechoserver_mutiple_connection_threadpool.cpp: Server programs runs on ubuntu server
*  binds itself to ip localhost and port 54154, 
*  for each client create a thread from threadpool
*  receives a string from client
*  and will send it back to client
*  usage: ./tcpechoserver_mutiple_connection_threadpool
*/


#include <iostream>
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
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

#define BACKLOG 10
#define LOCAL_ADDR "127.0.0.1"
#define THREAD_POOL_SIZE 5 // Adjust as needed

using namespace std;

void tcp_echo_routine(int client_socket_fd);

class ThreadPool {
public:
    ThreadPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mutex);
                        condition.wait(lock, [this] { return !tasks.empty() || stop; });
                        if (stop && tasks.empty())
                            return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<class F>
    void enqueue(F&& task) {
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.emplace(forward<F>(task));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (auto& worker : workers) {
            worker.join();
        }
    }

private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool stop = false;
};

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
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
    int bind_status = bind(server_socket_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bind_status == -1) {
        cerr << "binding failed " << endl;
        return 3;
    }

    int listen_status = listen(server_socket_fd, BACKLOG);
    if (listen_status == -1) {
        cerr << "listen failed " << endl;
        return 4;
    }

    ThreadPool pool(THREAD_POOL_SIZE);

    while (1) {
        cout << "\nServer waiting for client connection..." << endl;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket_fd == -1) {
            cerr << "client_socket_fd creation failed " << endl;
            return 1;
        }

        pool.enqueue([client_socket_fd] { tcp_echo_routine(client_socket_fd); });
    }

    return 0;
}

void tcp_echo_routine(int client_socket_fd) {
    cout << "\n********* CLIENT CONNECTION ESTABLISHED ********" << endl;
    char buf[100];
    int return_value;
    while ((return_value = read(client_socket_fd, buf, 100)) > 0) {
        write(client_socket_fd, buf, return_value);
    }

    close(client_socket_fd);
    cout << "\n********* CLIENT CONNECTION TERMINATED ********" << endl;
}
