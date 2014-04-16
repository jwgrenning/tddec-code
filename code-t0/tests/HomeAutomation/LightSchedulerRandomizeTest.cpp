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
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}
#include "CppUTest/TestHarness.h"

#if 1//START: UT_PTR_SET
TEST_GROUP(LightSchedulerRandomize)
{
    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
        UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }

    void checkLightState(int id, int level)
     {
         if (id == LIGHT_ID_UNKNOWN)
         {
             LONGS_EQUAL(id, LightControllerSpy_GetLastId());
             LONGS_EQUAL(level, LightControllerSpy_GetLastState());
         }
         else
             LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
     }

    void setTimeTo(int day, int minute)
    {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minute);
    }
};
#endif //END: UT_PTR_SET

//START: EnableRandomize
TEST(LightSchedulerRandomize, TurnsOnEarly)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);
    setTimeTo(MONDAY, 600-10);
    LightScheduler_WakeUp();
    checkLightState(4, LIGHT_ON);
}
//END: EnableRandomize

#if 0 //START: manualPtrInitRestore
TEST_GROUP(LightSchedulerRandomize)
{
    int (*savedRandomMinute_Get)();

    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
        savedRandomMinute_Get = RandomMinute_Get;
        RandomMinute_Get = FakeRandomMinute_Get;
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
        RandomMinute_Get = savedRandomMinute_Get;
    }
};
#endif //END: manualPtrInitRestore
