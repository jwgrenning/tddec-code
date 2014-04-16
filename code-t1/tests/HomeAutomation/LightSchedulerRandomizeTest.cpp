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
#include "LightDriverSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}
#include "CppUTest/TestHarness.h"

TEST_GROUP(LightSchedulerRandomize)
{
    int scheduledMinute;
    int expectedId;
    int expectedLevel;
    int lightNumber;
    int firstRandomMinute;


    void setup()
    {
		LightController_Create();
		LightDriverSpy_Reset();
		LightDriverSpy_AddSpiesToController();
		LightScheduler_Create();

		scheduledMinute = 1234;
		lightNumber = 4;

		UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
		FakeRandomMinute_Reset();
		firstRandomMinute = -10;
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }

    //START: helpers
    void setTimeTo(int day, int minute)
    {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minute);
    }

    void checkLightState(int id, int level)
    {
        if (id == LIGHT_ID_UNKNOWN)
            LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetLastState())
        else
            LONGS_EQUAL(level, LightDriverSpy_GetState(id))
    }
    //END: helpers

};


//START: EnableRandomize
TEST(LightSchedulerRandomize, TurnsOnEarly)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);

    FakeTimeService_SetMinute(600-10);

    LightScheduler_WakeUp();

	checkLightState(4, LIGHT_ON);
}
//END: EnableRandomize

//START: EnableRandomize
TEST(LightSchedulerRandomize, EnableRandomize)
{
    FakeRandomMinute_SetFirstAndIncrement(10, 1);

    LightScheduler_ScheduleTurnOn(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_Randomize(lightNumber, EVERYDAY, scheduledMinute);

    setTimeTo(MONDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

    setTimeTo(MONDAY, scheduledMinute + 10);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}
//END: EnableRandomize

TEST(LightSchedulerRandomize, DifferentRandmomFactorTheSecondDay)
{
	FakeRandomMinute_SetFirstAndIncrement(firstRandomMinute, 1);

    LightScheduler_ScheduleTurnOn(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_Randomize(lightNumber, EVERYDAY, scheduledMinute);

    setTimeTo(MONDAY, scheduledMinute + firstRandomMinute);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}

TEST(LightSchedulerRandomize, MultipleRandomControls)
{
	FakeRandomMinute_SetFirstAndIncrement(firstRandomMinute, 5);

    LightScheduler_ScheduleTurnOn(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_Randomize(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(lightNumber+1, EVERYDAY, scheduledMinute+3);
    LightScheduler_Randomize(lightNumber+1, EVERYDAY, scheduledMinute+3);

    setTimeTo(MONDAY, scheduledMinute + firstRandomMinute);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);

    setTimeTo(MONDAY, scheduledMinute +firstRandomMinute + 3 + 5);
    LightScheduler_WakeUp();
    checkLightState(lightNumber+1, LIGHT_ON);
}

