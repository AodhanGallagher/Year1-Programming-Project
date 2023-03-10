/* pgmReduce.c: A module to reduce an input pgm file by a stated factor in each dimension. */

//Including relevant libraries and modules.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"
#include "pgmReduce.h"
#include "pgmRead.h"
#include "pgmWrite.h"

// Main function used to reduce the file
int main(int argc, char **argv) {
    // Checks if no arguments have been supplied in the command line and prints correct usage
    if (argc == 1) {
        printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
        return EXIT_NO_ERRORS;
    }

    // Checks to see if the correct number of arguments have been supplied
    else if (argc != 4) {
        printf("ERROR: Bad Argument Count (%s)\n", argv[0]);
        return EXIT_BAD_ARG_COUNT;
    }

    // Converts the input factor from a string to a character
    char reductionFactorChar = *(argv[2]);

    // Error checking to check if the factor is non-numeric
    if (isdigit(reductionFactorChar) == 0) {
        printf("ERROR: Miscellaneous (Reduction factor must be numerical)\n");
        return MISCELLANEOUS;
    }

    // Converts the input factor from a string to an integer
    int reductionFactor = atoi(argv[2]);

    // Error checking to check that the factor is not negative (0 or above)
    if (reductionFactor < 0) {
        printf("ERROR: Miscellaneous (Reduction factor cannot be a negative value)\n");
        return MISCELLANEOUS;
    }

    // Creates a struct, allocates the size of the struct and initializes the struct
    pgmImage *pgmOriginal = NULL;
    pgmOriginal = (pgmImage *) malloc (sizeof(pgmImage));
    initializePgmStruct(pgmOriginal);

    /* Opens the input file and passes it into the pgmRead function for reading the input file.
        The pgmRead function's return value is saved to an integer variable for error checking. */
    FILE *inputFile = fopen(argv[1], "rb");
    int readError = pgmRead(inputFile, pgmOriginal, argv[1]);

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

    // Creates a struct, allocates the size of the struct and initializes the struct
    pgmImage *pgmReduced = NULL;
    pgmReduced = (pgmImage *) malloc (sizeof(pgmImage));
    initializePgmStruct(pgmReduced);

    // Calculates and sets the height and width of the reduced pgm image structure
    pgmReduced->height = (pgmOriginal->height + reductionFactor - 1) / reductionFactor;
    pgmReduced->width = (pgmOriginal->width + reductionFactor - 1) / reductionFactor;

    // Allocates the data pointer and assigns it to the array in the reduced pgm image structure
    pgmReduced->nImageBytes = pgmReduced->height * pgmReduced->width * sizeof(unsigned char);
    pgmReduced->imageData = (unsigned char *) malloc (pgmReduced->nImageBytes);

    // Sets the magic number values in the reduced pgm image structure
    pgmReduced->magicNumberArray[0] = pgmOriginal->magicNumberArray[0];
    pgmReduced->magicNumberArray[1] = pgmOriginal->magicNumberArray[1];
    pgmReduced->magicNumber = pgmOriginal->magicNumber;

    int reducedDataCount = 0; // Variable to keep count of the number of data values / gray values are in the image
    unsigned char *nextGrayValue = pgmOriginal->imageData; // Obtains the gray values from the input pgm image

    // Nested loops that iterate through the height and width of the input pgm image respectively
    for (int i = 0; i < pgmOriginal->height; i++) {
        for (int j = 0; j < pgmOriginal->width; j++) {
            /* The if statement triggers if height and width modulo the factor are equal to 0.
                This allows us to assign the gray values whilst following the recued image format. */
            if ((i % reductionFactor == 0) && (j % reductionFactor == 0)) {
                pgmReduced->imageData[reducedDataCount] = *nextGrayValue; // Assigns the next gray value to the image data of the reduced pgm file
                reducedDataCount++;
            }
            nextGrayValue++; // The next gray value is always incremented at each iteration of the loop
        }
    }

    /* Creates an output file and passes it into the pgmWrite function to write the output file.
        The pgmWrite function's return value is saved to an integer variable for error checking. */
    FILE *outputFile = fopen(argv[3], "w");
    int writeError = pgmWrite(outputFile, pgmReduced, argv[3]);

    // Returns the appropriate message and error code if the output fails
    if (writeError == OUTPUT_FAILED) {
        printf("ERROR: Output Failed (%s)\n", argv[3]);
        return OUTPUT_FAILED;
    }

    // Prints a message and returns 0 to indicate there were no errors and the program ran successfully
    printf("REDUCED\n");
    return EXIT_NO_ERRORS;
}