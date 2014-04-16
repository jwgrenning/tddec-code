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

TEST_GROUP(LightDriver)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

/* START: nullDriver */
#define NONSENSE_POINTER (LightDriver)~0
static LightDriver savedDriver = NONSENSE_POINTER;
static void shouldNotBeCalled(LightDriver self) { savedDriver = self ;}

LightDriverInterfaceStruct interface =
{
    shouldNotBeCalled,
    shouldNotBeCalled,
    shouldNotBeCalled
};

LightDriverStruct testDriver =
{
    "testDriver",
    13
};
/* END: nullDriver */

/* START: nullDriverTest */
TEST(LightDriver, NullDriverDoesNotCrash)
{
    LightDriver_SetInterface(&interface);
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
    POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}
/* END: nullDriverTest */

/* START: nullInterfaceTest */
TEST(LightDriver, NullInterfaceDoesNotCrash)
{
    LightDriver_SetInterface(NULL);
    LightDriver_TurnOn(&testDriver);
    LightDriver_TurnOff(&testDriver);
    LightDriver_Destroy(&testDriver);
    POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}
/* END: nullInterfaceTest */

TEST(LightDriver, Accessors)
{
    LONGS_EQUAL(13, LightDriver_GetId(&testDriver));
    STRCMP_EQUAL("testDriver", LightDriver_GetType(&testDriver));
}

