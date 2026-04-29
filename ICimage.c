#include "ICimage.h"

opcode_word* malloc_opcode_word_with_check() 
{ 
    opcode_word* variable = (opcode_word*)malloc(sizeof(opcode_word));
    
    if (variable == NULL) 
    {
        print_error(MEMORY_FAILED,0);
        exit(1);
    }
    
    return variable;
}


void is_proper_external_or_entry(char* current_word , char line[] , int line_num , bool *flag_error , labelHashTable** label_table , labelType ext_or_ent , fileData** ent_table)
{
    char label_name[MAX_LABEL_LENGTH];
    char* operand = NULL;
    current_word = strtok(NULL , WHITE_TABS);
    
    if(current_word != NULL)
    {
        current_word = strchr(line , '.');
        
        if( ext_or_ent == EXTERNAL)
            current_word = current_word+7;
        else
            current_word = current_word+6;
            
        if(check_commas( current_word , line_num))
        {
            operand = strtok(current_word , " \t\n,");
            
            while(operand != NULL)
            {
                if( ( strcpy(label_name , check_label(operand , line_num , flag_error ) ) ) != NULL )
                    insert_label(label_table , label_name , 0 , ext_or_ent , line_num , flag_error , ent_table);
                else
                {
                    *flag_error = true;
                    return;
                }
                
                operand = strtok(NULL , " \t\n,");
            } 
        }    
    }
    else
    {
        print_error(MISSING_OPERAND,line_num);
        *flag_error = true;
    }
}


bool is_proper_opcode(char* current_word ,  char line[] , int line_num , opcode_word** opcode_img)
{
    int opcode;
    if( (opcode = is_opcode(current_word)) != -1) 
    {
        if( opcode==14 || opcode==15 ) /* opcode with 0 operands */
        {
            if(line_processing_opcode_0_operands(opcode , current_word , line_num , opcode_img))
                return true;
        }
               
        else if( ( 4<=opcode && opcode<=5 ) || ( 7<=opcode && opcode<=13 ) ) /* opcode with 1 operands */
        {
            if(line_processing_opcode_1_operands(opcode , current_word , line , line_num , opcode_img))
                return true;
        }  
             
        else if( ( 0<=opcode && opcode<=3 ) || opcode==6 ) /* opcode with 2 operands */
        {
            if(line_processing_opcode_2_operands(opcode , current_word , line , line_num , opcode_img))
                return true;
        }
    }
    else
        print_error(INSTRUCTION_WORD_ERROR,line_num); 
    
    return false;       
}


int address_type(char* operand , int* num , int line_num)
{    
    if( is_integer(operand) ) /* addressing method 1 */
    {  
        *num = strtol(operand, NULL, 10); 
        if( -1023<=*num && *num<=1023) /* A number that can be represented in 10 bits is in the range between -1023 and 1023 (2’s complement) */
            return 1;
    }   

    else if(is_label_or_macro_name_proper(operand)) /* addressing method 3 */
        return 3;

    else if( (*num = is_register(operand)) != -1) /* addressing method 5 */
        return 5;
   
    return 0;           
}


bool create_opcode_word_1_operands(opcode_word** opcode_img , int opcode , int dest , int num , int line_num , char* operand) 
{
    opcode_word* new_node = malloc_opcode_word_with_check();
    
    int L=0 , operand3_dec_value=0 ;
    create_first_opcode_word(new_node , opcode , 0 , dest , L++);
    
    if(dest == 5)
        create_operand5_opcode_word(new_node , 0 , num , L);   
    else
        operand3_dec_value = create_operand13_opcode_word(new_node , num , dest , L++ , operand);
    
    new_node->L = L;
    new_node->line_num = line_num;
    new_node->operand3_dec_value = operand3_dec_value;
    
    return insert_opcode_word( opcode_img , new_node );
}

/*  

bool checking_memory_space(int line_num , opcode_word** opcode_img , opcode_word* new_node)
{
     if(IC+DC+(new_node->L) > MEMORY_SIZE)
    {
        print_error( SMALL_MEMORY , line_num);
        return false;
    }
    
    IC = IC+(new_node->L);
    
    if(new_node->operand3_dec_value == 0)
    {
        new_node->label_name = NULL;
        new_node->to_complete = 0;
    }
    
    insert_opcode_word( opcode_img , new_node );
        
    return true;
}


*/
bool insert_opcode_word(opcode_word** opcode_img , opcode_word* img_new_node)
{
    opcode_word* current = *opcode_img;
    img_new_node->next = NULL;
    
    if(!checking_memory_space(img_new_node->L , img_new_node->line_num))
        return false; 
        
    IC = IC + (img_new_node->L);
    
    if(img_new_node->operand3_dec_value == 0)
    {
        img_new_node->label_name = NULL;
        img_new_node->to_complete = 0;
    }
    
    if (*opcode_img == NULL) 
        *opcode_img = img_new_node;
    else 
    {
        while (current->next != NULL) 
            current = current->next;
        
        current->next = img_new_node;
    } 
    return true;
}


