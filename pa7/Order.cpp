/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA7
* Order.cpp
* Client module for Dictionary ADT.
***/


#include<iostream>
#include<fstream>
#include<string>

#include"Dictionary.h"

using namespace std;


int main(int argc, char* argv[]){
    // check command line for correct number of arguments.
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>." << endl;
        return(EXIT_FAILURE);
    }
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    
    // Check if the input file is readable
    if (!infile.is_open()) {
        std::cerr << "Could not open the file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // Check if the output file is writable
    if (!outfile.is_open()) {
        std::cerr << "Could not open the file " << argv[2] << std::endl;
        infile.close();
        return EXIT_FAILURE;
    }

    Dictionary D;
    std::string k = "";
    int v = 1;
    while (std::getline(infile, k)) {
        D.setValue(k, v);
        v += 1;
    }

    outfile << D.to_string() << std::endl;
    outfile << D.pre_string() << std::endl;
    D.clear();
    infile.close();
    outfile.close();

    return 1
}