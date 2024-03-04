#include<iostream>
#include<fstream>

int main(void){


    if (auto file = std::fstream("test.txt")) {
        int answer;
        file >> answer;
        std::cout << "The answer is: " << answer << '\n';
    }

    return 0;
}