/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/* 
 * Recursive implementation of a binary search.
 * Updates the array elements which are searched with each recursion
 * based on a comparison of the search value with the midpoint of the
 * remaining array
 */
bool binsearch(int value, int values[], int min, int max)
{ 
    int midpoint = values[(min + max) / 2];
    
    if (min > max) // searched the whole array and didn't find it!
    {
        return false;
    }
    
    if (value > midpoint) 
    {
        min = (min + max) / 2 + 1; // Look in the top half of the remaining array
        return binsearch(value, values, min, max);
    }    
 
    else if (value < midpoint)
    {
        max = (min + max) / 2 - 1; // Look in the bottom half of the remaining array
        return binsearch(value, values, min, max);
    }   
 
    else if (value == midpoint) // Found it!
    {
        return true;
    }    
    
    return false;
}   

/**
 * Returns true if value is in array of n values, else false.
 * Uses the binary search function defined above. 
 */
bool search(int value, int values[], int n)
{  
    if (n < 1) // checking if n is positive 
    {
       return false;
    }
    
    else
    {
        if (binsearch(value, values, 0, n))
        {
            return true;
        }
    }
    
    return false;
}


/**
 * Sorts array of n values.
 * Uses bubble sort: an O(n^2) sorting algorithm
 */
void sort(int values[], int n)
{
    bool sorted;
    int holder;
   
    do {
        sorted = true;
        
        for (int i = 0; i < n - 1 ; i++)
        {         
            if (values[i] > values[i + 1])
            {
                sorted = false;
                holder = values[i];
                values[i] = values[i + 1];
                values[i + 1] = holder;
            }
        }
        
    } while (sorted == false);
    
    return;
}
