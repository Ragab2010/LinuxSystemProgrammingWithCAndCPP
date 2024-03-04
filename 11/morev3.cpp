#include<iostream>
#include<fstream>
#include <string>
using namespace std;
#define PAGELEN 20
#define LINELEN 512

int get_input(){
    char c;
    std::cout << "\033[7m --more--(%%) \033[m";
    c=getchar();
    if (c == 'q')
        return 0;
    if (c == ' ')
        return 1;
    if (c == '\n')
        return 2;
    return 3;
}


void do_more(std::ifstream &file){
    string line{};
    int num_of_line=0;
    while(getline(file , line)){
        cout<<line<<'\n';
        num_of_line++;
        if (num_of_line == PAGELEN) {
            int rv = get_input();
            if (rv == 0) { // user pressed q
                cout<<"\033[1A \033[2K \033[1G";
                break;
            } else if (rv == 1) { // user pressed space bar
                cout<<"\033[1A \033[2K \033[1G";
                num_of_line -= PAGELEN;
            } else if (rv == 2) { // user pressed return/enter
                cout<<"\033[1A \033[2K \033[1G";
                --num_of_line; // show one more line
            } else if (rv == 3) { // invalid character
                cout<<"\033[1A \033[2K \033[1G";
                break;
            }
        }
    }
}

int main(int argc , char ** argv){
    if(argc ==1){
        std::cout << "This is the help page\n";
        return 0;
    }
    std::ifstream file;
    for(int i = 1 ; i< argc ; i++){
        file.open(argv[i]);
        if(!file.is_open()){
            std::cerr << "Can't open file: " << argv[i] << '\n';
            return 1;
        }
        do_more(file);

        file.close();   
    }
    return 0;
}