#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

int main() {
    mkfifo("myfifo1", 0666);

    int fd = open("myfifo1", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error: Failed to open FIFO for reading." << std::endl;
        return 1;
    }

    std::cout << "Reader process ready to receive messages:" << std::endl;

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the received data
        std::cout << "Received: " << buffer << std::endl;
    }

    close(fd);

    return 0;
}
