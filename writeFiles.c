#include "writeFiles.h"

/* array to convert bits to BASE64 */
char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    
bool write_files(char* source_file_name , FILE* am_file ,  data_word* data_img , opcode_word* opcode_img , labelHashTable* label_table , fileData* ext_table , fileData* ent_table)
{  
    if( write_ob_file(source_file_name , data_img , opcode_img) && write_ext_file(source_file_name , ext_table) && write_ent_file(source_file_name , ent_table) ) 
        return true; 
    
    return false;
}


bool write_ob_file(char* source_file_name , data_word* data_img , opcode_word* opcode_img)
{
    FILE* ob_file = NULL ;
    opcode_word* opcode_ptr = NULL;
    int i;
    char* ob_name;

    if( ( ob_file = open_file_with_check( (ob_name = name_with_suffix(source_file_name , OB_WORD) )  , "w+") ) == NULL )
        return false;
    free(ob_name);
    
    /* printing the number of the machine words in the data-image and the opcode-image to .ob file */
    fprintf(ob_file , "%d %d\n" , (IC-100) , DC); 
    
    /* printing the opcode words to .ob file */
    for (opcode_ptr = opcode_img; opcode_ptr != NULL; opcode_ptr = opcode_ptr->next)
        convert_opcode_word_to_Base64(opcode_ptr , &ob_file);
    
    /* printing the data words to .ob file */
    for (i=0 ; i<DC ; i++)
        fprintf(ob_file, "%c%c\n", base64_table[(data_img[i].w & 4032) >> 6] , base64_table[data_img[i].w & 63]);
        
    printf("\n.ob file has been created");    
    fclose(ob_file);
    return true;     
} 

void convert_opcode_word_to_Base64(opcode_word* opcode_ptr , FILE** ob_file)
{
    int  i=0 , dest , source , L = opcode_ptr->L; /* i = index to pass on the bits[] of opcode_ptr */
    unsigned int word_12_bits , right_6_bits , left_6_bits; /* word_12_bits = the 12 bits of a complete opcode_ptr->bits[i], */
                                                            /* first_6_bits = the right 6 bits of 'word_12_bits' */
                                                           /* left_6_bits = the left 6 bits of 'word_12_bits' */
    source = opcode_ptr->bits[i].first_word.source;
    dest = opcode_ptr->bits[i].first_word.dest;
    
    /* go through each word of opcode_ptr individually, and print it to the .ob file */       
    for(i=0 ; i<L ; i++)
    {
        if(i==0)
            word_12_bits = ((opcode_ptr->bits[i].first_word.ARE) | (opcode_ptr->bits[i].first_word.dest << 2) | (opcode_ptr->bits[i].first_word.opcode << 5) | (opcode_ptr->bits[i].first_word.source << 9));
        else if(i==1)
            word_12_bits = make_operand_word(source , i , opcode_ptr);
        else
            word_12_bits = make_operand_word(dest , i , opcode_ptr);
            
        right_6_bits = word_12_bits & 63;
        left_6_bits = (word_12_bits & 4032) >> 6;
        fprintf(*ob_file, "%c%c\n", base64_table[left_6_bits] , base64_table[right_6_bits]);
    }
}

unsigned int make_operand_word(int source_or_dest , int i , opcode_word* opcode_ptr) 
{
    if( source_or_dest == 5 ) /* If it is a code word of operand of address 5 */
        return ((opcode_ptr->bits[i].operand5.ARE) | (opcode_ptr->bits[i].operand5.dest_reg << 2) | (opcode_ptr->bits[i].operand5.source_reg << 7));    
    else /* if it is a code word of operand of address 1 or 3 */
        return ((opcode_ptr->bits[i].operand13.ARE) | (opcode_ptr->bits[i].operand13.value << 2));
}
 
bool write_ext_file(char* source_file_name , fileData* ext_table)
{
    FILE* ext_file = NULL ;
    fileData* current = ext_table;
    char* ext_name;
    
    if(ext_table != NULL)
    {
        if( ( ext_file = open_file_with_check( (ext_name = name_with_suffix(source_file_name , EXTERN_WORD)) , "w+") ) == NULL )
            return false;
        free(ext_name);
            
        while (current != NULL) 
        {
            fprintf(ext_file , "%s  %d\n" , current->label_name , current->dec_value);
            current = current->next;
        }
        
        fclose(ext_file);
        printf("\n.ext file has been created");
    }
    else
        printf("\nno external labels were used in the file, therefore .ext file not created.");
    
    return true;      
} 


bool write_ent_file(char* source_file_name , fileData* ent_table)
{
    FILE* ent_file = NULL ;
    fileData* current = ent_table;
    char* ent_name=NULL;
    
    if(ent_table != NULL)
    {
        if( ( ent_file = open_file_with_check( (ent_name=name_with_suffix(source_file_name , ENTRY_WORD)) , "w+") ) == NULL )
            return false;
        free(ent_name);
            
        while (current != NULL) 
        {
            fprintf(ent_file , "%s  %d\n" , current->label_name , current->dec_value);
            current = current->next;
        }
        
        fclose(ent_file);
        printf("\n.ent file has been created");
    }
    else
        printf("\nno entry labels were used in the file, therefore .ent file not created.");
    
    return true;  
} 
