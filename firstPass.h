#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "DCimage.h"
#include "ICimage.h"

/* A function that manages the first pass */
void first_pass(FILE* am_file , data_word* data_img , opcode_word** opcode_img , labelHashTable** label_table , bool* error_passes_flag);

#endif
