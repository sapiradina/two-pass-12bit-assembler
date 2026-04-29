#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include "macro.h"

/* A function that gets the name of the source file, variable to store the .am file and an error-flag. */
/* It manages the pre-assembler phase, creates the .am file if no errors are found and returns the error flag.*/
bool pre_assembler(char* source_file_name , FILE** am_file , bool* error_passes_flag);

/* A function that checks the correctness of the macro declaration line, where current_word points to the start of the name of the macro in the line. */
/* If it is correct, the macro name will be stored in macro_name and true will be returned. otherwise - false. */
bool check_macro(char* current_word , int line_number , macroHashTable* macro_table , bool* macro_flag , char macro_name[] , char** data);

/* A function that analyzes a line inside a macro body. If an error is found, false will be returned. Otherwise - true */
/* current_word is a pointer to the start of the line. */
bool macro_flag_true(char* current_word , int line_num , macroHashTable** macro_table , bool* macro_flag , char macro_name[] , char** data , char line[] , FILE** am_file);

/* A function that analyzes a line that NOT inside a macro body. If an error is found, false will be returned. Otherwise - true */
/* current_word is a pointer to the start of the line. */
bool macro_flag_false(char* current_word , int line_num , macroHashTable* macro_table , bool* macro_flag , char macro_name[] , char** data , char line[] , FILE** am_file);

#endif 
