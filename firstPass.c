#include "firstPass.h" 

void first_pass(FILE* am_file , data_word* data_img , opcode_word** opcode_img , labelHashTable** label_table , bool* error_passes_flag)
{
    
    char line[MAX_LINE_LENGTH] , copy_line[MAX_LINE_LENGTH] , copy_copy_line[MAX_LINE_LENGTH] , label_name[MAX_LABEL_LENGTH];
    char* current_word = NULL;
    int line_num=0;
    bool label_flag=false;
    
    IC = 100;
    DC = 0;
    
    rewind(am_file);

    while(fgets(line , sizeof(line) , am_file) != NULL)
    {
        label_flag=false;
        strcpy(copy_line , line);
        strcpy(copy_copy_line , line);
        line_num++;

        current_word = strtok(line, WHITE_TABS);
        
        if(strchr(current_word, ':') != NULL) /* if label */
        {
            if( ( strcpy(label_name , check_label(current_word , line_num , error_passes_flag ) ) ) != NULL )
                label_flag = true;
            else
                continue;
            current_word = strtok(NULL, WHITE_TABS);
        }
        
        if(!strcmp(current_word , directive[1]) || !strcmp(current_word , directive[0])) /* if .data or .string */ 
        {
            if( label_flag  &&  (!insert_label( label_table , label_name , DC , DATA , line_num , error_passes_flag , NULL)) ) /* label definition */
                continue;  
            
            if(!is_proper_string(current_word , copy_line , line_num, data_img))
            {
                if (!is_proper_data(current_word , copy_line , line_num, data_img))
                    *error_passes_flag = true;
            } 
            continue;
        }
        
        else if(!strcmp(current_word , directive[2]) || !strcmp(current_word , directive[3])) /* if .entry or .extern */ 
        {
            if(!strcmp(current_word , directive[3])) /* if .extern */
                 is_proper_external_or_entry(current_word , copy_line , line_num , error_passes_flag , label_table , EXTERNAL , NULL);

            continue;
        }
        
        else if(label_flag  &&  (!insert_label( label_table , label_name , IC , CODE , line_num , error_passes_flag , NULL))) /* if opcode */
            continue;
        
        if(label_flag)
            current_word = strchr(copy_line , ':') + 1;
        
        current_word = strtok(current_word, WHITE_TABS);   
        if (!is_proper_opcode( current_word , copy_copy_line , line_num , opcode_img))
            *error_passes_flag = true;

    } 
    
    if(!*error_passes_flag)
        add_IC_to_data(label_table);
}
