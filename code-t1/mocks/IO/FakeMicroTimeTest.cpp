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
#include "FakeMicroTime.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(MicroTime)
{
    void setup()
    {
        FakeMicroTime_Init(0, 5);
    }

    void teardown()
    {
    }
};

TEST(MicroTime, Create)
{
  LONGS_EQUAL(0, MicroTime_Get());
}

TEST(MicroTime, MicroTimeIncrements)
{
    LONGS_EQUAL(0, MicroTime_Get());
    LONGS_EQUAL(5, MicroTime_Get());
    LONGS_EQUAL(10, MicroTime_Get());
}

TEST(MicroTime, MicroTimeDelay)
{
    LONGS_EQUAL(0, MicroTime_Get());
    LONGS_EQUAL(5, MicroTime_Get());
    MicroTime_Delay(20);
    LONGS_EQUAL(30, MicroTime_Get());
}

TEST(MicroTime, MicroTimeDelayRecording)
{
    MicroTime_Delay(20);
    MicroTime_Delay(20);
    MicroTime_Delay(20);
    LONGS_EQUAL(60, FakeMicroTime_GetDelayDuration());
}


