#ifndef UTILS_H
#define UTILS_H

#include "errors.h"

/* A function based on malloc() and adds a check to see if the memory allocation was successfully performed. */
/* If so, a string pointer will be returned. Otherwise - NULL. */
char* malloc_with_check(size_t size);

/* A function based on realloc() and adds a check to see if the memory allocation was successfully performed. */
/* If so, a pointer to string will be returned. Otherwise - NULL. */
char* realloc_with_check(char* data , size_t size);

/* A function that gets name and mode of file, opens a new file, and checks if it was opened successfully.*/
/* If so, a file pointer will be returned. Otherwise - NULL. */
FILE* open_file_with_check(char* file_name, char* mode);

/* A function that gets a file, a pointer and number of line in it. If the line is longer than 80 characters, */
/* the function returns false. Otherwise - true will be returned.*/
bool check_line_length(FILE* file , char* line , int line_num);

/* A function that gets a file-name and an suffix, unifies them and returns the new name. */
char* name_with_suffix(char* file_name , char suffix[]);

/* A function that gets a line and checks whether it is a comment line or an empty line. */
/* If so, true will be returned. Otherwise - false. */
bool check_empty_commend_line(char line[]);

/* A function that gets a string and check if it separated by proper commas */
/* If so, true will be returned. Otherwise - false. */
bool check_commas(char* str , int line_num);

/*  A function that gets pointers to beginning and end of a string, and returns true if all the characters of the string are printable. Otherwise - false will be returned. */
bool isprint_string(char* start_str , char* end_str , int line_num);

/* A function that gets a string and check if its a name of register. */
/* If so, the register number will be returned. Otherwise - 0 will be returned. */
int is_register(char* name);

/* A function that gets a string and check if it represent an integer. */
/* If so, 'true' will be returned. Otherwise - 'false' will be returned. */
bool is_integer(char* str);


/* A function that checks whether following the insertion of machine-word (its size is additional_memory) to opcode\data image we exceed the memory size. */
/* If there is an exception, false will be returned. Otherwise - false.*/
bool checking_memory_space(int additional_memory , int line_num);


#endif
