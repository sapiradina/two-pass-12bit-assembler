#include "utils.h"


char* malloc_with_check(size_t size) 
{ 
    char* variable = (char*)malloc(size + 1);

    if (variable == NULL || size==0) 
    {
        print_error(MEMORY_FAILED,0);
        exit(1);
    }
    
    return variable;
}


char* realloc_with_check(char* data , size_t size) 
{
    char* variable = (char*)realloc(data , size);

    if (variable == NULL || size==0) 
    {
        print_error(MEMORY_FAILED,0);
        exit(1);
    }
    
    return variable;
}


FILE* open_file_with_check(char* file_name, char* mode) 
{
    FILE* file = fopen(file_name, mode);
    
    if ( file == NULL) 
    {
        print_error(OPEN_FILE_FAILED,0);
        printf("%s" , file_name);
    }
    
    return file;
}


bool check_line_length(FILE* file , char* line , int line_num)
{
    if (line[strlen(line) - 1] == '\n')
        return true;
    
    print_error(LONG_LINE , line_num);
    return false;
}


char* name_with_suffix(char* file_name , char suffix[])
{   
    char* new_file_name = malloc_with_check(strlen(file_name) + strlen(suffix) + 1);
    strcpy(new_file_name , file_name);
    strcat(new_file_name , suffix);
    
    return new_file_name;
}


bool check_empty_commend_line(char line[])
{
    int i=0;
    
    if( !(line[0]==';' || line[0]=='\n') )
    {   
        while (line[i] != '\0') 
        {
            if (!isspace(*line) && *line != '\t') 
                return false;
            
            i++; 
        }
    }    
    return true;
}


bool check_commas(char* str , int line_num) 
{
    bool comma_needed = false , in_operand = false;
    char* copy_str = malloc_with_check(strlen(str));
    strcpy(copy_str , str);
    
    while(*copy_str != '\0')
    {
        if(!(*copy_str==' ' || *copy_str=='\t'))
        {
            if(!(*copy_str == ','))
            { 
                if(!in_operand)
                {      
                    if(comma_needed)
                    {
                        print_error(MISSING_COMA , line_num);
                        free(copy_str);
                        return false;
                    }
                    in_operand=true;
                    comma_needed=true;
                }
            }
            else if(!comma_needed)
            {
                print_error(EXTRA_COMMA , line_num);
                free(copy_str);
                return false;    
            }
            else
            {
                comma_needed = false;
                in_operand=false;
            }
        } 
        else 
            in_operand=false;
        
        
        copy_str++; 
    }
    
    if(in_operand || comma_needed)
        return true;  
    
    print_error(EXTRA_COMMA , line_num);
    free(copy_str);   
    return false;
}


bool isprint_string(char* start_str , char* end_str , int line_num)
{
    while(start_str != end_str)
    {
        if(!isprint(*start_str))
        {
            print_error(UNPRINTABLE_STRING , line_num);
            return false;
        }
        start_str++;
    }
    return true;
}


int is_register(char* name)
{
    int i;
    
    for( i=0 ; i<REGISTERS_NUM ; i++)
    {
        if(!strcmp( name , registers[i]))
            return i;
    }
    
    return -1;
}


bool is_integer(char* str)
{
    char *end_ptr;
    
    if( isdigit(*str) || *str == '+' || *str == '-') 
    {
        strtol(str, &end_ptr, 10);
        
        if(*end_ptr == '\0') 
            return true;
    }
    
    return false;
}


bool checking_memory_space(int additional_memory , int line_num)
{
    if(IC+DC+additional_memory > MEMORY_SIZE)
    {
        print_error( SMALL_MEMORY , line_num);
        return false;
    }
    
   return true;
}
