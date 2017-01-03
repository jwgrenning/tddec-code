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

static void null(LightDriver self) {}

static LightDriverInterfaceStruct doNothing =
{
   null, null, null
};

static LightDriverStruct testDriver =
{
    &doNothing,
    "testDriver",
    13
};

TEST_GROUP(LightDriver)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(LightDriver, NullDriverDoesNoHarm)
{
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
}

TEST(LightDriver, Accessors)
{
    LONGS_EQUAL(13, LightDriver_GetId(&testDriver));
    STRCMP_EQUAL("testDriver", LightDriver_GetType(&testDriver));
}

