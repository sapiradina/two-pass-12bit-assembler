#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define WHITE_TABS " \t\n"

/* constant numbers */
#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 32
#define DIRECTIVE_WORDS_NUM 4 
#define OPCODE_WORDS_NUM 16 
#define REGISTERS_NUM 8
#define FIRST_MEMORY_CELL 100
#define MEMORY_SIZE 1024
#define CELL_SIZE 12
#define ALPHABET_SIZE 26


/* files suffix words */
#define AM_WORD ".am"
#define ENTRY_WORD ".ent"
#define EXTERN_WORD ".ext"
#define OB_WORD ".ob"


/* types */
typedef enum {false,true} bool;


/* arrays*/
extern const char* registers[REGISTERS_NUM];
extern const char* opcodes[OPCODE_WORDS_NUM]; 
extern const char* directive[DIRECTIVE_WORDS_NUM];


extern int IC; /* instruction counter*/
extern int DC; /* data counter*/

#endif
