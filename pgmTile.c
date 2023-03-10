/* pgmTile.c: A module to divide an input pgm file into nxn smaller images corresponding to parts of the original image. */

/* This module has not been fully completed due to time constraints, however,
    implementation has begun and basic error checking has been added. */

//Including relevant libraries and modules.
#include <stdio.h>
#include <stdlib.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"
#include "pgmTile.h"
#include "pgmRead.h"
#include "pgmWrite.h"

// Main function used to divide the file
int main(int argc, char **argv) {
    // Checks if no arguments have been supplied in the command line and prints correct usage
    if (argc == 1) {
        printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n", argv[0]);
        return EXIT_NO_ERRORS;
    }
    // Checks to see if 2 arguments have been supplied
    else if (argc == 2) {
        printf("ERROR: Bad Argument Count (%s)\n", argv[0]);
        return EXIT_BAD_ARG_COUNT;
    }
    // Checks to see if the correct number of arguments have been supplied
    else if (argc != 4) {
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
    int readError = pgmRead(inputFile, pgm, argv[1]);

    // Returns the appropriate message and error code upon a bad file name
    if (readError == EXIT_BAD_FILE_NAME) {
        printf("ERROR: Bad File Name (%s)\n", argv[1]);
        return EXIT_BAD_FILE_NAME;
    }

    // Returns the appropriate message and error code upon a bad magic number
    if (readError == EXIT_BAD_MAGIC_NO) {
        printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
        return EXIT_BAD_MAGIC_NO;
    }

    // Returns the appropriate message and error code upon a bad comment line
    if (readError == BAD_COMMENT_LINE) {
        printf("ERROR: Bad Comment Line (%s)\n", argv[1]);
        return BAD_COMMENT_LINE;
    }

    // Returns the appropriate message and error code upon bad dimensions
    if (readError == BAD_DIMENSIONS) {
        printf("ERROR: Bad Dimensions (%s)\n", argv[1]);
        return BAD_DIMENSIONS;
    }

    // Returns the appropriate message and error code upon a bad max gray value
    if (readError == BAD_MAX_GRAY_VALUE) {
        printf("ERROR: Bad Max Gray Value (%s)\n", argv[1]);
        return BAD_MAX_GRAY_VALUE;
    }

    // Returns the appropriate message and error code if the image malloc fails
    if (readError == IMAGE_MALLOC_FAILED) {
        printf("ERROR: Image Malloc Failed\n");
        return IMAGE_MALLOC_FAILED;
    }
    
    // Returns the appropriate message and error code upon bad data values
    if (readError == BAD_DATA) {
        printf("ERROR: Bad Data (%s)\n", argv[1]);
        return BAD_DATA;
    }

    /* Creates an output file and passes it into the pgmWrite function to write the output file.
        The pgmWrite function's return value is saved to an integer variable for error checking. */
    FILE *outputFile = fopen(argv[2], "w");
    int writeError = pgmWrite(outputFile, pgm, argv[3]);

    // Returns the appropriate message and error code if the output fails
    if (writeError == OUTPUT_FAILED) {
        printf("ERROR: Output Failed (%s)\n", argv[3]);
        return OUTPUT_FAILED;
    }

    // Prints a message and returns 0 to indicate there were no errors and the program ran successfully
    printf("TILED\n");
    return EXIT_NO_ERRORS;
}