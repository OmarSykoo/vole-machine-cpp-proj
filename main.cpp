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
    Machine() ;
    ~Machine() ;
    void run() ;
    friend class Fetch_info ;
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

void Machine::run() {
    while ( step != -1 && ( step / 2 < data_.size() ) ) {
        pair<int,int> temp = data_[step / 2] ;
        step = instructions[ ( ( (temp.first & 0xF0)) >> 4 ) ]->process(registers , addresses, (temp.first & 0x0F) , temp.second , step );
    }
}

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
    Fetch_info F(vol) ;
    string text ; cin >> text ;
    F.fetch( text ) ;
    vol.run() ;
    return 0 ;
}
