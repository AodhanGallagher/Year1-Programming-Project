/* Header file that defines the structure for storing the relevant data from pgm files */

typedef struct pgmImage {
    unsigned char magicNumberArray[2];
    unsigned short *magicNumber;
    char *commentLine;
    unsigned int width;
    unsigned int height;
    unsigned int maxGray;
    unsigned char *imageData;
    long nImageBytes;
} pgmImage;