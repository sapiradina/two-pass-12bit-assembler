#include "secondPass.h"

void second_pass(FILE* am_file ,  data_word* data_img , opcode_word** opcode_img , labelHashTable** label_table , bool* error_passes_flag , fileData** ent_table , fileData** ext_table)
{

    char line[MAX_LINE_LENGTH] , copy_line[MAX_LINE_LENGTH];  
    char* current_word = NULL;
    int line_num=0;
    
    rewind(am_file); 

    while(fgets(line , sizeof(line) , am_file) != NULL)
    {
        strcpy(copy_line , line);
        line_num++;
        
        current_word = strtok(copy_line, WHITE_TABS);
        
        if(strchr(current_word, ':') != NULL) /* if label */ 
            current_word = strtok(NULL, WHITE_TABS);
        
        if(!strcmp(current_word , directive[2])) /* if .entry , change/update to ENTRY */
            is_proper_external_or_entry(current_word , line , line_num , error_passes_flag , label_table , ENTRY , ent_table);
    } 
    
    if(!complete_encoding_opcode_image(*opcode_img , *label_table , ext_table))  /* complete the opcode-image */
        *error_passes_flag=true;
    
    fclose(am_file);
}
