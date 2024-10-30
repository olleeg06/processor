#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SPU_function.h"
const char author[] = "610";
const char version[] =  "1";
const char num_commands[] = "14";
const int command = 14;

const char c_push[]  =  "push";
const char c_pop[]   =  "pop" ;
const char c_add[]   =  "add" ;
const char c_sub[]   =  "sub" ;
const char c_mul[]   =  "mul" ;
const char c_divv[]  =  "divv";
const char c_out[]   =  "out" ;
const char c_hlt[]   =  "hlt" ;
const char c_ja[]    =  "ja"  ;
const char c_jae[]   =  "jae" ;
const char c_jb[]    =  "jb"  ;
const char c_jbe[]   =  "jbe" ;
const char c_je[]    =  "je"  ;
const char c_jne[]   =  "jne" ;
const char c_jmp[]   =  "jmp" ;
const char rgs_ax[]  =  "ax"  ;
const char rgs_bx[]  =  "bx"  ;
const char rgs_cx[]  =  "cx"  ;
const char rgs_dx[]  =  "dx"  ;


size_t count_symbol (FILE* file);
int file_assert_header(FILE* file_assembler, FILE *file_write, char* buffer);





int main(){
    FILE *file_assembler   = fopen ("comands_assembler.txt" , "rb");
    FILE *file_write       = fopen ("comands.txt", "wb");
    assert (file_assembler && "file_read  open err");
    assert (file_write     && "file_write open err");
    size_t num_all_symbol = count_symbol (file_assembler);
    
    char* buffer = (char*) calloc (num_all_symbol, sizeof(char));
    assert (buffer != NULL);

    

    fread (buffer, sizeof(char), num_all_symbol, file_assembler);

    /*for (int i = 0; i < num_all_symbol; i++){
        printf ("%d ", buffer[i]);
    }*/

    file_assert_header (file_assembler, file_write, buffer);

    int help = strlen(author) + strlen(version) + strlen(num_commands) + 6;
    buffer = buffer + help;
    metky tags[10] = {};
    //    printf("&buffer = %p\n", buffer);
    for (int i = 0; i < command; i++){
        //printf ("i = %d, buffer[0] = %c\n", i, buffer[0]);

        if (strncmp (buffer, c_push, strlen(c_push)) == 0){
            buffer += strlen(c_push);
            fprintf(file_write, "%d", push);

        } else if (strncmp (buffer, c_pop, strlen(c_pop)) == 0){
            buffer += strlen(c_pop);
            fprintf(file_write, "%d", pop);

        } else if (strncmp (buffer, c_add, strlen(c_add)) == 0){
            buffer += strlen(c_add);
            fprintf(file_write, "%d", add);

        } else if (strncmp (buffer, c_sub, strlen(c_sub)) == 0){
            buffer += strlen(c_push);
            fprintf(file_write, "%d", sub);

        } else if (strncmp (buffer, c_mul, strlen(c_mul)) == 0){
            buffer += strlen(c_mul);
            fprintf(file_write, "%d", mul);

        } else if (strncmp (buffer, c_divv, strlen(c_divv)) == 0){
            buffer += strlen(c_divv);
            fprintf(file_write, "%d", divv);

        } else if (strncmp (buffer, c_out, strlen(c_out)) == 0){
            buffer += strlen(c_out);
            fprintf(file_write, "%d", out);

        } else if (strncmp (buffer, c_hlt, strlen(c_hlt)) == 0){
            buffer += strlen(c_hlt);
            fprintf(file_write, "%d", hlt);

        } else if (strncmp (buffer, c_jmp, strlen(c_jmp)) == 0){
            buffer += strlen(c_jmp);
            fprintf(file_write, "%d", jmp);

        } else if (strncmp (buffer, c_ja, strlen(c_ja)) == 0){
            buffer += strlen(c_ja);
            fprintf(file_write, "%d", ja);

        } else if (strncmp (buffer, c_jae, strlen(c_jae)) == 0){
            buffer += strlen(c_jae);
            fprintf(file_write, "%d", jae);

        } else if (strncmp (buffer, c_jb, strlen(c_jb)) == 0){
            buffer += strlen(c_jb);
            fprintf(file_write, "%d", jb);

        } else if (strncmp (buffer, c_jbe, strlen(c_jbe)) == 0){
            buffer += strlen(c_jbe);
            fprintf(file_write, "%d", jbe);

        } else if (strncmp (buffer, c_je, strlen(c_je)) == 0){
            buffer += strlen(c_je);
            fprintf(file_write, "%d", je);

        } else if (strncmp (buffer, c_jne, strlen(c_jne)) == 0){
            buffer += strlen(c_jne);
            fprintf(file_write, "%d", jne);

        } else if (strncmp (buffer, rgs_ax, strlen(rgs_ax)) == 0){
            buffer += strlen(rgs_ax);
            fprintf(file_write, "%d", 1);

        } else if (strncmp (buffer, rgs_bx, strlen(rgs_bx)) == 0){
            buffer += strlen(rgs_bx);
            fprintf(file_write, "%d", 2);

        } else if (strncmp (buffer, rgs_cx, strlen(rgs_cx)) == 0){
            buffer += strlen(rgs_cx);
            fprintf(file_write, "%d", 3);

        } else if (strncmp (buffer, rgs_dx, strlen(rgs_dx)) == 0){
            buffer += strlen(rgs_dx);
            fprintf(file_write, "%d", 4);

        } else if (buffer[0] == 32){
            fprintf(file_write, " ");
            buffer++;
            i--;

        } else if (isdigit(buffer[0])){
            while (isdigit(buffer[0])){
                fprintf(file_write, "%c", buffer[0]);
                buffer++;
            }

        } else if (buffer[0] == 13){
            fprintf (file_write, "%c", buffer[0]);
            buffer++;
            i--;
        } else if (buffer[0] == 10){
            fprintf (file_write, "%c", buffer[0]);
            buffer++;
            i--;
        }

    }
}


size_t count_symbol (FILE* file){
    fseek (file, 0, SEEK_END);
    size_t nums = ftell(file);
    fseek (file, 0, SEEK_SET);
    return nums;
}

int file_assert_header(FILE* file_assembler, FILE *file_write, char* buffer){

    if (strncmp(buffer, author, strlen(author)) != 0){
        printf("code does not match the author");
        exit(1);
    }
    fprintf(file_write,"%s\n", author);
    buffer = (buffer + strlen(author) + 2);
    
    if (strncmp(buffer, version, strlen(version)) != 0){
        printf("the version is not suitable");
        exit(1);
    }
    fprintf(file_write,"%s\n", version);
    buffer += strlen(version) + 2;

    if (strncmp(buffer, num_commands, strlen(num_commands)) != 0){
        printf("num_command ploxo");
        exit(1);
    }
    fprintf(file_write,"%s\n", num_commands);
    buffer += strlen(num_commands) + 2;
    return 0;
}

/*
610
1
13
1 30
1 70
3
1 80
1 60
4
6
7
-1
*/



/*
610
1
24
1 0
2 1
8 1
8 1
5
7
8 1
1 1
3
2 1
8 1
1 10
13 4
-1*/

/*610
1
24
push 0
pop ax
pushr 1
pushr 1
mul
out
pushr 1
push 1
add
pop ax
pushr 1
push 10
jb 4
hlt*/