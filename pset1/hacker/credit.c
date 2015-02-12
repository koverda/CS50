#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //Get card number convert to integer and convert to string and figure out length
    printf("Number: ");    
    long long input = GetLongLong();
    long long int round_input = (long long int) round (input);    
    char str_input[40];
    sprintf(str_input, "%lli", round_input);
    int in_length = strlen(str_input);
    
    //Checksum parameters, remainder of deviding by 10 is used to figure out digit's places
    long long int remainder = round_input % 10;
    long long int large_digit_remainder = 0;
    long long int sum_odd = 0;
    long long int sum_even = 0;
    
    //Checksum calculations
    for (int i = 0; i <= in_length / 2 ; i++)
    {     
        //get remainder of odd digit, add to 'sum_odd', move to next digit (dividing by 10)
        remainder = round_input % 10;  
        sum_odd = sum_odd + remainder;    
        round_input = (round_input - remainder) / 10.00;    
        
        //get remainder of even digit, add to 'sum_even', move to next digit (dividing by 10)
        remainder =  round_input % 10;  
        round_input = (round_input - remainder) / 10;
        
        //doubling digits       
        large_digit_remainder = 0;
        remainder = remainder * 2;
        
        //splitting out digits from doubling
        if (remainder >= 10)
        {
            large_digit_remainder = remainder % 10;  
            remainder = (remainder - large_digit_remainder) / 10;
        }                
        sum_even = sum_even + remainder + large_digit_remainder; 
    }
      
      
    //final sum        
    sum_odd = sum_odd + sum_even;
    
    //conditions to figure out card type
    char output[40] = "INVALID\n";
    char amex[40] = "AMEX\n";    
    char visa[40] = "VISA\n";
    char mc[40] = "MASTERCARD\n"; 

    //Getting first two numbers of string as integers to figure out card type
    char first_two_char[2] = "xx";
    strncpy ( first_two_char, str_input, 2 );  
    int first_two_int = atoi ( first_two_char);     
    
    //if the checksum is divisible by 10, and the input length is correct
    //and the card number starts with the correct sequece
    //update the output to the correct value (AMEX, MC, VISA, etc)
    //if it's not correct, leave output value as INVALID 
    if (sum_odd % 10 == 0)
    {        
        if (in_length == 16 || in_length == 15 || in_length == 13)
        {
            if (first_two_int == 34 || first_two_int == 37)
            {
                strcpy (output, amex);
            }
            else if (first_two_int >= 40 && first_two_int <= 49)
            {
                strcpy (output, visa);
            }
            else if (first_two_int >= 51 && first_two_int <= 55)
            {
                strcpy (output, mc);
            } 
        }        
        else
        {
            printf("%s", output);
            return(0);
        }
    }
    else
    {
        printf("%s", output);
        return(0);
    }
    printf("%s", output);
    return(0);
}
