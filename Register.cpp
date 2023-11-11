//
// Created by Sykoo on 11/10/2023.
//

#include "Register.h"
void Register::set_value(int val) {
    in_use = true ;
    this->value = val ;
}

int Register::get_value() {
    if ( in_use )
        return value ;
    throw std::invalid_argument("Garbage!R\n") ;
}
