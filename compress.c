#include <stdlib.h>
#include <string.h>
#include "compress.h"

void text_to_binary(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r"); // Open input file
    FILE *outputFile = fopen(outputFileName, "wb"); // Open output file

    // If error occurred
    if (!inputFile || !outputFile) {
        printf("Error opening file.\n");
        if (inputFile) fclose(inputFile);
        return;
    }

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (ch >= '0' && ch <= '9') {
            int digit = ch - '0'; // Convert char to int
            int binaryRepresentation = 15 - digit; // Calculate the binary representation

            // Write to binary file in our format
            for (int i = 3; i >= 0; i--) { // Write each bit of the 4-bit binary representation
                char bit = (binaryRepresentation & (1 << i)) ? '1' : '0';
                fwrite(&bit, sizeof(char), 1, outputFile);
            }
        }
    }

    // If the text file is i a odd number
    if(getFileSize(inputFile) % 2 == 1){
        for(int i = 0; i < 4; i++){
            char zero = '0';
            fwrite(&zero, sizeof(char), 1, outputFile);
        }
    }

    // Closing the files
    fclose(inputFile);
    fclose(outputFile);
}

void binary_to_text(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "rb"); // Open input file
    FILE *outputFile = fopen(outputFileName, "w"); // open output file

    // If error occurred
    if (!inputFile || !outputFile) {
        printf("Error opening file.\n");
        if (inputFile) fclose(inputFile);
        return;
    }

    char binary[5]; // Buffer to hold each 4-bit binary representation as a string
    while (fread(binary, sizeof(char), 4, inputFile) == 4) {
        binary[4] = '\0'; // Null-terminate the string

        int decimal = strtol(binary, NULL, 2); // Convert binary string to decimal
        decimal = 15 - decimal; // Reverse the transformation

        // If we are not got 4 zeroes
        if(decimal != 15){
            fprintf(outputFile, "%d", decimal); // Write the digit
        }
    }

    // Closing the files
    fclose(inputFile);
    fclose(outputFile);
}

char* deepCopyString(const char* original) {
    // Calculate the length of the original string
    size_t length = strlen(original);

    // Allocate memory for a new string
    char* newString = (char*)malloc((length + 1) * sizeof(char));

    if (newString == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Copy the original string to the new memory location
    strcpy(newString, original);

    return newString;
}


// Helper function to get file size
int getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}


