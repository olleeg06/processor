#include <stdio.h> 
#include <assert.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

#include "SPU_function.h"
#include "stack_function.h"



void RunCode (struct processor* SPU){
    stack_t stk = {};

    StackCtor(&SPU->stk, 2);     

    while ((int)SPU->code[SPU->ip] != -1){
        printf("command{%d} = %d\n",SPU->ip, SPU->code[SPU->ip]);
        SPU->ip++;
    } SPU->ip = 0;
        
    while (1){
        //StackDumb(&SPU->stk);
        if (SPU->code[SPU->ip] == push){                                      //push
            if (SPU->code[SPU->ip + 1] == 1){
                StackPush (&SPU->stk, SPU->code[SPU->ip + 2]);
            } else if (SPU->code[SPU->ip + 1] == 2){
                StackPush (&SPU->stk, SPU->registers[SPU->code[SPU->ip + 2] - 1]);
            }
            SPU->ip += 3;

        } else if (SPU->code[SPU->ip] == pop){                               //pop
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            SPU->registers[SPU->code[SPU->ip + 1] - 1] = a;
            SPU->ip +=2;
        
        } else if (SPU->code[SPU->ip] == add){                               //add 
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            StackPush (&SPU->stk, b + a);
            SPU->ip++;

        } else if (SPU->code[SPU->ip] == sub){                               //sub
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            StackPush (&SPU->stk, b - a);
            SPU->ip++;

        } else if (SPU->code[SPU->ip] == mul){                               //mul
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            StackPush (&SPU->stk, b * a);
            SPU->ip++;
        
        } else if (SPU->code[SPU->ip] == divv){                               //div 
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            StackPush (&SPU->stk, b / a);
            SPU->ip++;

        } else if (SPU->code[SPU->ip] == out){                               //out 
            stack_elem_t x = 0;
            StackPop(&SPU->stk, &x);
            printf("%d\n", x);
            SPU->ip++;
        
        } else if (SPU->code[SPU->ip] == jmp){                               //jmp
            SPU->ip = SPU->code[SPU->ip + 1];
        
        } else if (SPU->code[SPU->ip] == ja){                                //ja
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            if (a < b){
                SPU->ip = SPU->code[SPU->ip + 1];
            } else 
                SPU->ip += 2;
            
        } else if (SPU->code[SPU->ip] == jae){                               //jae
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            if (a <= b){
                SPU->ip = SPU->code[SPU->ip + 1];
            } else 
                SPU->ip += 2;
        
        } else if (SPU->code[SPU->ip] == jb){                               //jb
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            if (a > b){
                SPU->ip = SPU->code[SPU->ip + 1];
            } else
                SPU->ip += 2;
        
        } else if (SPU->code[SPU->ip] == jbe){                               //jbe
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            if (a >= b){
                SPU->ip = SPU->code[SPU->ip + 1];
            } else 
                SPU->ip += 2;
        
        } else if (SPU->code[SPU->ip] == je){                               //je
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            if (a == b){
                SPU->ip = SPU->code[SPU->ip + 1];
            } else 
                SPU->ip += 2;
        
        } else if (SPU->code[SPU->ip] == jne){                               //jne
            stack_elem_t a = 0;
            StackPop(&SPU->stk, &a);
            stack_elem_t b = 0;
            StackPop(&SPU->stk, &b);
            if (a != b){
                SPU->ip = SPU->code[SPU->ip + 1];
            } else 
                SPU->ip += 2;
        
        } else if (SPU->code[SPU->ip] == hlt){                              //hlt
            
            break;

        } else {
            printf("sorry, but you dayn\n");
            break;
        }
    } 
    
    return;
}