#include "Register.h"

void Register::set_value(int val) {
    this->value = val ;
}

int Register::get_value() const {
    return value ;
}

void Register::clear() {
    value = false ;
}
