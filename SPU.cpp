#include <stdio.h> 
#include <assert.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

#include "SPU_function.h"
#include "stack_function.h"

#define AUTHOR 610
#define VERSION 1



int main(){
    processor SPU = {};
    
    FILE *file = fopen ("comands.txt", "rb");
    assert (file && "file open err");

    int author = 0;
    fscanf(file, "%d", &author);
    assert (AUTHOR == author && "code does not match the author");
    printf ("author = %d\n", author);
    int version = 0;
    fscanf(file, "%d", &version);
    assert (VERSION == version && "the version is not suitable");

    int num_commands = 0;
    fscanf(file, "%d", &num_commands);
    assert (num_commands != NULL && "no commands");
    printf("num_commands = %d\n", num_commands);

    SPU.code = (stack_elem_t*) calloc (num_commands, sizeof(stack_elem_t));
    for (size_t i = 0; i < num_commands; i++){
        fscanf(file, "%d", &SPU.code[i]);
    }

    RunCode(&SPU);
    
}
