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
#include "TimeService.h"
#include "FakeTimeService.h"
}

TEST_GROUP(TimeService)
{
    void setup()
    {
      TimeService_Create();
    }

    void teardown()
    {
       TimeService_Destroy();
    }
};

TEST(TimeService, Create)
{
    LONGS_EQUAL(MINUTE_UNKNOWN, TimeService_GetMinute());
    LONGS_EQUAL(DAY_UNKNOWN, TimeService_GetDay());
}

TEST(TimeService, Set)
{
    FakeTimeService_SetMinute(42);
    LONGS_EQUAL(42, TimeService_GetMinute());
    FakeTimeService_SetDay(3);
    LONGS_EQUAL(3, TimeService_GetDay());
}
