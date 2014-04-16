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
#include "LightController.h"
#include "LightDriverSpy.h"
#include "CountingLightDriver.h"
}

#include "CppUTest/TestHarness.h"
//START: controllerTests
TEST_GROUP(LightController)
{
    void setup()
    {
        LightController_Create();
        LightDriverSpy_AddSpiesToController();
        LightDriverSpy_Reset();
    }

    void teardown()
    {
       LightController_Destroy();
    }
};
//END: controllerTests

TEST(LightController, CreateDestroy)
{
}

TEST(LightController, DriverIsDestroyedByLightController)
{
    LightDriver spy = LightDriverSpy_Create(1);
    LightController_Add(1, spy);
}

//START: controllerTests

//START: turnOn
TEST(LightController, TurnOn)
{
    LightController_TurnOn(7);
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
}
//END: turnOn
//END: controllerTests

TEST(LightController, TurnOff)
{
    LightController_TurnOff(1);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightController, AllDriversDestroyed)
{
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver spy = LightDriverSpy_Create(i);
        LONGS_EQUAL(TRUE, LightController_Add(i, (LightDriver)spy));
    }
}

TEST(LightController, ValidIdLowerRange)
{
    LightDriver spy = LightDriverSpy_Create(0);
    LONGS_EQUAL(TRUE, LightController_Add(0, spy));
}

TEST(LightController, ValidIdUpperRange)
{
    LightDriver spy = LightDriverSpy_Create(MAX_LIGHTS);
    LONGS_EQUAL(TRUE, LightController_Add(MAX_LIGHTS-1, spy));
}

TEST(LightController, InValidIdBeyondUpperRange)
{
    LightDriver spy = LightDriverSpy_Create(MAX_LIGHTS);
    LONGS_EQUAL(FALSE, LightController_Add(MAX_LIGHTS, spy));
    free(spy);
}

TEST(LightController, RemoveExistingLightDriverSucceeds)
{
    CHECK(LightController_Remove(10));
}

TEST(LightController, RemovedLightDoesNothing)
{
    LightController_Remove(1);
    LightController_TurnOn(1);
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
    LightController_TurnOff(1);
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}

TEST(LightController, RejectsNullDrivers)
{
    LONGS_EQUAL(FALSE, LightController_Add(1, NULL));
}

TEST(LightController, RemoveNonExistingLightDriverFails)
{
    CHECK(LightController_Remove(10));
    CHECK(LightController_Remove(10) == FALSE);
}

//START: turnOnDifferentDriverTypes
TEST(LightController, turnOnDifferentDriverTypes)
{
    LightDriver otherDriver = CountingLightDriver_Create(5);
    LightController_Add(5, otherDriver);
    LightController_TurnOn(7);
    LightController_TurnOn(5);
    LightController_TurnOff(5);
	
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
    LONGS_EQUAL(2, CountingLightDriver_GetCallCount(otherDriver));
}
//END: turnOnDifferentDriverTypes
