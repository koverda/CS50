#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    printf("O hai!  ");
    float c = 0;
    
    do {     
        //get user input
        printf("How much change is owed?\n");
        c = GetFloat();  
        
        //convert to cents and round
        int ci = (int) round (c * 100);
        
        //initialize denomination counters    
        int qu = 0;
        int di = 0;
        int ni = 0;
        int pe = 0;
        
        //do we have a positive value?
        if (c >= 0)
        {   
            //begin counting loops
            //quarters
            while (ci >= 25)
            {
                ci = ci - 25;
                qu++;
            }
            
            //dimes
            while (ci >= 10)
            {
                ci = ci - 10;
                di++;
            }
            
            //nickels
            while (ci >= 5)
            {
                ci = ci - 5;
                ni++;
            }
            
            //pennies
            while (ci >= 1)
            {
                ci = ci - 1;
                pe++;
            }
            
            //total count
            printf("%i\n", qu + di + ni + pe);
        }
    } while (c < 0);
}
