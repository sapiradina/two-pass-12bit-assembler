#include "general.h"

int DC,IC;

const char* registers[REGISTERS_NUM] = {"@r0", "@r1", "@r2", "@r3",
                                        "@r4", "@r5", "@r6", "@r7"};

const char* opcodes[OPCODE_WORDS_NUM] = {"mov" , "cmp" , "add" , "sub" , "not" , "clr" , "lea" , "inc" , 
                                        "dec" , "jmp" , "bne" , "red" , "prn" , "jsr" , "rts" , "stop"};

const char* directive[DIRECTIVE_WORDS_NUM] = {".data" , ".string" , ".entry" , ".extern"}; 

 
