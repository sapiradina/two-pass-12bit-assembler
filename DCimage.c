#include "DCimage.h"


bool is_proper_string(char* current_word , char line[] , int line_num , data_word* data_img)
{
    char* first_punctuations = strchr(line, '"');
    char* last_punctuations = strrchr(line, '"');
    
    if(!strcmp(current_word , directive[1]))
    {
        current_word = strtok(NULL , WHITE_TABS);
        
        if(current_word != NULL)
        {
            if(current_word[0] == '"' && last_punctuations != NULL && last_punctuations != first_punctuations)
            {
                last_punctuations++;
                if(strtok(last_punctuations , WHITE_TABS) == NULL)
                {
                    last_punctuations = strrchr(line, '"');
                    if(isprint_string(first_punctuations+1 , last_punctuations , line_num))
                    {
                        if(checking_memory_space( (strlen(last_punctuations) - strlen(first_punctuations) -1) , line_num ))
                        {
                            encoding_string(first_punctuations+1 , last_punctuations-1 , data_img);
                            return true;
                        }       
                    }
                }
                else
                    print_error(EXTRANEOUS_TEXT , line_num);
            }
            else
                print_error(INVALID_STRING , line_num);  
        }
        else
            print_error(MISSING_OPERAND , line_num);
    }
          
    return false;
}





bool is_proper_data(char* current_word ,  char line[] , int line_num , data_word* data_img)
{ 

    current_word = strtok(NULL , WHITE_TABS);
    
    if(current_word != NULL)
    {
        current_word = strchr(line , '.');
        current_word = current_word+5;
        
        if( check_commas( current_word , line_num) )
        {
            if( extract_numbers_from_data(current_word , line_num,data_img))
                return true;
        }
    }
    else
        print_error(MISSING_OPERAND,line_num);
    
    return false;
}


bool extract_numbers_from_data(char* data_operands , int line_num , data_word* data_img) 
{
    char *end_ptr , *operand;
    int count = 0 , num;
    int numbers[MAX_LINE_LENGTH];
    
    operand = strtok(data_operands , " \t\n,");
    
     while(operand != NULL)
    {
        if( isdigit(*operand) || *operand == '+' || *operand == '-')
        {
            num = strtol(operand, &end_ptr, 10);
            
            if( (-4095<=num && num<=4095) && *end_ptr == '\0') /* A number that can be represented in 12 bits is in the range between -4095 and 4095 (2’s complement) */
            {
                numbers[count] = num;
                count++;
                operand = strtok(NULL , " \t\n,");
                continue;
            }
        }       
       
        print_error(INVALID_DATA , line_num);
        return false;
    } 
    
    if(!checking_memory_space(count , line_num))
        return false;
        
    encoding_data(numbers,count,data_img);
    return true;
}


void encoding_string(char* first_char , char* last_char , data_word* data_img)
{
    while(first_char <= last_char)
    {
        data_img[DC++].w = *first_char;
        first_char++;
    }
    data_img[DC++].w = '\0';
}


void encoding_data(int numbers[] , int length , data_word* data_img)
{
    int i;
    for(i=0 ; i<length ; i++)
        data_img[DC++].w = numbers[i];
}

