//
// Created by Sykoo on 11/10/2023.
//

#include "instruction.h"

int _RXY1::process( Register *R , Memory *M, int l, int r , int step ){
    R[l].set_value(M[r].get_value()) ;
    return step + 2 ;
}

int _RXY2::process( Register *R , Memory *M, int l, int r , int step ) {
    R[l].set_value(r) ;
    return step + 2 ;
}

int _RXY3::process( Register *R , Memory *M, int l, int r , int step ) {
    if ( r == 0 ) {
        std::cout << R[l].get_value() << ' ' ;
        std::cout << (char)R[l].get_value() << '\n' ;
    }
    M[r].set_value(R[l].get_value()) ;
    return step + 2 ;
}

int _0RS::process( Register *R , Memory *M, int l, int r , int step) {
    int left_bit = r & 0xF0 , right_bit = r & 0x0F ;
    R[right_bit].set_value(R[ left_bit >> 4 ].get_value() ) ;
    return step + 2 ;
}

int _RST::process( Register *R , Memory *M, int l, int r , int step ) {
    int left_bit = r & 0xF0 , right_bit = r & 0x0F ;
    R[l].set_value( (R[(left_bit >> 4)].get_value() + R[right_bit].get_value()) & 0xFF ) ;
    return step + 2 ;
}

int _RXYB::process( Register *R , Memory *M, int l, int r , int step ) {
    if ( R[0].get_value() == R[l].get_value() ) {
        return r ;
    }
    return step + 2 ;
}

int _000::process( Register *R , Memory *M, int l, int r, int step) {
    return -1 ;
}
