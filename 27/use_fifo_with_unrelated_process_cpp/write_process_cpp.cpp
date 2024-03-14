#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

int main() {
    mkfifo("myfifo1", 0666);

    int fd = open("myfifo1", O_WRONLY);
    if (fd == -1) {
        std::cerr << "Error: Failed to open FIFO for writing." << std::endl;
        return 1;
    }

    std::cout << "Writer process ready to send messages:" << std::endl;

    std::string message;
    while (std::getline(std::cin, message)) {
        write(fd, message.c_str(), message.size());
    }

    close(fd);

    return 0;
}
