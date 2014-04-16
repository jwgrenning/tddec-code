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


TEST_GROUP(LightScheduler)
{
    int id;

    void setup()
    {
      LightController_Create();
      LightScheduler_Create();
    }

    //START: DestroyCancelsOneMinuteAlarm
    void teardown()
    {
       LightScheduler_Destroy();
//       POINTERS_EQUAL(NULL, (void *)FakeTimeSource_GetAlarmCallback());
    }
    //END:DestroyCancelsOneMinuteAlarm

};

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, CreateStartsOneMinuteAlarm)
{
//    POINTERS_EQUAL((void *)LightScheduler_WakeUp,
//                   (void *)FakeTimeSource_GetAlarmCallback());
//    LONGS_EQUAL(60, FakeTimeSource_GetAlarmPeriod());
}

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnTodayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200); //<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.sched" />
    FakeTimeService_SetMinute(1199); //<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.SetTime" />
    LightScheduler_WakeUp();//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.wake" />
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.chk1" />
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.chk2" />
}

TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
TEST(LightScheduler, ScheduleTwoEventsAtTheSameTIme)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_WakeUp();

    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(3));
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(12));
}

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, 100);

    FakeTimeService_SetMinute(99);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, 200);
    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayButItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);
    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(TUESDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, TUESDAY, 200);
    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(TUESDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}

//START: refactorThis
TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, WEEKEND, 200);

    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(SATURDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}
//END: refactorThis

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(SUNDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(SUNDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 200);

    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);

    FakeTimeService_SetMinute(1000);
    FakeTimeService_SetDay(FRIDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);

    FakeTimeService_SetMinute(1000);
    FakeTimeService_SetDay(SATURDAY);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(6000);

    LightScheduler_WakeUp();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);

    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(7, MONDAY, 600);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(600);

    LightScheduler_WakeUp();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, RejectsTooManyEvents)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LONGS_EQUAL(LS_TOO_MANY_EVENTS,
            LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, AcceptsValidLightIds)
{
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

TEST(LightScheduler, RejectsInvalidLightIds)
{
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}

TEST(LightScheduler, RemoveRecyclesEventSlot)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

TEST(LightScheduler, MultipleScheduledEventsSameTime)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, 500);
    LightScheduler_ScheduleTurnOn(3, MONDAY, 500);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(500);

    LightScheduler_WakeUp();
    LONGS_EQUAL(2, LightControllerSpy_GetEventCounts());
}

TEST(LightScheduler, MultipleScheduledEventsDifferentTimes)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(3, MONDAY, 500);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(500);

    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());

    FakeTimeService_SetMinute(600);

    LightScheduler_WakeUp();
    LONGS_EQUAL(4, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(FRIDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 100);
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(1, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(6, WEEKEND, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(6, LightControllerSpy_GetLastId());
    LONGS_EQUAL(1, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

//START: rambleOn
TEST(LightScheduler, ScheduleWeekEnd)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(FRIDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(1, LightControllerSpy_GetLastState());
    LightController_TurnOff(3);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(1, LightControllerSpy_GetLastState());
    LightController_Create();
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
//END: rambleOn

//START: rambleOn-refactored
TEST(LightScheduler, ScheduleWeekEndFridayExcluded)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(FRIDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekEndSaturdayIncluded)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(1, LightControllerSpy_GetLastState());
 }

TEST(LightScheduler, ScheduleWeekEndSundayIncluded)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(1, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekEndMondayExcluded)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
//END: rambleOn-refactored



