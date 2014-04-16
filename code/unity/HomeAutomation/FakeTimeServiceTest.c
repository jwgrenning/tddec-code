/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
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


#include "unity_fixture.h"



#include "FakeTimeService.h"
#include "LightScheduler.h"
#include "memory.h"


static int callBackCalled;

TEST_GROUP(FakeTimeService);

TEST_SETUP(FakeTimeService)
{
  callBackCalled = 0;
  TimeService_Create();
}

TEST_TEAR_DOWN(FakeTimeService)
{
   TimeService_Destroy();
}


static void TestCallback()
{
    callBackCalled = 1;
}

TEST(FakeTimeService, SimulateATic)
{
    TimeService_SetPeriodicAlarmInSeconds(60, TestCallback);

    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_MinuteIsUp();

    TEST_ASSERT_EQUAL(1, callBackCalled);
}


TEST(FakeTimeService, Create)
{
    Time time;
    TimeService_GetTime(&time);

    TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
    TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);

    TimeService_GetTime(&time);

    TEST_ASSERT_EQUAL(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL(SATURDAY, time.dayOfWeek);
}
