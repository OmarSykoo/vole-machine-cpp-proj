#ifndef VOL_MACHINE_MEMORY_H
#define VOL_MACHINE_MEMORY_H

class Memory {
private:
    int value {} ;
public:
    Memory() : value(0) {}
    int get_value();
    void set_value( int val );
    void clear() ;
};

#endif //VOL_MACHINE_MEMORY_H
