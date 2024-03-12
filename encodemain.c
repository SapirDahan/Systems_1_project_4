#include <string.h>
#include <stdlib.h>
#include "compress.h"


int main(int argc, char *argv[]){

    // If we didn't get 3 arguments
    if(argc != 3){
        exit(1);
    }

    char* flag = argv[1]; // The flag we got
    char* file_name = argv[2]; // the name of the file we got

    int length = strlen(file_name);
    char *start_file_type_index = file_name + length - 3;

    // The file type
    char *file_type = start_file_type_index;

    // If it is txt
    if(strcmp(file_type,"txt") == 0){

        // Must be flag -c
        if(strcmp(flag,"-c") != 0){
            exit(1);
        }

        // Create a new string that replace txt to bin
        char* file_name_txt = deepCopyString(file_name);
        strcpy(start_file_type_index, "bin");

        // Calling the function
        text_to_binary(file_name_txt, file_name);
    }

    // If it is bin
    if(strcmp(file_type,"bin") == 0){

        // the flag must be -d
        if(strcmp(flag,"-d") != 0){
            exit(1);
        }

        // Changing the ending of the file from bin to txt
        char* file_name_txt = deepCopyString(file_name);
        strcpy(start_file_type_index, "txt");

        // Calling the function
        binary_to_text(file_name_txt, file_name);
    }
}