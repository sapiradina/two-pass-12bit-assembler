#include "errors.h"

const char* errors[ERRORS_NUM] = {

/* 0 */    "system error: memory allocation failed", 
/* 1 */    "can`t open the file ",
/* 2 */    "macro name is too long",
/* 3 */    "macro name is not proper",
/* 4 */    "macro name already exists",
/* 5 */    "extraneous text after end of command",
/* 6 */    "the line is longer than 80 characters",
/* 7 */    "too long name of ", 
/* 8 */    "not proper name of ", 
/* 9 */    "label was defined as .entry but was not declared",
/* 10 */   "label name already exists",
/* 11 */   "error in instruction word",   
/* 12 */   "invalid operand of string",
/* 13 */   "unprintable operand of string",
/* 14 */   "missing operand(s)",
/* 15 */   "invalid operand of data",
/* 16 */   "missing comma",
/* 17 */   "extra comma",
/* 18 */   "User Error: Missing name of file",
/* 19 */   "invalid operand of opcode" ,
/* 20 */   "memory space error - there are not enough cells in memory for this command",
/* 21 */   "opcode used an undeclared label in the file"
};

void print_error(errorName error_num , int line_num)
{
    if(line_num == 0) /* Error messages without association to a particular line */
        fprintf(stderr , "\n%s" , errors[error_num]);
    
    else /* Error messages with association to a particular line */
        fprintf(stderr ,"\nError at line %d: %s" , line_num , errors[error_num]);
}



