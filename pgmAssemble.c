/* pgmAssemble.c: A module to assemble a large pgm image from smaller ones. */

/* This module has not been fully completed due to time constraints, however,
    implementation has begun and basic error checking has been added. */

//Including relevant libraries and modules.
#include <stdio.h>
#include <stdlib.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"
#include "pgmAssemble.h"
#include "pgmRead.h"
#include "pgmWrite.h"

// Main function used to assemble the image
int main(int argc, char **argv) {
    // Checks if no arguments have been supplied in the command line and prints correct usage
    if (argc == 1) {
        printf("Usage: %s outputImage.pgm width height (row column inputImage.pgm)+\n", argv[0]);
        return EXIT_NO_ERRORS;
    }

    // Checks to see if the correct number of arguments have been supplied
    else if (argc != 6) {
        printf("ERROR: Bad Argument Count (%s)\n", argv[0]);
        return EXIT_BAD_ARG_COUNT;
    }

    // Creates a struct, allocates the size of the struct and initializes the struct
    pgmImage *pgm = NULL;
    pgm = (pgmImage *) malloc (sizeof(pgmImage));
    initializePgmStruct(pgm);

    /* Opens the input file and passes it into the pgmRead function for reading the input file.
        The pgmRead function's return value is saved to an integer variable for error checking. */
    FILE *inputFile = fopen(argv[1], "rb");
    int readError = pgmRead(inputFile, pgm, argv[6]);

    // Returns the appropriate message and error code upon a bad file name
    if (readError == EXIT_BAD_FILE_NAME) {
        printf("ERROR: Bad File Name (%s)\n", argv[6]);
        return EXIT_BAD_FILE_NAME;
    }

    // Returns the appropriate message and error code upon a bad magic number
    if (readError == EXIT_BAD_MAGIC_NO) {
        printf("ERROR: Bad Magic Number (%s)\n", argv[6]);
        return EXIT_BAD_MAGIC_NO;
    }

    // Returns the appropriate message and error code upon a bad comment line
    if (readError == BAD_COMMENT_LINE) {
        printf("ERROR: Bad Comment Line (%s)\n", argv[6]);
        return BAD_COMMENT_LINE;
    }

    // Returns the appropriate message and error code upon bad dimensions
    if (readError == BAD_DIMENSIONS) {
        printf("ERROR: Bad Dimensions (%s)\n", argv[6]);
        return BAD_DIMENSIONS;
    }

    // Returns the appropriate message and error code upon a bad max gray value
    if (readError == BAD_MAX_GRAY_VALUE) {
        printf("ERROR: Bad Max Gray Value (%s)\n", argv[6]);
        return BAD_MAX_GRAY_VALUE;
    }

    // Returns the appropriate message and error code if the image malloc fails
    if (readError == IMAGE_MALLOC_FAILED) {
        printf("ERROR: Image Malloc Failed\n");
        return IMAGE_MALLOC_FAILED;
    }
    
    // Returns the appropriate message and error code upon bad data values
    if (readError == BAD_DATA) {
        printf("ERROR: Bad Data (%s)\n", argv[6]);
        return BAD_DATA;
    }

    /* Creates an output file and passes it into the pgmWrite function to write the output file.
         The pgmWrite function's return value is saved to an integer variable for error checking. */
    FILE *outputFile = fopen(argv[2], "w");
    int writeError = pgmWrite(outputFile, pgm, argv[1]);

    // Returns the appropriate message and error code if the output fails
    if (writeError == OUTPUT_FAILED) {
        printf("ERROR: Output Failed (%s)\n", argv[1]);
        return OUTPUT_FAILED;
    }

    // Prints a message and returns 0 to indicate there were no errors and the program ran successfully
    printf("ASSEMBLED\n");
    return EXIT_NO_ERRORS;
}