/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/

#include "ProductionCode.h"

int Counter = 0;
int NumbersToFind[9] = { 0, 34, 55, 66, 32, 11, 1, 77, 888 }; //some obnoxious array to search that is 1-based indexing instead of 0.

// This function is supposed to search through NumbersToFind and find a particular number.  
// If it finds it, the index is returned.  Otherwise 0 is returned which sorta makes sense since 
// NumbersToFind is indexed from 1.  Unfortunately it's broken 
// (and should therefore be caught by our tests)
int FindFunction_WhichIsBroken(int NumberToFind)
{
    int i = 0;
    while (i <= 8) //Notice I should have been in braces
        i++;
        if (NumbersToFind[i] == NumberToFind) //Yikes!  I'm getting run after the loop finishes instead of during it!
            return i;
    return 0;
}

int FunctionWhichReturnsLocalVariable(void)
{
    return Counter;
}
