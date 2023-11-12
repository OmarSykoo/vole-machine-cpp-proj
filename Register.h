#ifndef VOL_MACHINE_REGISTER_H
#define VOL_MACHINE_REGISTER_H

class Register {
private:
    int value {} ;
public:
    Register() : value( 0 ) {}
    int get_value() const;
    void set_value( int val ) ;
    void clear() ;
};

#endif //VOL_MACHINE_REGISTER_H
