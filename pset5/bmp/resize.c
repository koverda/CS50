#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4 || *argv[1] > 100 || *argv[1] < 1)
    {
        printf("Usage: ./resize n infile outfile\n");
        printf("Where n is the resize factor, a positive integer <= 100\n");    
        return 1;
    }
       
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]);  
    
    // try to open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
     
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
      
    // copy file headers
    BITMAPINFOHEADER biCopy = bi;
    BITMAPFILEHEADER bfCopy = bf;    

    // determine padding for input file's scanlines
    int padding  =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
    // resize  
    biCopy.biHeight = bi.biHeight * n;
    biCopy.biWidth = bi.biWidth * n;

   // determine padding for resized file's scanlines
    int outpadding  =  (4 - (biCopy.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
         
    // determine resized sizes    
    biCopy.biSizeImage = ((biCopy.biWidth  * sizeof(RGBTRIPLE) + outpadding) * abs(biCopy.biHeight));
    bfCopy.bfSize = biCopy.biSizeImage + 54;
    
       
    // try to open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }   
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfCopy, sizeof(BITMAPFILEHEADER), 1, outptr);
     
    // write outfile's BITMAPINFOHEADER
    fwrite(&biCopy, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create position variable
    fpos_t position; 
        
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //get position of beginning of scanline
        fgetpos(inptr, &position);
        
        //loop through each scanline, n times (copy vertically)
        for (int l = 0; l < n; l++)
        {
            // iterate over pixels in scanline  
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile, n times (copy horizontally)
                for (int k = 0; k < n; k++)
                {   
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }                         
            }

            // adding output padding
            for (int m = 0; m < outpadding; m++)
            {
                fputc(0x00, outptr);
            }
        
            //set position to beginning of scanline
            fsetpos(inptr, &position);    
        }
            
        // skip to end of scanline and padding, if any
        fseek(inptr, sizeof(RGBTRIPLE) * bi.biWidth + padding, SEEK_CUR); 
    }
   
    
    // close infile
    fclose(inptr);
    fclose(outptr);
}
