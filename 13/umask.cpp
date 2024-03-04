#include <sys/stat.h>
#include <fcntl.h>

int main() {
    //free to set (read , write , execute) in owner , group only 
    mode_t mask = umask(077); // Set the umask to 077 
    int fd = open("file.txt", O_CREAT | O_WRONLY, 0666); // Create a file with permissions 0666
    umask(mask); // Restore the previous umask
    return 0;
}
