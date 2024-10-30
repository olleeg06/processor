#ifndef SPU_FUNCTION
#define SPU_FUNCTION
#include <stdio.h> 
#include "stack_function.h"

struct processor {
    stack_elem_t *code;
    size_t ip;
    stack_t stk;
    int registers[16];
};

struct metky {
    char word[10];
    int place;
};

enum commands {
    push =  1,
    pop  =  2,
    add  =  3,
    sub  =  4,
    mul  =  5,
    divv =  6,
    out  =  7,
    jmp  = 10,
    ja   = 11,
    jae  = 12,
    jb   = 13,
    jbe  = 14,
    je   = 15,
    jne  = 16,
    hlt  = -1,
};


void RunCode(struct processor* SPU);

#endif