#ifndef ERRORS_H
#define ERRORS_H

#include "general.h"

#define ERRORS_NUM 22

typedef enum { MEMORY_FAILED=0 , OPEN_FILE_FAILED=1 , LONG_MACRO_NAME=2 , NOT_PROPER_MACRO_NAME=3 , EXIST_MACRO_NAME=4 , EXTRANEOUS_TEXT=5 , LONG_LINE=6 ,
                  LONG_LABEL_NAME=7 , NOT_PROPER_LABEL_NAME=8 , ENTRY_NOT_DECLARED=9 , EXIST_LABEL_NAME=10 , INSTRUCTION_WORD_ERROR=11 , INVALID_STRING=12 ,
                  UNPRINTABLE_STRING=13 , MISSING_OPERAND=14 , INVALID_DATA=15 , MISSING_COMA=16 , EXTRA_COMMA=17 , MISSING_FILE_NAME=18 , INVALID_OPCODE_OPERAND=19 ,
                  SMALL_MEMORY=20 , LABEL_NOT_DECLARED=21 } errorName; 

extern const char* errors[ERRORS_NUM]; /* All assembler error messages */

/* A function that gets the error number and the line number where the error occurred, and prints the error accordingly. */
/* If there is no association to a certain line, then line_num=0 */
void print_error(errorName error_num , int line_num);

#endif
