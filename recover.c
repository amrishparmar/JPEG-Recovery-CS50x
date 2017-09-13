/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(void)
{
    // open raw card image file for reading
    FILE* inptr = fopen("card.raw", "r");
    FILE* outptr = NULL;
    
    int jpgsFound = -1;
    char outTitle[8];
    BYTE buffer[BLOCK];
    
    // while not eof
    while (fread(buffer, BLOCK, 1, inptr)) { // reads 512 bytes into an array buffer and ensures that it does not read one block past eof

        // start of new jpg?
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)) {
                //yes
                jpgsFound++; // increment the number of jpgs found (0-indexed)
                sprintf(outTitle, "%03d.jpg", jpgsFound); // format the file name string
                // check the the outptr file is not already open before writing
                if (outptr != NULL) {
                    fclose(outptr);
                }
                
                // create new file for writing
                outptr = fopen(outTitle, "a");
            }
            
            // write the contents of the buffer to the new block in the outptr file if not NULL
            if (outptr != NULL)
                fwrite(buffer, BLOCK, 1, outptr);     
    }
    
    // close remaining files
    fclose(inptr);
    fclose(outptr);
    
    return 0;   
}
