/* A module containing definitions for relevant error numbers and other values in the assignment */

// Defining Errors
#define EXIT_NO_ERRORS 0
#define EXIT_BAD_ARG_COUNT 1
#define EXIT_BAD_FILE_NAME 2
#define EXIT_BAD_MAGIC_NO 3
#define BAD_COMMENT_LINE 4
#define BAD_DIMENSIONS 5
#define BAD_MAX_GRAY_VALUE 6
#define IMAGE_MALLOC_FAILED 7
#define BAD_DATA 8
#define OUTPUT_FAILED 9
#define BAD_LAYOUT 10
#define MISCELLANEOUS 100

// Defining Common Numbers
#define MAGIC_NUMBER_BINARY_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128