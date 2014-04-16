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


#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}


TEST_GROUP(LightScheduler)
{
    int id;
    Day fakeDay;
    Day scheduledDay;
    int fakeMinute;
    int scheduledMinute;

    void setup()
    {
      LightController_Create();
      LightScheduler_Create();

      id = 4;
      fakeDay = MONDAY;
      scheduledDay = NONE;
      fakeMinute = 1234;
      scheduledMinute = 1234;
    }

    void teardown()
    {
       LightScheduler_Destroy();
    }

    #if 0 //START: helpers_1
     void setTimeTo(int day, int minuteOfDay)
     {
         FakeTimeService_SetDay(day);
         FakeTimeService_SetMinute(minuteOfDay);
     }
     void checkLightState(int id, int level)
     {
         LONGS_EQUAL(id, LightControllerSpy_GetLastId());
         LONGS_EQUAL(level, LightControllerSpy_GetLastState());
     }
     #endif //END: helpers_1
     void setTimeTo(int day, int minute)
     {
         FakeTimeService_SetDay(day);
         FakeTimeService_SetMinute(minute);
     }
     //START: helpers_2
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
      //END: helpers_2

};

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    LONGS_EQUAL(NONE, LightControllerSpy_GetLastId());
    LONGS_EQUAL(NONE, LightControllerSpy_GetLastState());
}

//START:CreateStartsOneMinuteAlarm
TEST_GROUP(LightSchedulerInitAndCleanup)
{
};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void *)LightScheduler_Wakeup,
                   (void *)FakeTimeService_GetAlarmCallback());
				   
    LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destroy();
}
//END:CreateStartsOneMinuteAlarm

//START: DestroyCancelsOneMinuteAlarm
TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    POINTERS_EQUAL(NULL, (void *)FakeTimeService_GetAlarmCallback());
}

//END: DestroyCancelsOneMinuteAlarm


/**********
 The first few tests looked like this, then I refactored them
 to remove the duplication.
 */
#if 0 // START: testGroup1
TEST_GROUP(LightScheduler)
{
    void setup()
    {
      LightController_Create();
      LightScheduler_Create();
    }

    void teardown()
    {
       LightScheduler_Destroy();
       LightController_Destroy();
    }
};
// END: testGroup1

// START: NoChangeToLightsDuringInitialization
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
// END: NoChangeToLightsDuringInitialization

// START: NoScheduleNothingHappens
TEST(LightScheduler, NoScheduleNothingHappens)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_Wakeup();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
// END: NoScheduleNothingHappens
// START: ScheduleOnTodayNotTimeYet_1
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_Wakeup();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
// END: ScheduleOnTodayNotTimeYet_1
// START: ScheduleOnEverydayItsTime
TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
// END: ScheduleOnEverydayItsTime
// START: ScheduleOffEverydayItsTime
TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();

    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}
// END: ScheduleOffEverydayItsTime
//START: ScheduleTuesdayButItsMonday
TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
//END: ScheduleTuesdayButItsMonday
//START: ScheduleTuesdayAndItsTuesday
TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}
//END: ScheduleTuesdayAndItsTuesday
//START: WeekdayScheduleNotOperatedOnSunday
TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
//END: WeekdayScheduleNotOperatedOnSunday
//START: WeekdayScheduleIsOperatedOnMonday
TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
//END:WeekdayScheduleIsOperatedOnMonday
#endif

//START: ScheduleWeekEndItsFriday
TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
//END: ScheduleWeekEndItsFriday
//START: fourPhaseTest
//START: ScheduleWeekEndItsSaturday
TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}
//END: fourPhaseTest
//END: ScheduleWeekEndItsSaturday

//START: ScheduleWeekEndItsSunday
TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}
//END: ScheduleWeekEndItsSunday

//START: ScheduleWeekEndItsMonday
TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
//END: ScheduleWeekEndItsMonday

#if 0 //START: ScheduleWeekEndItsMonday_2
TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
#endif //END: ScheduleWeekEndItsMonday_2

//START: ScheduleTwo
TEST(LightScheduler, ScheduleTwoEventsAtTheSameTIme)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

    setTimeTo(SUNDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
    checkLightState(12, LIGHT_ON);
}
//END: ScheduleTwo

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, 100);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, scheduledMinute);
    setTimeTo(SUNDAY, scheduledMinute);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayButItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);
    setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);
    setTimeTo(TUESDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, TUESDAY, 200);
    setTimeTo(TUESDAY, 200);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, WEEKEND, 200);
    setTimeTo(SATURDAY, 200);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);
    setTimeTo(SUNDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);
    setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 100);
    setTimeTo(SUNDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 200);
    setTimeTo(MONDAY, 200);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);
    setTimeTo(FRIDAY, 1000);
    LightScheduler_Wakeup();
    checkLightState(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);
    setTimeTo(SATURDAY, 1000);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    setTimeTo(MONDAY, 599);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//START: RemoveMultipleScheduledEvent
TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    setTimeTo(MONDAY, 600);

    LightScheduler_Wakeup();

    checkLightState(6, LIGHT_STATE_UNKNOWN);
    checkLightState(7, LIGHT_ON);
}
//END: RemoveMultipleScheduledEvent

//START: RejectsTooManyEvents
TEST(LightScheduler, RejectsTooManyEvents)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LONGS_EQUAL(LS_TOO_MANY_EVENTS,
                LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}
//END: RejectsTooManyEvents

//START: CheckLightIds
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
//END: CheckLightIds

//START: RemoveRecyclesEventSlot
TEST(LightScheduler, RemoveRecyclesScheduleSlot)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}
//END: RemoveRecyclesEventSlot

