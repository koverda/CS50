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
#include <string.h>
#include <stdint.h>


int main(int argc, char* argv[])
{
    //open raw data file you are trying to recover
    FILE* file = fopen("card.raw", "r");
    
    //define buffer
    uint8_t buf[512];
    
    //define jpg title holder, counter, and position holder
    char title[10];
    int counter = 0;
    fpos_t position; 
    
    //read from file into buffer until you can't load 512 bytes into buffer
    while (fread(&buf, sizeof (char), 512, file) == 512)
    {
        //check for start of initial jpeg
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff  && (buf[3] == 0xe0 || buf[3] == 0xe1))
        {
            //store the title of the JPG
            sprintf(title, "%03d.jpg", counter);
                        
            //open an image file named 'title' to store image info
            FILE* image = fopen(title, "a");
            
            //write beginning block 
            fwrite(&buf, sizeof (char), 512, image);
            
            //while not at the beginning of a new jpg    
            while ((fread(&buf, sizeof (char), 512, file) == 512) && (!(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff  && (buf[3] == 0xe0 || buf[3] == 0xe1))))
            {    
                //write buffer to image file   
                fwrite(&buf, sizeof (char), 512, image);
                
                //record position in raw file
                fgetpos(file, &position); 
            }       
            
            //go back to start of image
            fsetpos(file, &position);
            
            //close image file and iterate image counter
            fclose(image); 
            counter++;
        }
    }
  
    //close raw file
    fclose(file);
    return 0;
}
