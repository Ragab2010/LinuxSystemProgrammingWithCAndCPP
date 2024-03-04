#include <iostream>
#include <fstream>

using namespace std;
int main(){

    ofstream file("txtfile.txt");
    if(!file.is_open()){
        // cerr<<"the file dosn't exist"<<endl;
        return 1;
    }
    file<<"Welcome In Egypt\n";
    file.close();
    cout<<"the operation completed ..";

    return 0;
}