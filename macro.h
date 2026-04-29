#ifndef MACRO_H
#define MACRO_H

#include "general.h"
#include "label.h"
#include "utils.h"

#define MACRO_START_WORD "mcro"
#define MACRO_END_WORD "endmcro"


/* macro node */
typedef struct macroNode 
{
    int key; /* the position of the macro in the macro-table, according to the alphabet */
    char name[MAX_LABEL_LENGTH+1];
    char* data; /* the macro body */
    struct macroNode* next;  
}macroNode;

/* macro table - sorted by the order of the alphabet */
typedef struct macroHashTable 
{
    macroNode* table[ALPHABET_SIZE];
} macroHashTable;

/* A function that gets 2 strings - name of macro and data, create a macro node and return it. If the memory allocation failed - NULL will be returned */
struct macroNode* create_macro(char macro_name[] , char* macro_data);

/* A function that gets all the information needed to create a macro node, and inserts the new node into the macro table */
void insert_macro(macroHashTable** hash_table , char macro_name[] , char* macro_data);

/* A function that gets a name of macro and macro table. */
/* If a macro with a matching name is found in the table, the data of this macro node will be returned. otherwise - NULL will be returned */
char* lookup_macro(macroHashTable* hash_table, char macro_name[], int line_num);

/* A function that gets a macro-table, and frees the memory allocated to it */
void free_macro(macroHashTable** hash_table);

#endif
