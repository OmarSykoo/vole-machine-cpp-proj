#include "Memory.h"

void Memory::set_value( int val ){
    value = val ;
}

int Memory::get_value() {
    return value;
}

void Memory::clear() {
    value = false ;
}

