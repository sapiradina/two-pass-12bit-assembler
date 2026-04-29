#ifndef FILE_DATA_H
#define FILE_DATA_H

#include "utils.h"

/* A structure contains the data to build the .ext & .ent files */
/* for ent.file - all the entry labels - name & adrress in decimal value */
/* for ext.file - all the external labels that we used as operand in opcodes - name & adrress in decimal value */
typedef struct fileData 
{
    char* label_name;
    int dec_value; /* adrress of operand13 in decimal value */
    struct fileData* next;
}fileData;

/* A function that insert the name and the adrress in decimal value of the label in the data-table */
void insert_file_data(fileData** data_table , char* label_name , int dec_value);

/* A function that create the node for inserting in the data-table */
fileData* create_file_data(char* label_name , int dec_value);

/* A function that frees memory from the data-table of the .ext\.ent file */
void free_file_data(fileData* data_table);


#endif


