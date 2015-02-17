#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/*********************************************
CS50 pset2 2015
Peter Koverda

Initials program

recieves input of a name with no special 
characters besides spaces: ' '
outputs capitalized initials of name:
Input = foo bar
Output = FB
*********************************************/

int main(void)
{
    // get input
    string name = GetString();

    // print first initial    
    printf("%c", toupper(name[0]));
    
    // search for spaces, and print the letter after a space
    char * pch;
    pch = strchr(name,' ');
    while (pch!=NULL)
    {
        printf ("%c", toupper(name[pch-name+1]));
        pch=strchr(pch+1,' ');
    }
    
    //finish with a newline character
    printf("\n"); 
    return 0;
}

