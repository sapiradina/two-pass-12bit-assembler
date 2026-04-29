#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "ICimage.h"
#include "DCimage.h"

/* A function that manages the second pass */
void second_pass(FILE* am_file ,  data_word* data_img , opcode_word** opcode_img , labelHashTable** label_table , bool* error_passes_flag , fileData** ent_table , fileData** ext_table);

#endif
