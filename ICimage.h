#ifndef IC_IMAGE_H
#define IC_IMAGE_H

#include "label.h"
#include "fileData.h"
#include "utils.h"

/* the first code word of a machine opcode word */
typedef struct first_machine_word
{
    unsigned int ARE : 2;
    unsigned int dest : 3;
    unsigned int opcode : 4;
    unsigned int source : 3;
}first_machine_word;

/* code word of operand from address 1 or 3 (immediately or directly) */
typedef struct immediate_or_direct_address 
{
    unsigned int ARE : 2;
    unsigned int value : 10;
}immediate_or_direct_address;


/* code word of operand from address 5 (register) */
typedef struct register_address
{
    unsigned int ARE : 2;
    unsigned int dest_reg : 5;
    unsigned int source_reg : 5;
}register_address;


/* A machine opcode word */
typedef struct opcode_word
{
    struct opcode_word *next;
    int to_complete ; /* If completion of the opcode word is required in the second pass - save the location at bits[] of the current word (1 or 2). otherwise - 0 */
    char* label_name;/* If completion of the opcode word is required in the second pass - save the label name. otherwise - NULL */
    int line_num; /* If completion of the opcode word is required in the second pass - save the line number. otherwise - 0 */
    int operand3_dec_value; /* If completion of the opcode word is required in the second pass - save the decimal value of the edrress of the current word. otherwise - 0 */
    
    union
    {
        first_machine_word first_word;
        immediate_or_direct_address operand13;
        register_address operand5;
    } bits[3];
    int L; /* number of words in the opcode word machine (1,2 or 3) */
     
}opcode_word;


/* A function to allocate memory for opcode_word and return it. If the memory allocation failed, NULL will be returned */
opcode_word* malloc_opcode_word_with_check();

/* A function that analyzes a line that has an .entry or .extern command. the label\s in this line will be saved\updated in the label table. */
void is_proper_external_or_entry(char* current_word , char line[] , int line_num , bool *flag_error , labelHashTable** label_table , labelType ext_or_ent , fileData** ent_table);

/* A function that gets code-line with opcode name, and routes it to the corresponding analysis function according to the number of its operands. */
/* If the line has been processed successfully, true will be returned. Otherwise - false.*/
bool is_proper_opcode(char* current_word ,  char line[] , int line_num , opcode_word** opcode_img);

/* A function that inserts the opcode-word to the opcode-image */
bool insert_opcode_word(opcode_word** opcode_img , opcode_word* img_new_node);

/* A function that gets an operand and returns the number of its addressing method (1,3 or 5). If the operand is not correct, 0 will be returned. */
/* In addition, num will be updated to a value according to the addressing method: */
/*at address 1 num the will be updated to the number represented by the operand. At address 5 num will be updated to the register number. At address 3 num will not be updated. */
int address_type(char* operand , int* num , int line_num);

/* A function that checks the general integrity of a line of opcode with 0 operands. */
/* If it is correct, the function sends data for further processing. Otherwise - false will be returned.*/
bool line_processing_opcode_0_operands(int opcode , char* current_word , int line_num , opcode_word** opcode_img);

/* A function that creates an opcode word for opcodes without operands. */
bool create_opcode_word_0_operands(opcode_word** opcode_img , int opcode , int line_num);

/* A function that checks the general integrity of a line of opcode with one operand. */
/* If it is correct, the function sends the operand for further processing. Otherwise - false will be returned.*/
bool line_processing_opcode_1_operands(int opcode , char* current_word , char line[] , int line_num , opcode_word** head);

/* A function that checks if the addressing methods of the operands are valid, for instructions with two operands. */
bool check_1_operands(int opcode , char* operand , int line_num , opcode_word** head);

/* A function that creates an opcode word for opcodes with two operands. */
bool create_opcode_word_1_operands(opcode_word** opcode_img , int opcode , int dest , int num , int line_num , char* operand);
 
/* A function that checks the general integrity of a line of opcode with two operands. */
/* If it is correct, the function sends the operands for further processing. Otherwise - false will be returned.*/
bool line_processing_opcode_2_operands(int opcode , char* current_word ,  char line[] , int line_num , opcode_word** head);

/* A function that checks if the addressing methods of the operands are valid, for instructions with one operand. */
bool check_2_operands(int opcode , char* first_operand , char* second_operand , int line_num , opcode_word** head);

/* A function that creates an opcode word for opcodes with one operand. */
bool create_opcode_word_2_operands(opcode_word** opcode_img , int opcode , int source , int dest , int source_num , int dest_num , int line_num , char* first_operand , char* second_operand);

/* A function that creates the first_word of an opcode word machine. */
void create_first_opcode_word(opcode_word* new_node , int opcode , int source , int dest , int L);

/* A function that creates the operand13 of an opcode word machine. */
int create_operand13_opcode_word(opcode_word* new_node , int value , int adrress , int L , char* operand);

/* A function that creates the operand5 of an opcode word machine. */
void create_operand5_opcode_word(opcode_word* new_node , int source_reg , int dest_reg , int L);

/* A function that completes the opcode image, in the words that had labels that we didn't know if they were entry or external. */
/* In addition, the external-labels table will be filled. If everything was done successfully, true will be returned. Otherwise - false. */
bool complete_encoding_opcode_image(opcode_word* opcode_img , labelHashTable* label_table , fileData** ext_table);

/* A function that frees memory allocated to opcode image */
void free_opcode_word(opcode_word* opcode_img);

#endif
