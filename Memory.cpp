//
// Created by Sykoo on 11/10/2023.
//

#include "Memory.h"

void Memory::set_value( int val ){
    in_use = true ;
    value = val ;
}

int Memory::get_value() {
    if ( in_use )
        return value ;
    throw std::invalid_argument("Garbage!M\n") ;
}
