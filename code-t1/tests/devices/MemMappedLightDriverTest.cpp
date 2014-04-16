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
#include "MemMappedLightDriver.h"
}

#include "CppUTest/TestHarness.h"



TEST_GROUP(MemMappedLightDriver)
{
    LightDriver driver;
    uint32_t mockLights;

    void setup()
    {
      driver = MemMappedLightDriver_Create(4, &mockLights);
    }

    void teardown()
    {
       MemMappedLightDriver_Destroy( (LightDriver)driver);
    }
};

TEST(MemMappedLightDriver, Create)
{
    LONGS_EQUAL(MemoryMapped, driver->type);
    LONGS_EQUAL(4, driver->id);
}

