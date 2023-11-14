#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Memory.h"
#include "Memory.cpp"
#include "Register.h"
#include "Register.cpp"
#include "instruction.h"
#include "instruction.cpp"
using namespace std;

Machine::Machine() {
    instructions[0x1] = new _RXY1 ;
    instructions[0x2] = new _RXY2 ;
    instructions[0x3] = new _RXY3 ;
    instructions[0x4] = new _0RS  ;
    instructions[0x5] = new _RST  ;
    instructions[0xB] = new _RXYB ;
    instructions[0xC] = new _000  ;
}

Machine::~Machine() {
    for ( auto &i : instructions )
        delete i.second ;
    instructions.clear() ;
}

int main(){
    Machine vol ;
    bool logged_in = true ;
    while ( logged_in ){
        cout << "1) Load Data \n" ;
        cout << "2) Clear Memory \n" ;
        cout << "3) Run\n" ;
        cout << "4) Single step\n" ;
        cout << "5) list information\n" ;
        cout << "0) exit \n" ;
        char c ; cin >> c ;
        switch (c) {
            case '0' :
                logged_in = false ;
                break;
            case '1' :
                vol.fetch("input") ;
                cout << "Data_loaded\n" ;
                break;
            case '2' :
                vol.clear_memory() ;
                cout << "Cleared memory\n" ;
                break;
            case '3' :
                vol.run() ;
                cout << "Running..\n" ;
                break;
            case '4' :
                vol.single_step() ;
                cout << "Next_step...\n" ;
                break;
            case '5' :
                vol.print() ;
                cout << "printing_info...\n" ;
                break;
            default:
                cout << "INVALID INPUT\n" << '\n' ;
                cout << "Try Again\n" ;
                break;
        }
    }

    return 0 ;
}
