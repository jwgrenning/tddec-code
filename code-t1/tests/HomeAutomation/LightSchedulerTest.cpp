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

TEST_GROUP(LightScheduler)
{
    int scheduledMinute;
    int expectedId;
    int expectedLevel;
    int lightNumber;

    void setup()
    {
		LightController_Create();
		LightDriverSpy_Reset();
		LightDriverSpy_AddSpiesToController();
		LightScheduler_Create();

		scheduledMinute = 1234;
		lightNumber = 4;
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

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, scheduledMinute);
    setTimeTo(MONDAY, scheduledMinute-1);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnTodayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, scheduledMinute);
    setTimeTo(MONDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, scheduledMinute);
    setTimeTo(MONDAY, scheduledMinute);
        LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, scheduledMinute);
    setTimeTo(TUESDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(lightNumber, TUESDAY, scheduledMinute);
    setTimeTo(TUESDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_OFF);
}

//START: refactored
TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(lightNumber, WEEKEND, scheduledMinute);
    setTimeTo(SATURDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_OFF);
}
//END: refactored

#if 0 //START: GivWenZen
TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAtTheScheduledTime)
{
    given(lightNumber); isScheduledFor(WEEKEND); toTurnOffAt(scheduledMinute);
    setTimeTo(SATURDAY); at(scheduledMinute);
    then(lightNumber); is(LIGHT_OFF);
}
#endif //END: GivWenZen

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
	setTimeTo(SUNDAY, scheduledMinute);
	LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
	LightScheduler_ScheduleTurnOff(lightNumber, WEEKEND, scheduledMinute);
	setTimeTo(MONDAY, scheduledMinute);
	LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
	setTimeTo(SUNDAY, scheduledMinute);
	LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	setTimeTo(MONDAY, scheduledMinute);
	LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}

//START: cut-paste-tweak-repeat-refactored
TEST(LightScheduler, ScheduleWeekEndFridayExcluded)
{
    LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
    setTimeTo(FRIDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekEndSaturdayIncluded)
{
    LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
    setTimeTo(SATURDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndSundayIncluded)
{
    LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
    setTimeTo(SUNDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndMondayExcluded)
{
    LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
    setTimeTo(MONDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
//END:  cut-paste-tweak-repeat-refactored


TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, scheduledMinute);
    LightScheduler_ScheduleRemove(6, MONDAY, scheduledMinute);

	setTimeTo(MONDAY, scheduledMinute);
	LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, MultipleScheduledEventsSameTime)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(3, MONDAY, scheduledMinute);

    setTimeTo(MONDAY, scheduledMinute);
    LightScheduler_WakeUp();

    checkLightState(4, LIGHT_OFF);
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, MultipleScheduledEventsDifferentTimes)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(3, MONDAY, scheduledMinute+1);

    setTimeTo(MONDAY, scheduledMinute);
    LightScheduler_WakeUp();
    checkLightState(4, LIGHT_OFF);

    setTimeTo(MONDAY, scheduledMinute+1);
    LightScheduler_WakeUp();
    checkLightState(3, LIGHT_ON);
}

