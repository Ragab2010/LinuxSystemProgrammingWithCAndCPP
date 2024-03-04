#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "file.txt";
    mode_t mode = S_IRWXU | S_IRWXG; // Set read, write, and execute permissions for the owner and the group
    int result = chmod(filename, mode);

    if (result == 0) {
        printf("Permissions of %s changed successfully.\n", filename);
    } else {
        perror("chmod");
        exit(EXIT_FAILURE);
    }

    return 0;
}
