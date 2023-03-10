/* Header file for pgmRead.c containing function prototypes */

void initializePgmStruct(pgmImage *pgm);

int pgmRead(FILE *inputFile, pgmImage *pgm, char str[]);