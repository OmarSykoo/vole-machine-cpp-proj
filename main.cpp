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

vector<instruction> all_instructions ;

class Machine {
private :
    Register registers[16] ;
    Memory addresses[256] ;
    vector<pair<int,int>> data_ ;
    map< int , instruction* > instructions ;
    int step {0} ;
public:
    Machine()  ;
    ~Machine() ;
    void run(){
        while ( step != -1 && ( step / 2 < data_.size() ) ) {
            pair<int,int> temp = data_[ step / 2] ;
            step = instructions[ ( ( (temp.first & 0xF0)) >> 4 ) ]->process(registers , addresses, (temp.first & 0x0F) , temp.second , step );
        }
    }
    void single_step(){
        pair<int,int> temp = data_[step / 2] ;
        step = instructions[ ( ( (temp.first & 0xF0)) >> 4 ) ]->process( registers , addresses, (temp.first & 0x0F) , temp.second , step );
    }
    friend class Run_mach ;
    void fetch( const string& text ){
        ifstream fin(text + ".txt" ) ;
        if ( fin.fail() ){
            throw invalid_argument("can't open file \n") ;
        }
        int R , XY ;
        while ( fin >> hex >> R >> XY ) {
            data_.emplace_back( R , XY ) ;
        }
    }
    void clear_memory() {
        for ( auto& i : registers){
            i.clear() ;
        }
        for ( auto& i : addresses ) {
            i.clear() ;
        }
        step = 0 ;
    }
    void print(){
        cout << "N R 0 1 2 3 4 5 6 7 8 9 A B C D E F\n" ;
        for ( int i = 0 ; i < 16 ; i++ ){
            cout << hex << i << ' ' ;
            cout << hex << registers[i].get_value() << ' ' ;
            for ( int j = 0 ; j < 16 ; j++ ){
                cout << hex << addresses[ ( j << 4 ) + i ].get_value() << ' ' ;
            }
            cout << '\n' ;
        }
    }
};

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
