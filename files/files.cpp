#include<iostream>
#include<fstream>

int main(void){
    constexpr auto mode  =   std::ios::in | std::ios::out | std::ios::trunc;
    if (auto file = std::fstream("test.txt", mode)) {
        // if (auto file = std::ofstream("test.txt" , mode)) {
        //file<<"Welcome\n";
        std::cout << "success\n";
    }


    return 0;
}