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
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "CppUTestExt/MockSupport_c.h"
#include "Flash.h"
#include "m28w160ect.h"
#include "FakeMicroTime.h"

// START: IO_Write
void IO_Write(ioAddress addr, ioData value)
{
    mock_c()->actualCall("IO_Write")
            ->withIntParameters("addr", addr)
            ->withIntParameters("value", value);
}
// END: IO_Write

// START: IO_Read
ioData IO_Read(ioAddress addr)
{
    mock_c()->actualCall("IO_Read")
            ->withIntParameters("addr", addr);

   return mock_c()->returnValue().value.intValue;
}
// END: IO_Read

}

// START: TEST_GROUP2
TEST_GROUP(Flash)
{
    ioAddress address;
    ioData data;
    int result;

    void setup()
    {
        address = 0xfeed;
        data = 0x1dea;
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
    }

    // START: helpers
    void expectCommand(ioData command)
    {
        mock().expectOneCall("IO_Write")
                .withParameter("addr", CommandRegister)
                .withParameter("value", command);
    }

    void expectWriteData()
    {
        mock().expectOneCall("IO_Write")
                .withParameter("addr", (int) address)
                .withParameter("value", data);
    }

    void simulateDeviceStatus(ioData status)
    {
        mock().expectOneCall("IO_Read")
                .withParameter("addr", StatusRegister)
                .andReturnValue((int) status);
    }

    void simulateDeviceStatusWithRepeat(ioData status, int repeatCount)
    {
        mock().expectNCalls(repeatCount, "IO_Read")
                .withParameter("addr", StatusRegister)
                .andReturnValue((int) status);
    }

    void simulateReadback(ioData data)
    {
        mock().expectOneCall("IO_Read")
                .withParameter("addr", (int) address)
                .andReturnValue((int) data);
    }
    // END: helpers



};
// END: TEST_GROUP2

// START: WriteSucceedsReadyImmediately2
TEST(Flash, WriteSuccessImmediately)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit);
    simulateReadback(data);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}
// END: WriteSucceedsReadyImmediately2

//START: ProgramSucceedsNotImmediatelyReady
TEST(Flash, ProgramSucceedsNotImmediately)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatusWithRepeat(0, 3);
    simulateDeviceStatus(ReadyBit);
    simulateReadback(data);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}
//END: ProgramSucceedsNotImmediatelyReady

//START: WriteFails_VppError
TEST(Flash, WriteFails_VppError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | VppErrorBit);
    expectCommand(Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_VPP_ERROR, result);
}
//END: WriteFails_VppError

//START: WriteFails_ProgramError
TEST(Flash, WriteFails_ProgramError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | ProgramErrorBit);
    expectCommand(Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROGRAM_ERROR, result);
}
//END: WriteFails_ProgramError

//START: WriteFails_ProtectedBlockError
TEST(Flash, WriteFails_ProtectedBlockError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit | BlockProtectionErrorBit);
    expectCommand(Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROTECTED_BLOCK_ERROR, result);
}
//END: WriteFails_ProtectedBlockError

//START: WriteFails_FlashUnknownProgramError
TEST(Flash, WriteFails_FlashUnknownProgramError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit |  EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit);
    expectCommand(Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_UNKNOWN_PROGRAM_ERROR, result);
}
//END: WriteFails_FlashUnknownProgramError

//START: WriteFails_FlashReadBackError
TEST(Flash, WriteFails_FlashReadBackError)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(ReadyBit);
    simulateReadback(data-1);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}
//END: WriteFails_FlashReadBackError

//START: WriteSucceeds_IgnoresOtherBitsUntilReady
TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatus(~ReadyBit);
    simulateDeviceStatus(ReadyBit);
    simulateReadback(data);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}
//END: WriteSucceeds_IgnoresOtherBitsUntilReady

//START: WriteFails_Timeout_1
TEST(Flash, WriteFails_Timeout)
{
    FakeMicroTime_Init(0, 500);
    Flash_Create();
    expectCommand(ProgramCommand);
    expectWriteData();
    simulateDeviceStatusWithRepeat(~ReadyBit, 10);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}
//END: WriteFails_Timeout_1

//START: WriteFails_TimeoutAtEndOfTime
TEST(Flash, WriteFails_TimeoutAtEndOfTime)
{
    FakeMicroTime_Init(0xffffffff, 500);
    Flash_Create();
    expectCommand(ProgramCommand);
    expectWriteData();
    for (int i = 0; i < 10; i++)
        simulateDeviceStatus(~ReadyBit);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}
//END: WriteFails_TimeoutAtEndOfTime


#if 0 // START: TEST_GROUP1
TEST_GROUP(Flash)
{
    ioAddress address;
    ioData data;
    int result;

    void setup()
    {
        address = 0xfeed;
        data = 0x1dea;
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
    }
};
#endif // END: TEST_GROUP1

#if 0 // START: WriteSucceedsReadyImmediately1
TEST(Flash, WriteSuccessImmediately)
{
    mock().expectOneCall("IO_Write")
            .withParameter("addr", CommandRegister)
            .withParameter("value", ProgramCommand);
    mock().expectOneCall("IO_Write")
            .withParameter("addr", (int) address)
            .withParameter("value", data);
			
    mock().expectOneCall("IO_Read")
            .withParameter("addr", StatusRegister)
            .andReturnValue((int) ReadyBit);
    mock().expectOneCall("IO_Read")
            .withParameter("addr", (int) address)
            .andReturnValue((int) data);

    int result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_SUCCESS, result);
}
#endif // END: WriteSucceedsReadyImmediately1

