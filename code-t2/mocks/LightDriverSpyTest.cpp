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
#include "LightDriverSpy.h"
}

#include "CppUTest/TestHarness.h"

//START: turnOnTest
TEST_GROUP(LightDriverSpy)
{
    LightDriver lightDriver;

    void setup()
    {
        LightDriverSpy_Reset();
        lightDriver = LightDriverSpy_Create(1);
        LightDriverSpy_InstallInterface();
    }

    void teardown()
    {
        LightDriver_Destroy(lightDriver);
    }
};

TEST(LightDriverSpy, On)
{
    LightDriver_TurnOn(lightDriver);
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}
//END: turnOnTest

TEST(LightDriverSpy, LightStateUnknownAfterCreate)
{
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, Off)
{
    LightDriver_TurnOff(lightDriver);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, RecordsLastIdLastTurnOn)
{
    LightDriver_TurnOff(lightDriver);
    LONGS_EQUAL(1, LightDriverSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetLastState());
}

TEST(LightDriverSpy, RecordsLastIdLastTurnOff)
{
    LightDriver_TurnOn(lightDriver);
    LONGS_EQUAL(1, LightDriverSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetLastState());
}