bool line_processing_opcode_1_operands(int opcode , char* current_word , char line[] , int line_num , opcode_word** head)
{
    char *copy_line = malloc_with_check(strlen(line));
    strcpy(copy_line , line);
    line = strstr(line, opcodes[opcode])+strlen(opcodes[opcode]);
    current_word=strtok(line , WHITE_TABS);
    
    if(current_word != NULL)
    {
        current_word = strtok(NULL , WHITE_TABS);
        
        if(current_word == NULL)
        {        
            copy_line = strstr(copy_line, opcodes[opcode])+strlen(opcodes[opcode]);
            current_word=strtok(copy_line , WHITE_TABS);
            
            if(check_1_operands(opcode , current_word , line_num , head))
                return true;
        }
        else
            print_error( EXTRANEOUS_TEXT , line_num); 
    }
    else
        print_error( MISSING_OPERAND , line_num);
        
    return false;
}


bool check_1_operands(int opcode , char* operand , int line_num , opcode_word** head)
{
    int num=0 , dest=0;
    
    if( (dest = address_type(operand , &num , line_num)) != 0 )
    {
        if( !(dest==1 && opcode != 12) ) /* only 'prn' (opcode 12) addressing method 1 */
            return create_opcode_word_1_operands(head , opcode , dest ,num , line_num , operand);
    }
    
    print_error( INVALID_OPCODE_OPERAND , line_num);
    return false;
}


/* 0 operands */

bool create_opcode_word_0_operands(opcode_word** opcode_img , int opcode , int line_num) 
{
    opcode_word* new_node = malloc_opcode_word_with_check();
    int L = 0;
    create_first_opcode_word( new_node , opcode , 0 , 0 , L);
    
    new_node->L = ++L;
    new_node->operand3_dec_value=0;
    
    return insert_opcode_word( opcode_img , new_node);
}


bool line_processing_opcode_0_operands(int opcode , char* current_word , int line_num , opcode_word** opcode_img)
{
    current_word = strtok(NULL , WHITE_TABS);
       
    if(current_word == NULL)
    {
        if(create_opcode_word_0_operands(opcode_img , opcode , line_num))
            return true;     
    }
    else
        print_error( EXTRANEOUS_TEXT , line_num); 
           
    return false;   
}


int create_operand13_opcode_word(opcode_word* new_node , int value , int adrress , int L , char* operand)
{
    if(adrress == 1)
    {
        new_node->bits[L].operand13.ARE = 0;
        new_node->bits[L].operand13.value = value;
        return 0;
    }
    
    /* adrress == 3 */ 
    new_node->bits[L].operand13.ARE = 0;
    new_node->bits[L].operand13.value = 0;
    new_node->to_complete = L;
    new_node->label_name = operand;
    return IC+L ;
}


void create_first_opcode_word(opcode_word* new_node , int opcode , int source , int dest , int L)
{
    new_node->bits[L].first_word.ARE = 0;
    new_node->bits[L].first_word.opcode = opcode;
    new_node->bits[L].first_word.dest = dest;
    new_node->bits[L].first_word.source = source;
}


void create_operand5_opcode_word(opcode_word* new_node , int source_reg , int dest_reg , int L)
{
    new_node->bits[L].operand5.ARE = 0;
    new_node->bits[L].operand5.source_reg = source_reg;
    new_node->bits[L].operand5.dest_reg = dest_reg;
}


