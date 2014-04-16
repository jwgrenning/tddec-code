//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------




#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
#include "Utils.h"
#include "FormatOutputSpy.h"
}

//START: TEST_GROUP
TEST_GROUP(CircularBufferPrint)
{
    CircularBuffer buffer;
    const char * expectedOutput;
    const char * actualOutput;

    void setup()
    {
      UT_PTR_SET(FormatOutput, FormatOutputSpy);
      FormatOutputSpy_Create(100);
      actualOutput = FormatOutputSpy_GetOutput();
      buffer = CircularBuffer_Create(10);
    }

    void teardown()
    {
       CircularBuffer_Destroy(buffer);
       FormatOutputSpy_Destroy();
    }
    //END: TEST_GROUP
    void putManyInTheBuffer(int seed, int howMany)
    {
        for (int i = 0; i < howMany; i++)
            CircularBuffer_Put(buffer, i+seed);
    }
    //START: TEST_GROUP
};
//END: TEST_GROUP

//START: PrintEmpty
TEST(CircularBufferPrint, PrintEmpty)
{
    expectedOutput = "Circular buffer content:\n<>\n";
    CircularBuffer_Print(buffer);
    STRCMP_EQUAL(expectedOutput, actualOutput);
}
//END: PrintEmpty

/*
 * You should have only printed the heading.  this next test drives you
 * to get the format of a single element.  Did you implement any of
 * the wrap around logic in your print function?  Delete it if you did.
 */

//START: PrintAfterOneIsPut
TEST(CircularBufferPrint, PrintAfterOneIsPut)
{
    expectedOutput = "Circular buffer content:\n<17>\n";
    CircularBuffer_Put(buffer, 17);
    CircularBuffer_Print(buffer);
    STRCMP_EQUAL(expectedOutput, actualOutput);
}
//END: PrintAfterOneIsPut

//START: PrintNotYetWrappedOrFull
TEST(CircularBufferPrint, PrintNotYetWrappedOrFull)
{
    expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
    CircularBuffer_Put(buffer, 10);
    CircularBuffer_Put(buffer, 20);
    CircularBuffer_Put(buffer, 30);
    CircularBuffer_Print(buffer);
    STRCMP_EQUAL(expectedOutput, actualOutput);
}
//END: PrintNotYetWrappedOrFull

//START: PrintNotYetWrappedAndIsFull
TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull)
{
    expectedOutput = "Circular buffer content:\n"
                     "<31, 41, 59, 26, 53>\n";

    CircularBuffer b = CircularBuffer_Create(5);
    CircularBuffer_Put(b, 31);
    CircularBuffer_Put(b, 41);
    CircularBuffer_Put(b, 59);
    CircularBuffer_Put(b, 26);
    CircularBuffer_Put(b, 53);

    CircularBuffer_Print(b);

    STRCMP_EQUAL(expectedOutput, actualOutput);
    CircularBuffer_Destroy(b);
}
//END: PrintNotYetWrappedAndIsFull

//START: PrintWrappedAndIsFullOldestToNewest
TEST(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull)
{
    expectedOutput =
        "Circular buffer content:\n"
        "<201, 202, 203, 204, 999>\n";

    CircularBuffer b = CircularBuffer_Create(5);
    CircularBuffer_Put(b, 200);
    CircularBuffer_Put(b, 201);
    CircularBuffer_Put(b, 202);
    CircularBuffer_Put(b, 203);
    CircularBuffer_Put(b, 204);
    CircularBuffer_Get(b);
    CircularBuffer_Put(b, 999);

    CircularBuffer_Print(b);

    STRCMP_EQUAL(expectedOutput, actualOutput);
    CircularBuffer_Destroy(b);
}
//END: PrintWrappedAndIsFullOldestToNewest

#if 0   //Move this line down one test at a time
TEST(CircularBufferPrint, FillThenEmptyThenPrint)
{
    char * expectedOutput =
        "Circular buffer content:\n"
        "<>\n";
}

TEST(CircularBufferPrint, PrintAMessageForPutToFull)
{

}

TEST(CircularBufferPrint, PrintAMessageForGetFromEmpty)
{

}

#endif


