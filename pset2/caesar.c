#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**************************
Ceasar cypher

program accepts one command line argument 
signifying how many letters to rotate the ceaser cypher by (k)
then prompts the user for a text to cypher.

We then rotate each non-numeric character by k%26 and output it.

Case must be preserved.

**************************/

int main(int argc, string argv[])
{
    
    //checking number of arguments
    if (argc != 2)
    {
        printf("Please enter one argument!\n");
        return 1;
            
    }
    
    long long int k = atoll(argv[1]);
    k =  k % 26;
    //printf("%lli\n", k);
    
    //printf("Please enter the text you want encrypted with the ceasar cypher: \n");
    string input = GetString();
    
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (input[i] > 64 && input[i] < 91)
        { 
            input[i] = ( ( (input[i] - 65) + k ) % 26 ) + 65;
            printf("%c", input[i]);   
        }
            
        else if (input[i] > 96 && input[i] < 123)
        {
            input[i] = ( ( (input[i] - 97) + k ) % 26 ) + 97;
            printf("%c", input[i]);   
        }    
        
        else printf("%c", input[i]);
}
    printf("\n");
    return 0;
    
}
