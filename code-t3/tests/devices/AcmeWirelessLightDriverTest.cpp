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
#include "AcmeWirelessLightDriver.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AcmeWirelessLightDriver)
{
    LightDriver lightDriver;

    void setup()
    {
      lightDriver = AcmeWirelessLightDriver_Create(5, "SSID", "decafc0ffee11decafc0ffee22", 3);
    }

    void teardown()
    {
        LightDriver_Destroy(lightDriver);
    }
};

TEST(AcmeWirelessLightDriver, Create)
{
     STRCMP_EQUAL("Acme wireless", LightDriver_GetType(lightDriver));
     LONGS_EQUAL(5, LightDriver_GetId(lightDriver));
}
