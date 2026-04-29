#include "main.h"

int main(int argc, char *argv[]) 
{
    int i;

    if (argc == 1) /* if the user has not entered source files on the command line */
    { 
        print_error(MISSING_FILE_NAME,0);
        return (1);
    }

    for (i = 1 ; i < argc ; i++) /* running the assembler on the source files entered by the user */
    {
        printf("\nfile %s:\n" , argv[i]);
        process_file(argv[i]); 
    }

    return (0);
}


void process_file(char* source_file_name) 
{
    FILE* am_file = NULL;
    bool error_passes_flag = false; /* error flag that turned to 'true' if an error is found during the run */
    data_word data_img[MEMORY_SIZE]; /* the data of the data&string words machine */
    opcode_word* opcode_img = NULL; /* the data of the opcode words machine */
    labelHashTable* label_table = malloc(sizeof(labelHashTable)); /* the data of the declared labels */
    fileData* ext_table = NULL; /* information for the ext.file - all places in memory where the external labels was used in opcode */
    fileData* ent_table = NULL; /* information for the ent.file - all places in memory where the entry labels was declared */
    
    if (label_table == NULL) 
    {
        print_error(MEMORY_FAILED , 0);
        exit(1);
    }
    
    if(!pre_assembler(source_file_name , &am_file , &error_passes_flag)) /* pre-assembler and writing the .am file */
    { 
        first_pass(am_file , data_img , &opcode_img , &label_table , &error_passes_flag); /* first pass */
        second_pass(am_file , data_img , &opcode_img , &label_table , &error_passes_flag , &ent_table , &ext_table);  /* second pass */
                      
        if(error_passes_flag)
            printf("\nDue to the error/s during the .am file processing, the .ob, .ext and .ent files creation failed.\n");
            
        else if(write_files(source_file_name , am_file ,  data_img , opcode_img , label_table , ext_table , ent_table)) /* writing the .ob , .ext , .ent files */
            printf("\nFile '%s' successfully compiled !\n", source_file_name);
            
        else
        {
            printf("\nSystem error - .ob, .ext and .ent files creation failed.\n");
            exit(1);
        }    
    }
    
    else
        printf("\nDue to the error/s during the pre assembler, the .am file creation failed.\n");
    
    /* Freeing memory from the structures */
    free_opcode_word(opcode_img);
    free_label(&label_table);
    free_file_data(ext_table);
    free_file_data(ent_table);
}

