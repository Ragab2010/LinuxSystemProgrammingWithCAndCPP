#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void forkToInvokeVim(char *tempFileName) {
    auto id = fork();
    if (id == 0) {
        // Child
        char *const cmd[] = {"vim", tempFileName, NULL};
        auto return_value = execvp(cmd[0], cmd);
        if (return_value == -1) {
            ::exit(1);
        }
    } else if (id > 0) {
        // Parent
        ::wait(nullptr);
        // ::exit(0);
    } else {
        std::cout << "failed to invoke Vim" << '\n';
    }
}
// void forkToInvokeVim(char *tempFileName, int tempFileFd) {
//     auto id = fork();
//     if (id == 0) {
//         // Child
//         // Close the file descriptor before invoking vim
//         close(tempFileFd);
//         char *const cmd[] = {"vim", tempFileName, NULL};
//         auto return_value = execvp(cmd[0], cmd);
//         if (return_value == -1) {
//             ::exit(1);
//         }
//     } else if (id > 0) {
//         // Parent
//         int status;
//         waitpid(id, &status, 0);
//         if (WIFEXITED(status)) {
//             // Vim exited normally
//             int exit_status = WEXITSTATUS(status);
//             if (exit_status == 0) {
//                 cout << "Vim exited normally." << endl;
//             } else {
//                 cout << "Vim exited with error code " << exit_status << endl;
//             }
//         } else {
//             // Vim exited abnormally
//             cout << "Vim exited abnormally." << endl;
//         }
//     } else {
//         std::cout << "failed to invoke Vim" << '\n';
//     }
// }

int main() {
    // Generate a random file name for the temporary file
    char tempFileName[] = "/tmp/XXXXXX";
    int tempFileFd = mkstemp(tempFileName);
    if (tempFileFd == -1) {
        cerr << "Failed to create temporary file." << endl;
        exit(EXIT_FAILURE);
    }

    // Read from stdin and write to the temporary file
    string buffer;
    while (getline(cin, buffer)) {
        buffer += '\n'; // Add newline character
        ssize_t bytesWritten = write(tempFileFd, buffer.c_str(), buffer.size());
        if (bytesWritten == -1) {
            cerr << "Failed to write to temporary file." << endl;
            close(tempFileFd);
            exit(EXIT_FAILURE);
        }
    }

    // Close the temporary file
    close(tempFileFd);

    // fork vim with the temp file
    forkToInvokeVim(tempFileName);

    // Remove the temporary file
    remove(tempFileName);

    return 0;
}
