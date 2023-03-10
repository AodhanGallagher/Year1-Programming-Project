/* pgmComp: A module to compare two pgm files to test if they are logically equivalent. */

//Including relevant libraries and modules
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"
#include "pgmComp.h"
#include "pgmRead.h"

// Function used to compare the two pgm structs, it returns 1 if they don't match and returns 0 if they do match
int pgmCompareImages(pgmImage *pgm1, pgmImage *pgm2) {
    // Compares the magic number
    if ((pgm1->magicNumberArray[0] != pgm2->magicNumberArray[0]) && (pgm1->magicNumberArray[1] != pgm2->magicNumberArray[1])) {
        return 1;
    } 

    // Compares the width
    if (pgm1->width != pgm2->width) {
        return 1;
    }

    // Compares the height
    if (pgm1->height != pgm2->height) {
        return 1;
    }

    // Compares the maxGray value
    if (pgm1->maxGray != pgm2->maxGray) {
        return 1;
    }

    // Compares the image data
    if (memcmp(pgm1->imageData, pgm2->imageData, pgm1->nImageBytes) != 0) {
        return 1;
    }

    // Returns 0 if the two pgm structs are identical
    return 0;
}

// Main function used to compare two pgm files
int main(int argc, char **argv) {
    // Checks if no arguments have been supplied in the command line and prints correct usage
    if (argc == 1) {
        printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
        return EXIT_NO_ERRORS;
    }
    // Checks to see if the correct number of arguments have been supplied
    else if (argc != 3) {
        printf("ERROR: Bad Argument Count\n");
        return EXIT_BAD_ARG_COUNT;
    }

    // Creates a first struct, allocates the size of the struct and initializes the struct
    pgmImage *pgm1 = NULL;
    pgm1 = (pgmImage *) malloc (sizeof(pgmImage));
    initializePgmStruct(pgm1);

    /* Opens the first input file and passes it into the pgmRead function for reading the input file.
        The pgmRead function's return value is saved to an integer variable for error checking. */
    FILE *inputFile1 = fopen(argv[1], "r");
    int readError1 = pgmRead(inputFile1, pgm1, argv[1]);

    // Returns the appropriate message and error code upon a bad file name
    if (readError1 == EXIT_BAD_FILE_NAME) {
        printf("ERROR: Bad File Name (%s)\n", argv[1]);
        return EXIT_BAD_FILE_NAME;
    }

    // Returns the appropriate message and error code upon a bad magic number
    if (readError1 == EXIT_BAD_MAGIC_NO) {
        printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
        return EXIT_BAD_MAGIC_NO;
    }

    // Returns the appropriate message and error code upon a bad comment line
    if (readError1 == BAD_COMMENT_LINE) {
        printf("ERROR: Bad Comment Line (%s)\n", argv[1]);
        return BAD_COMMENT_LINE;
    }

    // Returns the appropriate message and error code upon bad dimensions
    if (readError1 == BAD_DIMENSIONS) {
        printf("ERROR: Bad Dimensions (%s)\n", argv[1]);
        return BAD_DIMENSIONS;
    }

    // Returns the appropriate message and error code upon a bad max gray value
    if (readError1 == BAD_MAX_GRAY_VALUE) {
        printf("ERROR: Bad Max Gray Value (%s)\n", argv[1]);
        return BAD_MAX_GRAY_VALUE;
    }

    // Returns the appropriate message and error code if the image malloc fails
    if (readError1 == IMAGE_MALLOC_FAILED) {
        printf("ERROR: Image Malloc Failed\n");
        return IMAGE_MALLOC_FAILED;
    }
    
    // Returns the appropriate message and error code upon bad data values
    if (readError1 == BAD_DATA) {
        printf("ERROR: Bad Data (%s)\n", argv[1]);
        return BAD_DATA;
    }

    // Creates a second struct, allocates the size of the struct and initializes the struct
    pgmImage *pgm2 = NULL;
    pgm2 = (pgmImage *) malloc (sizeof(pgmImage));
    initializePgmStruct(pgm2);

    /* Opens the second input file and passes it into the pgmRead function for reading the input file.
        The pgmRead function's return value is saved to an integer variable for error checking. */
    FILE *inputFile2 = fopen(argv[2], "r");
    int readError2 = pgmRead(inputFile2, pgm2, argv[2]);

    // Returns the appropriate message and error code upon a bad file name
    if (readError1 == EXIT_BAD_FILE_NAME) {
        printf("ERROR: Bad File Name (%s)\n", argv[2]);
        return EXIT_BAD_FILE_NAME;
    }

    // Returns the appropriate message and error code upon a bad magic number
    if (readError2 == EXIT_BAD_MAGIC_NO) {
        printf("ERROR: Bad Magic Number (%s)\n", argv[2]);
        return EXIT_BAD_MAGIC_NO;
    }

    // Returns the appropriate message and error code upon a bad comment line
    if (readError2 == BAD_COMMENT_LINE) {
        printf("ERROR: Bad Comment Line (%s)\n", argv[2]);
        return BAD_COMMENT_LINE;
    }

    // Returns the appropriate message and error code upon bad dimensions
    if (readError2 == BAD_DIMENSIONS) {
        printf("ERROR: Bad Dimensions (%s)\n", argv[2]);
        return BAD_DIMENSIONS;
    }

    // Returns the appropriate message and error code upon a bad max gray value
    if (readError2 == BAD_MAX_GRAY_VALUE) {
        printf("ERROR: Bad Max Gray Value (%s)\n", argv[2]);
        return BAD_MAX_GRAY_VALUE;
    }

    // Returns the appropriate message and error code if the image malloc fails
    if (readError2 == IMAGE_MALLOC_FAILED) {
        printf("ERROR: Image Malloc Failed\n");
        return IMAGE_MALLOC_FAILED;
    }
    
    // Returns the appropriate message and error code upon bad data values
    if (readError2 == BAD_DATA) {
        printf("ERROR: Bad Data (%s)\n", argv[2]);
        return BAD_DATA;
    }

    // Runs pgmCompareImages and tests the return value to see if the two files are identcial or different
    if (pgmCompareImages(pgm1, pgm2) == 0) {
        printf("IDENTICAL\n");
        return EXIT_NO_ERRORS;
    }
    else if (pgmCompareImages(pgm1, pgm2) == 1) {
        printf("DIFFERENT\n");
        return EXIT_NO_ERRORS;
    }

    /* This triggers if there was a problem when comparing files (and the previous if statements did not trigger).
        An error message is printed and an error value is returned. */
    printf("ERROR: Miscellaneous (A problem has occurred when comparing pgm files)\n");
    return MISCELLANEOUS;
}