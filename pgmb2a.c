/* pgmb2a: A module to convert binary pgm files to ASCII pgm files */

//Including relevant libraries and modules
#include <stdio.h>
#include <stdlib.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"
#include "pgmb2a.h"
#include "pgmRead.h"
#include "pgmWrite.h"

// Main function used to convert binary pgm files to ASCII pgm files
int main(int argc, char **argv) {
    // Checks if no arguments have been supplied in the command line and prints correct usage
    if (argc == 1) {
        printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
        return EXIT_NO_ERRORS;
    }
    // Checks to see if the correct number of arguments have been supplied
    else if (argc != 3) {
        printf("ERROR: Bad Argument Count (%s)\n", argv[0]);
        return EXIT_BAD_ARG_COUNT;
    }

    // Creates a struct, allocates the size of the struct and initializes the struct
    pgmImage *pgmb2a = NULL;
    pgmb2a = (pgmImage *) malloc (sizeof(pgmImage));
    initializePgmStruct(pgmb2a);

    /* Opens the input file and passes it into the pgmRead function for reading the input file.
        The pgmRead function's return value is saved to an integer variable for error checking. */
    FILE *inputFile = fopen(argv[1], "rb");
    int readError = pgmRead(inputFile, pgmb2a, argv[1]);

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

    // Triggers if the magic number is 'P5'
    if (pgmb2a->magicNumberArray[1] == '5') {
        // Changes the magic number to be 'P2'
        pgmb2a->magicNumberArray[1] = '2';
        
        /* Creates an output file and passes it into the pgmWrite function to write the output file.
            The pgmWrite function's return value is saved to an integer variable for error checking. */
        FILE *outputFile = fopen(argv[2], "w");
        int writeError = pgmWrite(outputFile, pgmb2a, argv[2]);

        // Returns the appropriate message and error code if the output fails
        if (writeError == OUTPUT_FAILED) {
            printf("ERROR: Output Failed (%s)\n", argv[2]);
            return OUTPUT_FAILED;
        }
    }
    else {
        printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
        return EXIT_BAD_MAGIC_NO;
    }

    // Prints a message and returns 0 to indicate there were no errors and the program ran successfully
    printf("CONVERTED\n");
    return EXIT_NO_ERRORS;
}