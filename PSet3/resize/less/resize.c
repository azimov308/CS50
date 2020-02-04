#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Need to take in 4 arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // Get scale size for new image
    int n = atoi(argv[1]);

    // Make sure n is a number
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            fprintf(stderr, "Scale multiplier must be a digit");
            return 2;
        }
    }

    // Make sure n is between 1 and 100
    if (n < 1 || n > 100)
    {
        printf("The number should be between 1 and 100");
        return 3;
    }

    // Get data for the infile and outfile
    char *infile = argv[2];
    char *outfile = argv[3];

    // Read in the infile
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 4;
    }

    // Create outfile
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 5;
    }

    // read infile's BITMAP FILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAP INFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // update RGBTRIPLE
    RGBTRIPLE scanline[bi.biWidth * sizeof(RGBTRIPLE)];

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create padding
    int newWidth = bi.biWidth * n;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update headers
    bi.biHeight = bi.biHeight * n;
    bi.biWidth = bi.biWidth * n;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(newWidth)) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // scanline temp array
    RGBTRIPLE sltemp[sizeof(RGBTRIPLE) * newWidth];

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight)/n; i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth/n; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // repeat each column n times
            for (int l = 0; l < n; l++)
            {
                // position for scanline to update temp storage
                int pos = (j * n) + l;
                sltemp[pos] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        for (int d = 0; d < n; d++)
        {
            // display scanline
            fwrite(sltemp, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            // then add it back (to demonstrate how)
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}