#include "preAssembler.h" 

bool pre_assembler(char* source_file_name , FILE** am_file , bool* error_passes_flag)
{
    FILE *source_file = NULL;
    char line[MAX_LINE_LENGTH] , copy_line[MAX_LINE_LENGTH] , macro_name[MAX_LABEL_LENGTH];
    char *am_file_name = NULL , *data = NULL , *current_word = NULL , *am_name=NULL ;
    macroHashTable* macro_table = calloc(1,sizeof(macroHashTable));
    int line_num=0; 
    bool macro_flag = false;
    
    /* source and .am file opening */
    if( (source_file = open_file_with_check(source_file_name , "r")) ==NULL )
        return true;
        
    if( (*am_file = open_file_with_check( (am_name = name_with_suffix(source_file_name , AM_WORD) ) , "w+b")) == NULL )
        return true;
    
    /* macro's spreading */ 
    while(fgets(line , sizeof(line) , source_file) != NULL)
    {
        line_num++;
        
        if(check_line_length( *am_file , line , line_num)) /* if 80< long line - report an error */
        {
            if(!check_empty_commend_line(line))  /* if empty\commend line - skip it */  
            {
                strcpy(copy_line , line);
                current_word = strtok(line, WHITE_TABS);
                    
                if(macro_flag == false) /* If we are inside a macro body */ 
                {
                    if(!macro_flag_false(current_word , line_num , macro_table , &macro_flag , macro_name , &data , copy_line , am_file))
                        *error_passes_flag = true;  
                }
                   
                else /* If we are NOT inside a macro body */ 
                {
                    if(!macro_flag_true(current_word , line_num , &macro_table , &macro_flag , macro_name , &data , copy_line , am_file))
                        *error_passes_flag = true;  
                }  
            }      
        }
        else
        {
            *error_passes_flag = true; 
            while( !(line[strlen(line) - 1] == '\n') && (fgets(line , sizeof(line) , source_file) != NULL)) {}  /* Advancing the line pointer so that in the next iteration it points to the beginning of the next line */ 
        } 
    }
    
    if(*error_passes_flag) /* If an error is found at the pre assembler - the .am file will be deleted */
        remove(am_file_name);
    else
        printf("\n\n.am file has been created");    
                   
    fclose(source_file);
    free_macro(&macro_table);
    free(data);
    free(am_name);
 
    return *error_passes_flag;      
}


bool check_macro(char* current_word , int line_num , macroHashTable* macro_table , bool* macro_flag , char macro_name[] , char** data)
{
    current_word = strtok(NULL , WHITE_TABS);

    if(is_label_or_macro_name_proper(current_word)) /* Checking if the macro name is correct */
    {
        if(lookup_macro(macro_table , current_word , line_num) == NULL) /* Checking if the macro name already exists */
        {
            if(strtok(NULL , WHITE_TABS) == NULL) /* Checking whether there are extra characters after the macro name */
            {
                *macro_flag = true;
                strcpy(macro_name , current_word);
                *data = malloc_with_check(1);
                return true;
            }
            
            print_error(EXTRANEOUS_TEXT , line_num);
        }
    }
    else
    {
        print_error(NOT_PROPER_LABEL_NAME , line_num);
        fprintf(stderr ,"macro");
    }
    
    return false;
}


bool macro_flag_true(char* current_word , int line_num , macroHashTable** macro_table , bool* macro_flag , char macro_name[] , char** data ,  char line[] , FILE** am_file)
{
    if(!strcmp(current_word , MACRO_END_WORD)) /* if endmcro is found (ending of macro body) */
    {
        if(strtok(NULL , WHITE_TABS) == NULL)
        {
            *macro_flag = false;
            fprintf(*am_file , "%s" , *data);
            insert_macro(macro_table , macro_name , *data); /* adding the nacro to the macro-table */
        } 

        else
        {
            print_error(EXTRANEOUS_TEXT, line_num);
            *macro_flag = false;
            return false;
        }  
        
        return true;
    }
    
    /* adding the line to the data of the current macro */
    *data = realloc_with_check(*data , strlen(*data) + strlen(line));
    strcat( *data , line );
    return true;
}


bool macro_flag_false(char* current_word , int line_num , macroHashTable* macro_table , bool* macro_flag , char macro_name[] , char** data , char line[] , FILE** am_file)
{
    if(!strcmp(current_word , MACRO_START_WORD)) /* if mcro is found (starting of macro body) */
    {
        if(!check_macro(current_word , line_num , macro_table , macro_flag , macro_name , data)) 
            return false;
    }      

    else if( (*data = lookup_macro(macro_table , current_word , line_num)) != NULL) /* if exists macro is found */
    {    
        if(strtok(NULL , WHITE_TABS) != NULL)
        {
            print_error(EXTRANEOUS_TEXT , line_num);
            return false;
        }
        fprintf(*am_file , "%s" , *data);
    }   

    else
        fprintf(*am_file , "%s" , line);  /* if un-macro (regular) line is found */
    
    return true;
}
