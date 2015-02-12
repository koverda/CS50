#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 1;
    
    //setting up do - while loop to keep retrying until the right height is given
    do {
        
        //requesting height input
        printf("Height: ");
        height = GetInt();
        
        //intiializing loop integers
        int i;
        int j;
        int k;
        
        //only allowing loop to run if fits the correct vallues
        if(height <= 23 && height >= 0)
        {
            //building pyramid height
            for(i = 0; i < height; i++)
            {
            
                //building blank spaces before pyramid
                for(j=2; j <= (height - i); j++)
                {
                    printf(" ");
                }
                
                //building pyramid spots
                for(k=-1; k <= i; k++)
                {
                    printf("#");
                }
            
            //next level of pyramid!
            printf("\n");
            } 
        }
    } while (height > 23 || height < 0);
    return 0;
}
