#include <iostream>
#include <vector>
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
    vector<instruction*> instructions ;
    int step {0} ;
public:
    Machine() ;
    ~Machine() ;
    void fetch( const string& text ) ;
    void run() ;
};

void Machine::fetch( const string& text ) {
    ifstream fin(text + ".txt" ) ;
    if ( fin.fail() ){
        throw invalid_argument("can't opent file \n") ;
    }
    int R , XY ;
    while ( fin >> hex >> R >> XY ) {
        data_.emplace_back( R , XY ) ;
    }
}

void Machine::run() {
    while ( step != -1 && ( step / 2 < data_.size() ) ) {
        pair<int,int> temp = data_[step / 2];
        step = instructions[ ( ( (temp.first & 0xF0)) >> 4 ) - 1 ]->process(registers , addresses, (temp.first & 0x0F) , temp.second , step );
    }
}

Machine::Machine() {
    instructions.resize( 8) ;
    instructions[0] = new _RXY1 ;
    instructions[1] = new _RXY2 ;
    instructions[2] = new _RXY3 ;
    instructions[3] = new _0RS  ;
    instructions[4] = new _RST  ;
    instructions[5] = new _RXY1 ;
    instructions[6] = new _RXYB ;
    instructions[7] = new _000  ;
}

Machine::~Machine() {
    for ( int i = 0 ; i < 8 ; i++ )
        delete instructions[i] ;
    instructions.clear() ;
}

int main(){
    Machine vol ;
    string text ; cin >> text ;
    vol.fetch(text) ;
    vol.run() ;
}