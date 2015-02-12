#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    //initializing h
    int h = 0;
    
    //setting up do - while loop to keep retrying until the right height is given
    do {        
        //requesting height input
        printf("Height: ");
        h = GetInt();
        
        //intiializing loop integers
        int i;
        int j;
        int k;
        
        //only allowing loop to run if fits the correct vallues
        if (h <= 23 && h >= 0)
        {
            //building pyramid height
            for (i = 0; i < h; i++)
            {
            
                //building blank spaces before pyramid
                for (j=2; j <= (h - i); j++)
                {
                    printf(" ");
                }
                
                //building pyramid spots
                for (k=0; k <= i; k++)
                {
                    printf("#");
                }
                
                printf("  ");
                
                //building pyramid spots r2
                for(k=0; k <= i; k++)
                {
                    printf("#");
                }
                           
            //next level of pyramid!
            printf("\n");
            } 
        }
    
    //keep asking until the correct input is given
    } while (h > 23 || h < 0);
    
    return 0;
}
