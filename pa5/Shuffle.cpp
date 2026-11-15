/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA5
* Shuffle.cpp
* Client module for List ADT.
***/


#include<string>
#include"List.h"

using namespace std;


void shuffle(List& D);

void shuffle(List& D){
    List A;
    int midpoint = (D.length()) / 2;
    D.moveFront();
    for (int i=0; i<midpoint; i++){
        A.insertBefore(D.moveNext());
        D.eraseBefore();
    }
    A.moveFront();
    for (int i=0; i<A.length(); i++){
        D.moveNext();
        D.insertBefore(A.moveNext());
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        throw invalid_argument("Incorrect number of arguments. Usage: Shuffle <deck size>.");
    }
    int size = stoi(argv[1]);
    if (size <= 0){
        throw invalid_argument("Invalid argument - must be an positive integer.");
    }

    cout << "deck size\t\tshuffle count\n------------------------------" << endl;
    for (int i=1; i<=size; i++){
        List deck;
        for (int j=1; j<=i; j++){
            deck.insertBefore(j);
        }
        List copy = deck;
        int count = 0;
        while (true){
            shuffle(deck);
            count += 1;
            if (deck.equals(copy)){
                break;
            }
        }
        cout << i << "\t\t\t\t" << count << endl;
    }
    return 1;
}