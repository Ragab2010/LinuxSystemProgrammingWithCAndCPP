#include <iostream>
#include <fstream>
#include <string>

#define PAGELEN 20
#define LINELEN 512

void do_more(std::istream&);
int get_input(std::istream&);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        do_more(std::cin);
    } else {
        for (int i = 1; i < argc; ++i) {
            std::ifstream file(argv[i]);
            if (!file.is_open()) {
                std::cerr << "Can't open file: " << argv[i] << std::endl;
                continue;
            }
            do_more(file);
            file.close();
        }
    }
    return 0;
}

void do_more(std::istream& file) {
    std::string line;
    int num_of_lines = 0;
    std::ifstream tty_file("/dev//tty");
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        num_of_lines++;
        if (num_of_lines == PAGELEN) {
            int rv = get_input(tty_file);
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
                break;
            }
        }
    }
}

int get_input(std::istream& tty_file) {
    int c;
    std::cout << "\033[7m --more--(%%) \033[m";
    //c  = getchar();
    // c=std::cin.get();
    c = tty_file.get();
    if (c == 'q')
        return 0;
    if (c == ' ')
        return 1;
    if (c == '\n')
        return 2;
    return 3;
}
