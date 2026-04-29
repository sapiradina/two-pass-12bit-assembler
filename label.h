#ifndef LABEL_H
#define LABEL_H

#include "errors.h"
#include "fileData.h"

typedef enum { DATA , EXTERNAL , CODE , ENTRY } labelType;


typedef struct labelNode 
{
    int key;
    char name[MAX_LABEL_LENGTH+1];
    int dec_value; /* value in decimal base */
    labelType type;  
    struct labelNode* next;  
}labelNode;


typedef struct labelHashTable 
{
    labelNode* table[ALPHABET_SIZE];
} labelHashTable;

/* A function that gets a string of letters, and converts the first letter in it to a number in the order of the alphabet, and returns it.*/
/* Assumption - the first letter in the string is an uppercase or lowercase letter */
int hash_by_alphabet(char name[]);

/* A function that gets name , decimal value and type of label and creates a node of label */
labelNode* create_label(char label_name[] , int dec_value , labelType label_type);

/* A function that gets a string (name of label)  and hash-table of labels. */
/* If a label with a matching name is found, we will return this label node. otherwise - NULL */
labelNode* lookup_label(labelHashTable* hash_table, char label_name[]) ;

/* A function that gets a hash-table of labels, and frees the memory allocated to it */
void free_label(labelHashTable** hash_table);

/* */
bool insert_label(labelHashTable** hash_table , char label_name[] , int dec_value , labelType label_type , int line_num , bool* error_flag , fileData** ent_table);

/* A function that gets a string, and checks whether it is a proper name of a macro\label (a string that starts with a letter, */
/* the rest of which are numbers or letters, with the proper length defined) */
/* If so - true will be returned. otherwise - false */
bool is_label_or_macro_name_proper(char* name);

/* A function that gets a string, a line number and a boolean variable, and performs a check to see if the label is correct. If so - true will be returned. */
/* Otherwise - false will be returned, and an appropriate error message and flag change will be performed accordingly*/
char* check_label(char* current_word , int line_num , bool* error_flag);

/* A function that gets a string, and checks whether it is a valid opcode name. */
/* If so - the opcode`s number will be returned. otherwise - 0 will be returned */
int is_opcode(char* name);

/* At the end of the first pass, the function adds the IC value to the decimal value of each data\string label */
void add_IC_to_data(labelHashTable** hash_table);



#endif
