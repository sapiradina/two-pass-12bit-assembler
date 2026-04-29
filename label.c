#include "label.h"


labelNode* create_label(char label_name[] , int dec_value , labelType label_type)
{
    labelNode* new_node = (labelNode*)malloc(sizeof(labelNode));
    if(!new_node)
    {
        print_error(MEMORY_FAILED,0);
        exit(1);
    }
    
    new_node->key = hash_by_alphabet(label_name);
    strcpy(new_node->name , label_name);
    new_node->type = label_type;
    new_node->dec_value = dec_value;
    new_node->next = NULL;
    
    return new_node;
}


bool insert_label(labelHashTable** hash_table , char label_name[] , int dec_value , labelType label_type , int line_num , bool* error_flag , fileData** ent_table)
{
    labelNode* exist_label = lookup_label(*hash_table , label_name) ;
    labelNode* new_label_node = create_label(label_name , dec_value , label_type);
    int index = new_label_node->key;
    
    
    if( exist_label != NULL) /* if the label-node is already exist */
    {
        if( (label_type==EXTERNAL && exist_label->type==EXTERNAL) || (label_type==ENTRY && exist_label->type==ENTRY)) /* if entry\extern label that already declared */
            return true;
        
        else if( label_type==ENTRY && exist_label->type !=EXTERNAL) /* if it is an entry label that already declared */
        {
            exist_label->type = ENTRY;
            insert_file_data(ent_table , exist_label->name , exist_label->dec_value);
            return true;
        }
        
        print_error(EXIST_LABEL_NAME , line_num);
        *error_flag = true;
        return false;  
    }
    else
    {
        if(label_type == ENTRY) /* if it is an entry label that not declared */
        {
            print_error(ENTRY_NOT_DECLARED , line_num);
            *error_flag = true;
            return false;
        }
    }

    new_label_node->next = (*hash_table)->table[index];
    (*hash_table)->table[index] = new_label_node;
           
    return true;
}


labelNode* lookup_label(labelHashTable* hash_table, char label_name[]) 
{
    int index = hash_by_alphabet(label_name);
    labelNode* current = hash_table->table[index];
    
    while (current != NULL) 
    {
        if (!strcmp(current->name, label_name)) 
            return current;
        
        current = current->next;
    }

    return NULL; 
}


void free_label(labelHashTable** hash_table)
{
    int i;
    
    if (*hash_table == NULL) 
        return;
   
    for (i = 0; i < ALPHABET_SIZE; i++) 
    {
        labelNode* current = (*hash_table)->table[i];
        while (current != NULL) 
        {
            free(current);
            current = current->next;
        }
    }

    free(*hash_table);
}



bool is_label_or_macro_name_proper(char* name)
{
    if(strlen(name)<=MAX_LABEL_LENGTH && strlen(name)>0)
    {
        if( is_opcode(name) == -1 && isalpha(name[0]))
        {
            name++;

            while (*name != '\0') 
            {
                if (!isalpha(*name) && !isdigit(*name))
                    return false;

                name++;
            }
           
            return true;
        }
    }
    
    return false;
}


char* check_label(char* current_word , int line_num , bool* error_flag)
{
    char *copy_current_word = malloc_with_check(strlen(current_word)) , *ptr=NULL;
    strcpy(copy_current_word , current_word);
    ptr = strchr(copy_current_word, ':');
    if(ptr!=NULL)
        *ptr = '\0';
    
    if(is_label_or_macro_name_proper(copy_current_word)) 
            return copy_current_word; 
        
    print_error(NOT_PROPER_LABEL_NAME , line_num);
    printf("label");
    *error_flag = true;
    free(copy_current_word);
    return NULL;   
}


int is_opcode(char* name)
{
    int i;
    
    for( i=0 ; i<OPCODE_WORDS_NUM ; i++)
    {
        if(!strcmp( name , opcodes[i]))
            return i;
    }
    
    return -1;
}



int hash_by_alphabet(char name[])
{
    int index;
    
    if(isupper(name[0]))
        index = name[0] - 'A'; 
    else
        index = name[0] - 'a'; 
            
    return index % ALPHABET_SIZE;
}



void add_IC_to_data(labelHashTable** hash_table)
{
    int i;
    
    if (*hash_table == NULL) 
        return;
   
    for (i = 0; i < ALPHABET_SIZE; i++) 
    {
        labelNode* current = (*hash_table)->table[i];
        while (current != NULL) 
        {
            labelNode* next = current->next;
            if(current->type == DATA)
                current->dec_value += IC;
            
            current = next;
        }
    }
}
