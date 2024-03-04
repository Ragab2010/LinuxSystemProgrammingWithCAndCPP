#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define PAGELEN 20
#define LINELEN 512

void do_more( std::istream& , char* argv);
int get_input(double , std::istream&);
double update_percentage(int num_of_lines, int total_lines);
void forkToInvokeVim(char* argv);
void readFromCin(std::istream& input,  int tempFileFd);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        /*read from stdin*/
        // Generate a random file name for the temporary file
        char tempFileName[] = "/tmp/XXXXXX";
        int tempFileFd = mkstemp(tempFileName);
        if (tempFileFd == -1) {
            std::cerr << "Failed to create temporary file." << std::endl;
            exit(EXIT_FAILURE);
        }
        readFromCin(std::cin , tempFileFd);
        
        // Close the temporary file
        close(tempFileFd);
        std::fstream openFile(tempFileName);
        if(!openFile.is_open()){
            std::cerr << "Failed to open temporary file." << std::endl;
            exit(EXIT_FAILURE);
        }
        do_more(openFile ,tempFileName );
            // Remove the temporary file
        remove(tempFileName);
    } else {
        /*read from argv[]*/
        for (int i = 1; i < argc; ++i) {
            std::ifstream file(argv[i]);
            if (!file.is_open()) {
                std::cerr << "Can't open file: " << argv[i] << std::endl;
                continue;
            }
            do_more(file , argv[i]);
            file.close();
        }
    }
    return 0;
}

void do_more(std::istream& file ,char* arg ) {
    std::string line;
    int num_of_lines = 0;
    int total_lines = 0;
    std::ifstream tty_file("/dev//tty");
    while (std::getline(file, line)) {
        total_lines++;
        std::cout << line << std::endl;
        num_of_lines++;
        double  pre = update_percentage(num_of_lines, total_lines);
        if (num_of_lines == PAGELEN) {
            int rv = get_input( pre , tty_file);
            if (rv == 0) { // user pressed q
                std::cout<<"\033[1A \033[2K \033[1G";
                break;
            } else if (rv == 1) { // user pressed space bar
                std::cout<<"\033[1A \033[2K \033[1G";
                num_of_lines -= PAGELEN;
            } else if (rv == 2) { // user pressed return/enter
                std::cout<<"\033[1A \033[2K \033[1G";
                --num_of_lines; // show one more line
            } else if (rv == 3) { // invalid character
                std::cout<<"\033[1A \033[2K \033[1G";
                forkToInvokeVim(arg);
                break;
            } else if (rv == 4) { // invalid character
                std::cout<<"\033[1A \033[2K \033[1G";
                //break;
            }
            // double percentage = ((double)num_of_lines / total_lines) * 100;
            // std::cout << "\033[7m --more--(" << std::fixed << std::setprecision(2) << percentage << "%) \033[m";
        }

    }
}

double update_percentage(int num_of_lines, int total_lines) {
    // double percentage = ((double)num_of_lines / total_lines) * 100;
    return  (((double)num_of_lines / total_lines) * 100) -100;
    //std::cout << "\033[7m --more--(" << std::fixed << std::setprecision(2) << percentage << "%) \033[m";
}

int get_input(double pre ,  std::istream& tty_file) {
    int c;
    std::cout << "\033[7m --more--(%"<< std::fixed << std::setprecision(2) << pre << "%) \033[m";
    //c  = getchar();
    // c=std::cin.get();
    c = tty_file.get();
    if (c == 'q')
        return 0;
    if (c == ' ')
        return 1;
    if (c == '\n')
        return 2;
    if (c == 'v')
        return 3;
    return 4;
}
void forkToInvokeVim(char* argv){
    auto id = fork();
    if(id == 0){
        //child
        char *const cmd[] = {"vim", argv, NULL};
        auto return_value=  execvp(cmd[0], cmd);
        if(return_value == -1){
            ::exit(1);
        }
    }else if (id >0){
        //parent
        ::wait(nullptr);
        ::exit(0);

    }else{
        std::cout<<"failed to invoke Vim"<<'\n';
    }
}

void readFromCin(std::istream& input,  int tempFileFd){

    // Read from stdin and write to the temporary file
    std::string buffer;
    while (std::getline(input ,  buffer)) {
        buffer += '\n'; // Add newline character
        ssize_t bytesWritten = write(tempFileFd, buffer.c_str(), buffer.size()+1);
        if (bytesWritten == -1) {
            std::cerr << "Failed to write to temporary file." << std::endl;
            close(tempFileFd);
            exit(EXIT_FAILURE);
        }
    }
    // fork vim with the temp file
    // forkToInvokeVim(tempFileName);

}