bool line_processing_opcode_2_operands(int opcode , char* current_word ,  char line[] , int line_num , opcode_word** head)
{
    char *first_operand , *second_operand , *first_comma , *last_comma;
    char *copy_line = malloc_with_check(strlen(line));
    strcpy(copy_line , line);
    line = strstr(line, opcodes[opcode])+strlen(opcodes[opcode]);
    current_word=strtok(line , WHITE_TABS);
    
    if(current_word != NULL)
    {
        first_comma = strchr(copy_line, ',');
        last_comma = strrchr(copy_line, ',');
        
        if(first_comma != NULL)
        {
            if(last_comma == first_comma)
            {
                current_word = strstr( copy_line ,  opcodes[opcode] ) + 3;
                first_operand = strtok(current_word, " \n\t,");
                second_operand = strtok(NULL, " \n\t,");
                
                if(second_operand != NULL && first_operand!=NULL)
                {
                    if( strtok(NULL, " \n\t,") == NULL)
                    {
                        if(check_2_operands(opcode , first_operand , second_operand , line_num , head));
                        {
                            free(copy_line);
                            return true;
                        }
                    }
                    else
                        print_error(EXTRANEOUS_TEXT , line_num);
                }
                else
                    print_error(MISSING_OPERAND , line_num);
            } 
            else
              print_error(EXTRA_COMMA , line_num);       
        }
        else
            print_error(MISSING_COMA , line_num);
    }
    else
        print_error( MISSING_OPERAND , line_num); 
          
    free(copy_line);
    return false;
}


bool check_2_operands(int opcode , char* first_operand , char* second_operand , int line_num , opcode_word** head)
{
    int dest , source , dest_num , source_num;
    
    source = address_type(first_operand , &source_num , line_num);
    dest = address_type(second_operand , &dest_num , line_num);
    
    if( (dest != 0 && source != 0) && (!(dest == 3 && source == 3)) && (!(opcode==6 && source!=3)) && (!(opcode!=1 && dest==1)) ) /* valid operands types (1,3 or 5 type) && the operands can`t be both labels && 
                                                                                                                                checking that the opcode receives an appropriate addressing method */
    {
            return create_opcode_word_2_operands(head , opcode , source , dest , source_num , dest_num , line_num , first_operand , second_operand);
    }
    
    print_error(INVALID_OPCODE_OPERAND , line_num );
    return false;
}


bool create_opcode_word_2_operands(opcode_word** opcode_img , int opcode , int source , int dest , int source_num , int dest_num , int line_num , char* first_operand , char* second_operand)
{
    opcode_word* new_node = malloc_opcode_word_with_check();
    int L=0 , operand3_dec_value=0;
    create_first_opcode_word(new_node , opcode , source , dest , L++); 
    
    if( source==5 && dest==5)
        create_operand5_opcode_word(new_node , source_num , dest_num , L++);
    
    else 
    {
        if( source == 5)
            create_operand5_opcode_word(new_node , source_num , 0 , L++);
        else
            operand3_dec_value = create_operand13_opcode_word(new_node , source_num , source , L++ , first_operand);
         
        if( dest == 5)
            create_operand5_opcode_word(new_node , 0 , dest_num , L++);
        else
            operand3_dec_value = create_operand13_opcode_word(new_node , dest_num , dest , L++ , second_operand); 
    }
    
    new_node->operand3_dec_value = operand3_dec_value; 
    new_node->L = L;
    new_node->line_num = line_num;
    
    return insert_opcode_word( opcode_img , new_node);
}


bool complete_encoding_opcode_image(opcode_word* opcode_img , labelHashTable* label_table , fileData** ext_table)
{
    opcode_word* current_opcode_img = opcode_img;
    labelNode* current_label = NULL;
    
    while (current_opcode_img != NULL) 
    {
        if( current_opcode_img->to_complete != 0 )
        {
            if( ( current_label = lookup_label(label_table , current_opcode_img->label_name ) ) != NULL)
            {
                if( current_label->type == EXTERNAL) /* external label */
                {
                    current_opcode_img->bits[ current_opcode_img->to_complete ].operand13.ARE = 1;
                    insert_file_data(ext_table , current_opcode_img->label_name , current_opcode_img->operand3_dec_value);
                }
                else
                    current_opcode_img->bits[ current_opcode_img->to_complete ].operand13.ARE = 2; 
                     
                current_opcode_img->bits[ current_opcode_img->to_complete ].operand13.value = current_label->dec_value ;  
            }
            else
            {
                print_error( LABEL_NOT_DECLARED , current_opcode_img->line_num);
                return false;
            } 
        }
        current_opcode_img = current_opcode_img->next;
    }
    return true;
}


void free_opcode_word(opcode_word* opcode_img) 
{
    opcode_word* current = NULL;
    
    while (opcode_img != NULL) 
    {
        current = opcode_img;
        opcode_img = opcode_img->next;
        free(current); 
    }
}

