/* Module for reading in pgm files and storing the relevant values in a structure. */

//Including relevant libraries and modules
#include <stdio.h>
#include <stdlib.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"

// Function used to initialize the structure (that is used for storing pgm file values)
void initializePgmStruct(pgmImage *pgm) {
    pgm->magicNumberArray[0] = '0';
    pgm->magicNumberArray[1] = '0';
    pgm->magicNumber = (unsigned short *) pgm->magicNumberArray;
    pgm->commentLine = NULL;
    pgm->width = 0;
    pgm->height = 0;
    pgm->maxGray = 255;
    pgm->imageData = NULL;
    pgm->nImageBytes = 0;
}

// Function used to read in the pgm file and store the relevant values in a structure
int pgmRead(FILE *inputFile, pgmImage *pgm, char str[]) {
    // Checks if the input file exists
    if (inputFile == NULL) {
		return EXIT_BAD_FILE_NAME;
    }

    // Reads in the magic number and assigns it to the structure
    pgm->magicNumberArray[0] = getc(inputFile);
    pgm->magicNumberArray[1] = getc(inputFile);
    pgm->magicNumber = (unsigned short *) pgm->magicNumberArray; //Assigns the two array values to a single value in the struct.

    // Error checking on the magic number to ensure that it is of a correct value
    if ((pgm->magicNumberArray[0] == 'P') && ((pgm->magicNumberArray[1] == '2') || (pgm->magicNumberArray[1] == '5'))) {
        ;  // If magic number is valid, this semicolon is used to "do nothing" and skip over the if statement
    }
    else {
        fclose(inputFile);
        return EXIT_BAD_MAGIC_NO;
    }

    // Scans whitespace if present
    int scanCount = fscanf(inputFile, " ");

    // Checks for a comment line
    char nextChar = fgetc(inputFile);
	if (nextChar == '#') {
        // Allocates a buffer
        pgm->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
        // Reads a line and stores the return value
        char *commentString = fgets(pgm->commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);

        // Null means no comment was read and the memory is then freed and the file is closed
        if ((commentString == NULL) || (strlen(commentString) == MAX_COMMENT_LINE_LENGTH-1)) {
            free(pgm->commentLine);
            fclose(inputFile);
            return BAD_COMMENT_LINE;
        }
    }
    // This triggers when no comment line is present and the character is then put back
    else {
        ungetc(nextChar, inputFile);
    }

    // Reads in the width, height and maxGray values and stores them in the structure (There's whitespace to skip blanks)
    scanCount = fscanf(inputFile, " %u %u %u ", &(pgm->width), &(pgm->height), &(pgm->maxGray));

    /* Error checking on the width and height values.
        Must read three values (width, height and maxGray) and check if the width and height are within bounds. */
    if ((scanCount != 3) || (pgm->width < MIN_IMAGE_DIMENSION) || (pgm->width >= MAX_IMAGE_DIMENSION) ||
	    (pgm->height < MIN_IMAGE_DIMENSION) || (pgm->height >= MAX_IMAGE_DIMENSION)) {
            free(pgm->commentLine);
            fclose(inputFile);
            return BAD_DIMENSIONS;
    }
    
    // Checks to see that maxGray is the correct value of 255
    if (pgm->maxGray != 255) {
        free(pgm->commentLine);
        fclose(inputFile);
        return BAD_MAX_GRAY_VALUE;
    }

    // Allocates the data pointer and assigns it to the array
    pgm->nImageBytes = pgm->width * pgm->height * sizeof(unsigned char);
	pgm->imageData = (unsigned char *) malloc(pgm->nImageBytes);

    // Checks to see if the memory was correctly allocated
    if (pgm->imageData == NULL) {
        free(pgm->commentLine);
        fclose(inputFile);
        return IMAGE_MALLOC_FAILED;
    }

    // If statement triggers if the magic number is 'P2'
    if (pgm->magicNumberArray[1] == '2') {
        // Pointer for efficient read code that loops over each gray value
        for (unsigned char *nextGrayValue = pgm->imageData; nextGrayValue < pgm->imageData + pgm->nImageBytes; nextGrayValue++) {
            int grayValue = -1;
            int scanCount = fscanf(inputFile, " %u", &grayValue); // Reads the next gray value

            // Error checking to check that each gray value is read in and is within bounds
            if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255)) {
                free(pgm->commentLine);
                free(pgm->imageData);
                fclose(inputFile);
                return BAD_DATA;
            }

            // Sets the pixel value
            *nextGrayValue = (unsigned char) grayValue;
        }
        // Attempting to read the next gray value (to check for too much data)
        int grayValue = -1;
        scanCount = -1;
        scanCount = fscanf(inputFile, " %u", &grayValue); // Attempts to read the next gray value

        // Error checking which checks for too much data (that if the next gray value doesn't exist, an error is thrown)
        if (scanCount != -1) {
            free(pgm->commentLine);
            free(pgm->imageData);
            fclose(inputFile);
            return BAD_DATA;
        }
    }
    // This statement triggers if the magic number is 'P5'
    else if (pgm->magicNumberArray[1] == '5') {
        // Reads in the imageData as binary values
        fread(pgm->imageData, sizeof(unsigned char), pgm->width * pgm->height, inputFile);

        // Attempting to read the next gray value (to check for too much data)
        int grayValue = -1;
        scanCount = -1;
        scanCount = fscanf(inputFile, " %u", &grayValue); // Attempts to read the next gray value

        // Error checking which checks for too much data (that if the next gray value doesn't exist, an error is thrown)
        if (scanCount != -1) {
            free(pgm->commentLine);
            free(pgm->imageData);
            fclose(inputFile);
            return BAD_DATA;
        }
    }

    // Closes the input file
	fclose(inputFile);

    // Returns 0 to indicate there were no errors and the module ran successfully
    return EXIT_NO_ERRORS;
}