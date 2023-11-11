//
// Created by Sykoo on 11/10/2023.
//
#ifndef VOL_MACHINE_INSTRUCTION_H
#define VOL_MACHINE_INSTRUCTION_H
#include "Register.h"
#include "Memory.h"


class instruction {
public:
    virtual int process( Register *R , Memory *M , int l , int r , int step );
    virtual ~instruction() { } ;
};

class _RXY1 : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step ) override ;
};

class _RXY2 : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step ) override ;
};

class _RXY3 : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step  ) override ;
};

class _0RS : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step ) override ;
};

class _RST : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step ) override ;
};

class _RXYB : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step ) override ;
};

class _000 : public instruction {
public:
    int process( Register *R , Memory *M , int l , int r , int step ) override ;
};


#endif //VOL_MACHINE_INSTRUCTION_H
