#ifndef MAIN_H
#define MAIN_H

#include "preAssembler.h"
#include "firstPass.h"
#include "secondPass.h"
#include "writeFiles.h"

/* A function that receives a source file from the user and manages all the steps of the assembler */
void process_file(char* source_file_name) ;

#endif

