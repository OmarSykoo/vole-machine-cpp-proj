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
    friend class Fetch_info ;
    friend class Run_mach ;
    friend class Clear ;
    friend class print_info ;
};

class print_info {
private:
    Machine *a ;
public:
    print_info( Machine &pass ) : a(&pass) {}
    void print(){
        cout << "N R 0 1 2 3 4 5 6 7 8 9 A B C D E F\n" ;
        for ( int i = 0 ; i < 16 ; i++ ){
            cout << hex << i << ' ' ;
            cout << hex << a->registers[i].get_value() << ' ' ;
            for ( int j = 0 ; j < 16 ; j++ ){
                cout << hex << a->addresses[ ( j << 4 ) + i ].get_value() << ' ' ;
            }
            cout << '\n' ;
        }
    }
};

class Clear {
private:
    Machine *a ;
public:
    Clear( Machine &pass ) : a(&pass) {}
    void clear_memory() {
        for ( auto& i : a->registers){
            i.clear() ;
        }
        for ( auto& i : a->addresses ) {
            i.clear() ;
        }
        a->step = 0 ;
    }
};

class Fetch_info {
private:
    Machine *a ;
public:
    Fetch_info( Machine &pass ) : a(&pass) {}
    void fetch( const string& text ){
        ifstream fin(text + ".txt" ) ;
        if ( fin.fail() ){
            throw invalid_argument("can't opent file \n") ;
        }
        int R , XY ;
        while ( fin >> hex >> R >> XY ) {
            a->data_.emplace_back( R , XY ) ;
        }
    }
};

class Run_mach {
private:
    Machine *a ;
public:
    Run_mach( Machine &pass ) : a( &pass ) {}
    void run(){
        while ( a->step != -1 && ( a->step / 2 < a->data_.size() ) ) {
            pair<int,int> temp = a->data_[a->step / 2] ;
            a->step = a->instructions[ ( ( (temp.first & 0xF0)) >> 4 ) ]->process(a->registers , a->addresses, (temp.first & 0x0F) , temp.second , a->step );
        }
    }
    void single_step(){
        pair<int,int> temp = a->data_[a->step / 2] ;
        a->step = a->instructions[ ( ( (temp.first & 0xF0)) >> 4 ) ]->process(a->registers , a->addresses, (temp.first & 0x0F) , temp.second , a->step );
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
    Run_mach Run_machine( vol ) ;
    print_info print_memory(vol) ;
    Fetch_info Fetch_(vol) ;
    Clear clear_memory( vol ) ;
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
                Fetch_.fetch("input") ;
                cout << "Data_loaded\n" ;
                break;
            case '2' :
                clear_memory.clear_memory() ;
                cout << "Cleared memory\n" ;
                break;
            case '3' :
                Run_machine.run() ;
                cout << "Running..\n" ;
                break;
            case '4' :
                Run_machine.single_step() ;
                cout << "Next_step...\n" ;
                break;
            case '5' :
                print_memory.print() ;
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
