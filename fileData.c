#include "fileData.h"


void insert_file_data(fileData** data_table , char* label_name , int dec_value)
{
    fileData *new_node = create_file_data(label_name , dec_value) , *current=*data_table;
        
    if (*data_table == NULL) 
        *data_table = new_node;
    
    else 
    {
        while (current->next != NULL)
            current = current->next;
        
        current->next = new_node;
    }
}


fileData* create_file_data(char* label_name , int dec_value)
{
    fileData* new_node = (fileData*)malloc(sizeof(fileData));
    if(new_node == NULL )
    {
        print_error(MEMORY_FAILED,0);
        exit(1);
    }
    
    new_node->label_name = label_name;
    new_node->dec_value = dec_value;
    new_node->next = NULL;
    
    return new_node;
}

void free_file_data(fileData* data_table) 
{
    fileData* current = NULL;
    
    while (data_table != NULL) 
    {
        current = data_table;
        data_table = data_table->next;
        free(current); 
    }
}


