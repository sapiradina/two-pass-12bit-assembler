#ifndef WRITE_FILWS_H
#define WRITE_FILWS_H

#include "ICimage.h"
#include "DCimage.h"

/* A function that manages the process of writing the output files .ext , .ent and .ob */
/* If the files were created successfully, true will be returned. Otherwise - false */
bool write_files(char* source_file_name , FILE* am_file ,  data_word* data_img , opcode_word* opcode_img , labelHashTable* label_table , fileData* ext_table , fileData* ent_table);

/* A function that gets a entry-labels table and writes the .ent file. */
/* If the file were created successfully, true will be returned. Otherwise - false */
bool write_ent_file(char* source_file_name , fileData* ent_table);

/* A function that gets a external-labels table and writes the .ext file. */
/* If the file were created successfully, true will be returned. Otherwise - false */
bool write_ext_file(char* source_file_name , fileData* ext_table);

/* A function that gets data and opcode images and writes the .ob file. */
/* If the file were created successfully, true will be returned. Otherwise - false */
bool write_ob_file(char* source_file_name , data_word* data_img , opcode_word* opcode_img);

/* A function that gets a pointer to an opcode machine-word and file, and writes the word in the file. */
void convert_opcode_word_to_Base64(opcode_word* opcode_ptr , FILE** ob_file);

/* A function that gets a pointer to an opcode word, i which is the position of a certain word in the bits[] of the opcode word */
/* and source_or_dest which is an address method. Based on this data, a 12-bit word will be created and returned. */
unsigned int make_operand_word(int source_or_dest , int i , opcode_word* opcode_ptr);

#endif

