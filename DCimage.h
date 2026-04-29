#ifndef DC_IMAGE_H
#define DC_IMAGE_H

#include "label.h"
#include "utils.h"

/* A machine data word (a parameter of .data or .string) */
typedef struct data_word
{
    unsigned int w : 12; 
}data_word;


/* A function that gets a code line of '.string' and analyzes it. */
/* If the line was encoded successfully and without errors, true will be returned. Otherwise - false. */
bool is_proper_string(char* current_word , char line[] , int line_num , data_word* data_img);

/* A function that gets a code line of '.data' and analyzes it. */
/* If the line was encoded successfully and without errors, true will be returned. Otherwise - false. */
bool is_proper_data(char* current_word ,  char line[] , int line_num , data_word* data_img);

/* A function that gets a string which is the part of the code line where operands of integers are written, and transfers each integer to an array. */
/* If an error is found, false will be returned. otherwise - true. */
bool extract_numbers_from_data(char* data_operands , int line_num , data_word* data_img);

/* A function that gets pointers to the start and end characters of a string, and a data-image, and adds each character in the string to the data image */
void encoding_string(char* first_char , char* last_char , data_word* data_img);

/* A function that gets an array with integers, the length of this array and a data image, and adds each number in the array to the data image */
void encoding_data(int numbers[] , int length , data_word* data_img);

#endif
