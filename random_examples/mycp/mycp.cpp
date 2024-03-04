#include <iostream>
#include <fstream>

using namespace std;
int main(int argc , char **argv){
    
    if(argc < 3){
        cerr<<"there an mistake at input files!"<<endl;
        return 1;
    }
    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cerr<<"there is no file exist by this name :"<<argv[1]<<endl;
        return 1;
    }
    ofstream outputFile(argv[2]);
    
    //copy the contents
    outputFile<<inputFile.rdbuf();

    outputFile.close();
    inputFile.close();
    //cout<<"the operation completed ..";

    return 0;
}