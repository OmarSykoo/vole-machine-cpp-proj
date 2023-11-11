//
// Created by Sykoo on 11/10/2023.
//

#ifndef VOL_MACHINE_MEMORY_H
#define VOL_MACHINE_MEMORY_H

class Memory {
private:
    bool in_use {} ;
    int value {} ;
public:
    Memory() : in_use(false) , value(0) {}
    int get_value();
    void set_value( int val );
};

#endif //VOL_MACHINE_MEMORY_H
