/* Module for writing the values in the pgm struct to a new pgm file */

//Including relevant libraries and modules
#include <stdio.h>
#include <stdlib.h>

#include "pgmStruct.h"
#include "pgmDefinitions.h"


// Function used to write the values from the pgm struct to a new output file
int pgmWrite(FILE *outputFile,  pgmImage *pgm, char str[]) {
	// Checks to see that the output file exists / was created
	if (outputFile == NULL) {
		free(pgm->commentLine);
		free(pgm->imageData);
		printf("ERROR: Output Failed (%s)\n", str);
		return OUTPUT_FAILED;
	}

	// Writes the magic number, size and gray value
	size_t nBytesWritten = fprintf(outputFile, "%c%c\n%d %d\n%d\n",pgm->magicNumberArray[0], pgm->magicNumberArray[1], pgm->width, pgm->height, pgm->maxGray);

	// Checks that the dimensions wrote correctly
	if (nBytesWritten < 0) {
		free(pgm->commentLine);
		free(pgm->imageData);
		return OUTPUT_FAILED;
	}

	// If statement triggers if the magic number is 'P2'
	if (pgm->magicNumberArray[1] == '2') {
		// Pointer for efficient write code that loops over each gray value
		for (unsigned char *nextGrayValue = pgm->imageData; nextGrayValue < pgm->imageData + (pgm->width * pgm->height * sizeof(unsigned char)); nextGrayValue++) {
			// Gets the next character's column
			int nextCol = (nextGrayValue - pgm->imageData + 1) % pgm->width;

			// Writes the entry & whitespace
			nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

			// Error checking to check if the entry and whitespace was written correctly
			if (nBytesWritten < 0) {
				free(pgm->commentLine);
				free(pgm->imageData);
				return OUTPUT_FAILED;
			}
		}
	}
	// This statement triggers if the magic number is 'P5'
	else if (pgm->magicNumberArray[1] == '5') {
		// Writes the imageData to the outputFile as binary values
		fwrite(pgm->imageData, sizeof(unsigned char), pgm->width * pgm->height, outputFile);
	}

	// Returns 0 to indicate there were no errors and the module ran successfully
	return EXIT_NO_ERRORS;
}