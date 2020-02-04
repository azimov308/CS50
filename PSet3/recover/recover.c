#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check if valid num of args
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover filename.raw\n");
        return 1;
    }

    // get data from memory card
    char *inFile = argv[1];

    // open memory card
    FILE *file = fopen(inFile, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inFile);
        return 2;
    }

    // create an array buffer for 512 blocks per byte
    unsigned char buffer[512];

    // create counter for found jpeg's
    int counter = 0;

    // create a string with n positions, must be over 7 for some reason
    char resultString[20];

    // setting pointer to a type FILE
    FILE *img;

    // read in 512 blocks, 1 byte at a time
    while (fread(&buffer, 512, 1, file))
    {
        // test if the start of the jpeg is valid
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if valid, increment by 1
            counter += 1;

            // give names of the jpeg as ###.jpg
            sprintf(resultString, "%03i.jpg", counter - 1);

            // set img to equal temp storage of the written result
            img = fopen(resultString, "w");
        }
        // make sure there are jpeg's in the file
        if (counter > 0)
        {
            // print out contents from img into an array
            fwrite(&buffer, 512, 1, img);
        }
    }

    // close files
    fclose(img);
    fclose(file);

    // success
    return 0;
}