#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


/*******************************************************************************
Vigenere Cipher

This program accepts one alphabetical string argument. It then requires an input
string. The input string is encrypted with the vigienere's cipher, where the key
is the argument passed to the program on initialization.

Case of the input is perserved, non alphabetical characters remain unencrypted.
*******************************************************************************/

int main(int argc, string argv[])
{
    
    //checking number of arguments
    if (argc != 2)
    {
        printf("Please enter one argument!\n");
        return 1;
            
    }
    
    //checking that argument is all alphabetical
    int len_cipher = strlen(argv[1]);
    for (int i = 0; i < len_cipher; i++)
    {    
        if (isalpha(argv[1][i]) == false)
        {
            printf("Please enter alphabetical characters only!\n");
            return 1;
        }
    }
  
    //captalizing cipher key;        
    for (int i = 0; i < len_cipher; i++)
    {
        argv[1][i] = toupper (argv[1][i]);            
    }
    
    //getting input and its length, initializing counters/value stores
    string input = GetString();
    int len_input = strlen(input);    
    int k = 0;
    int j = 0;
   
    //cipher loops across the length of the input string
    for (int i = 0; i < len_input; i++)
    {
        //setting up the value to 'rotate' by
        k = (argv[1][j % len_cipher] - 'A');
    
        //for uppercase
        if ((input[i] >= 'A') && (input[i] <= 'Z'))
        { 
            input[i] = ( ( (input[i] - 'A') + k ) % 26 ) + 'A';
            printf("%c", input[i]);
            j++;  //j iterates the cipher character selector  
        }
        //for lowercase
        else if ((input[i] >= 'a') && (input[i] <= 'z'))
        {
            input[i] = ( ( (input[i] - 'a') + k ) % 26 ) + 'a';
            printf("%c", input[i]);   
            j++;
        }        
        //for non-alphabetical
        else printf("%c", input[i]);
    }
    printf("\n");
    return 0;   
}
