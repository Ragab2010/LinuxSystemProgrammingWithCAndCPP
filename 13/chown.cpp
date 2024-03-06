#include <unistd.h>
#include <stdio.h>

int main() {
    //change the owner and group by uid 
    if (chown("chowntxtfile.txt", -1, 137) == -1) {
        perror("chown");
        return 1;
    }
    printf("Ownership of /path/to/file changed successfully.\n");
    return 0;
}
