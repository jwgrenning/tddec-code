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
#include "MockIO.h"
}

#include "CppUTest/TestHarness.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/TestOutput.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTest/TestTestingFixture.h"


static void MockIOSetup()
{
    MockIO_Create(2);
}

static void MockIOTeardown()
{
    MockIO_Destroy();
}

TEST_GROUP(MockIO)
{
    TestTestingFixture* fixture;
    int expectedErrors;
    void setup()
    {
        fixture = new TestTestingFixture();
        fixture->setSetup(MockIOSetup);
        fixture->setTeardown(MockIOTeardown);
        expectedErrors = 1;
    }
    void teardown()
    {
        delete fixture;
    }

    void testFailureWith(void (*method)())
    {
       fixture->setTestFunction(method);
       fixture->runAllTests();
       LONGS_EQUAL(expectedErrors, fixture->getFailureCount());
    }

};

TEST_GROUP(MockIOTemp)
{
    void setup()
    {
      MockIO_Create(2);
    }

    void teardown()
    {
       MockIO_Destroy();
    }
};

static void CanMatchExpectations()
{
    MockIO_Expect_ReadThenReturn(1,2);
    MockIO_Expect_Write(1,2);
    IO_Write(1,IO_Read(1));
}

TEST(MockIO, CanMatchExpectations)
{
  expectedErrors = 0;
  testFailureWith(CanMatchExpectations);
  fixture->assertPrintContains("OK");
}

static void WriteWhenReadExpectedFails()
{
    MockIO_Expect_ReadThenReturn(0,1);
    IO_Write(0,0);
}

TEST(MockIO, WriteWhenReadExpectedFails)
{
  testFailureWith(WriteWhenReadExpectedFails);
  fixture->assertPrintContains("Expected IO_Read(0x0) would return 0x1");
  fixture->assertPrintContains("But was IO_Write(0x0, 0x0)");
}

static void ReadWhenWriteExpectedFails()
{
    MockIO_Expect_Write(0,1);
    IO_Read(0);
}

TEST(MockIO, ReadWhenWriteExpectedFails)
{
  testFailureWith(ReadWhenWriteExpectedFails);
  fixture->assertPrintContains("Expected IO_Write(0x0, 0x1)");
  fixture->assertPrintContains("But was IO_Read(0x0)");
}

static void TooManyWriteExpectations()
{
    MockIO_Expect_Write(0,1);
    MockIO_Expect_Write(0,1);
    MockIO_Expect_Write(0,1);
}

TEST(MockIO, TooManyWriteExpectations)
{
  testFailureWith(TooManyWriteExpectations);
  fixture->assertPrintContains("MockIO_Expect_IO_Write: Too many expectations");
}

static void TooManyReadExpectations()
{
    MockIO_Expect_ReadThenReturn(0,0);
    MockIO_Expect_ReadThenReturn(0,0);
    MockIO_Expect_ReadThenReturn(0,0);
}

TEST(MockIO, TooManyReadExpectations)
{
  testFailureWith(TooManyReadExpectations);
  fixture->assertPrintContains("MockIO_Expect_IO_Read: Too many expectations");
}


static void notInitializedReadTest()
{
    MockIO_Destroy();
    MockIO_Expect_ReadThenReturn(0,0);
}

TEST(MockIO, NotInitializedTheRead)
{
  testFailureWith(notInitializedReadTest);
  fixture->assertPrintContains("MockIO not initialized");
}

static void notInitializedWriteTest()
{
    MockIO_Destroy();
    MockIO_Expect_Write(0,0);
}

TEST(MockIO, NotInitializedTheWrite)
{
  testFailureWith(notInitializedWriteTest);
  fixture->assertPrintContains("MockIO not initialized");
}

static void MismatchedWriteAddress()
{
    MockIO_Expect_Write(0,0);
    IO_Write(0x10,0);
}

TEST(MockIO, MismatchedWriteAddress)
{
  testFailureWith(MismatchedWriteAddress);
  fixture->assertPrintContains("Expected IO_Write(0x0, 0x0)");
  fixture->assertPrintContains("But was IO_Write(0x10, 0x0)");
}

static void MismatchedWriteData()
{
    MockIO_Expect_Write(0,0);
    IO_Write(0,0xdead);
}

TEST(MockIO, MismatchedWriteData)
{
  testFailureWith(MismatchedWriteData);
  fixture->assertPrintContains("Expected IO_Write(0x0, 0x0)");
  fixture->assertPrintContains("But was IO_Write(0x0, 0xdead)");
}

static void MismatchedReadAddress()
{
    MockIO_Expect_ReadThenReturn(0x1000,0xaaaa);
    IO_Read(0x10000);
}

TEST(MockIO, MismatchedReadAddress)
{
  testFailureWith(MismatchedReadAddress);
  fixture->assertPrintContains("Expected IO_Read(0x1000) returns 0xaaaa");
  fixture->assertPrintContains("But was IO_Read(0x10000)");
}

static void TooManyReads()
{
    IO_Read(0x10000);
}

TEST(MockIO, TooManyReads)
{
  testFailureWith(TooManyReads);
  fixture->assertPrintContains("No more expectations but was IO_Read(0x10000)");
}

static void TooManyWrites()
{
    IO_Write(0x10000, 0x1234);
}

TEST(MockIO, TooManyWrites)
{
  testFailureWith(TooManyWrites);
  fixture->assertPrintContains(
          "No more expectations but was IO_Write(0x10000, 0x1234)");
}

static void NotAllExpectationsUsed()
{
    MockIO_Expect_ReadThenReturn(0x1000,0xaaaa);
    MockIO_Expect_Write(0x1000,0x5555);
    MockIO_Verify_Complete();
}

TEST(MockIO, NotAllExpectationsUsed)
{
  testFailureWith(NotAllExpectationsUsed);
  fixture->assertPrintContains("Expected 2 reads/writes but got 0");
}


