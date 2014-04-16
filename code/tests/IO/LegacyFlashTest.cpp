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


extern "C"
{
#include "Flash.h"
#include "MockIO.h"
#include "m28w160ect.h"
}

#include "CppUTest/TestHarness.h"

//START: TEST_GROUP_LegacyFlash
TEST_GROUP(LegacyFlash)
{
    int result;

    void setup()
    {
        MockIO_Create(10);
        Flash_Create();
        result = 0;
    }

    void teardown()
    {
        Flash_Destroy();
        MockIO_Verify_Complete();
        MockIO_Destroy();
    }
};
//END: TEST_GROUP_LegacyFlash

#if 1 //START: FlashProgramSuccess5
TEST(LegacyFlash, FlashProgramSuccess)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(0x1000, 0xBEEF);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    MockIO_Expect_ReadThenReturn(0x1000, 0xBEEF);

    result = Flash_Write(0x1000, 0xBEEF);

    LONGS_EQUAL(0, result);
}
#endif //END: FlashProgramSuccess5

#if 0 //START: FlashProgramSuccess4
TEST(LegacyFlash, FlashProgramSuccess)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(0x1000, 0xBEEF);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, 0);
    MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
    result = Flash_Write(0x1000, 0xBEEF);
    LONGS_EQUAL(0, result);
}
#endif //END: FlashProgramSuccess4

#if 0 //START: FlashProgramSuccess3
TEST(LegacyFlash, FlashProgramSuccess)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(0x1000, 0xBEEF);
    result = Flash_Write(0x1000, 0xBEEF);
    LONGS_EQUAL(0, result);
}
#endif //END: FlashProgramSuccess3

#if 0 //START: FlashProgramSuccess2
TEST(LegacyFlash, FlashProgramSuccess)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    result = Flash_Write(0x1000, 0xBEEF);
    LONGS_EQUAL(0, result);
}
#endif //END: FlashProgramSuccess2

#if 0 //START: FlashProgramSuccess1
TEST(LegacyFlash, FlashProgramSuccess)
{
    result = Flash_Write(0x1000, 0xBEEF);
    LONGS_EQUAL(0, result);
}
#endif //END: FlashProgramSuccess1

#if 0 //START: FlashProgramSuccess0
TEST(LegacyFlash, FlashProgramSuccess)
{
    FAIL("Getting started");
}
#endif //END: FlashProgramSuccess0


