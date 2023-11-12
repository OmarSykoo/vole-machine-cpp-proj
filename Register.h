//
// Created by Sykoo on 11/10/2023.
//

#ifndef VOL_MACHINE_REGISTER_H
#define VOL_MACHINE_REGISTER_H

class Register {
private:
    bool in_use {} ;
    int value {} ;
public:
    Register() : in_use( false ) , value( 0 ) {}
    int get_value() const;
    void set_value( int val ) ;
};

#endif //VOL_MACHINE_REGISTER_H

