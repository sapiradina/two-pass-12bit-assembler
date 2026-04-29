#include "macro.h"

macroNode* create_macro(char macro_name[] , char* macro_data)
{
    macroNode* new_node = (macroNode*)malloc(sizeof(macroNode));
    /* ERROR_MEMORY_ALLOCATION_FAILED(new_node , NULL); */
    
    new_node->key = hash_by_alphabet(macro_name);
    strcpy(new_node->name , macro_name);
    new_node->next = NULL;

    new_node->data = malloc_with_check(strlen(macro_data));
    strcpy(new_node->data , macro_data);

    return new_node;
}


void insert_macro(macroHashTable** hash_table , char macro_name[] , char* macro_data)
{
    macroNode* new_macro_node = create_macro(macro_name , macro_data);
    int index = new_macro_node->key;
    
    new_macro_node->next = (*hash_table)->table[index];
    (*hash_table)->table[index] = new_macro_node;
}


char* lookup_macro(macroHashTable* hash_table, char macro_name[], int line_num) 
{
    int index = hash_by_alphabet(macro_name);
    macroNode* current = (hash_table)->table[index];
    
    while (current != NULL) 
    {
        if (!strcmp(current->name, macro_name)) 
            return current->data;
        
        current = current->next;
    }
    
    return NULL; 
}

void free_macro(macroHashTable** hash_table)
{
    int i;
    
    if (*hash_table == NULL) 
        return;
   
    for (i = 0; i < ALPHABET_SIZE; i++) 
    {
        macroNode* current = (*hash_table)->table[i];
        while (current != NULL) 
        {
            macroNode* next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
    }

    free(*hash_table);
}
