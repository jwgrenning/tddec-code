/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
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

#include "unity_fixture.h"

#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"

TEST_GROUP(LightScheduler);

static int id;
static Day fakeDay;
static Day scheduledDay;
static int fakeMinute;
static int scheduledMinute;

TEST_SETUP(LightScheduler)
{
  LightController_Create();
  LightScheduler_Create();

  id = 4;
  fakeDay = MONDAY;
  scheduledDay = NONE;
  fakeMinute = 1234;
  scheduledMinute = 1234;
}

TEST_TEAR_DOWN(LightScheduler)
{
   LightScheduler_Destroy();
}

#if 0 
static void setTimeTo(int day, int minuteOfDay)
 {
     FakeTimeService_SetDay(day);
     FakeTimeService_SetMinute(minuteOfDay);
 }
static void checkLightState(int id, int level)
 {
     TEST_ASSERT_EQUAL(id, LightControllerSpy_GetLastId());
     TEST_ASSERT_EQUAL(level, LightControllerSpy_GetLastState());
 }
 #endif 
static void setTimeTo(int day, int minute)
 {
     FakeTimeService_SetDay(day);
     FakeTimeService_SetMinute(minute);
 }
static void checkLightState(int id, int level)
  {
      if (id == LIGHT_ID_UNKNOWN)
      {
          TEST_ASSERT_EQUAL(id, LightControllerSpy_GetLastId());
          TEST_ASSERT_EQUAL(level, LightControllerSpy_GetLastState());
      }
      else
          TEST_ASSERT_EQUAL(level, LightControllerSpy_GetLightState(id));
  }



TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    TEST_ASSERT_EQUAL(NONE, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(NONE, LightControllerSpy_GetLastState());
}

TEST_GROUP(LightSchedulerInitAndCleanup);

TEST_SETUP(LightSchedulerInitAndCleanup)
{
}

TEST_TEAR_DOWN(LightSchedulerInitAndCleanup)
{
}


TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    TEST_ASSERT_POINTERS_EQUAL((void *)LightScheduler_Wakeup,
                   (void *)FakeTimeSource_GetAlarmCallback());
    TEST_ASSERT_EQUAL(60, FakeTimeSource_GetAlarmPeriod());
    LightScheduler_Destroy();
}


TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    TEST_ASSERT_POINTERS_EQUAL(NULL, (void *)FakeTimeSource_GetAlarmCallback());
}



/**********
 The first few tests looked like this, then I refactored them
 to remove the duplication.
 */
#if 0 
TEST_GROUP(LightScheduler);

TEST_SETUP(LightScheduler)
{
  LightController_Create();
  LightScheduler_Create();
}

TEST_TEAR_DOWN(LightScheduler)
{
   LightScheduler_Destroy();
   LightController_Destroy();
}


TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);

    LightScheduler_Wakeup();

    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);

    LightScheduler_Wakeup();

    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    TEST_ASSERT_EQUAL(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    TEST_ASSERT_EQUAL(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}
TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}
TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    TEST_ASSERT_EQUAL(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
#endif

TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

#if 0 
TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
#endif 

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTIme)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

    setTimeTo(SUNDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
    checkLightState(12, LIGHT_ON);
}

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

TEST(LightScheduler, RejectsTooManyEvents)
{
    int i;
    for (i = 0; i < 128; i++)
        TEST_ASSERT_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    TEST_ASSERT_EQUAL(LS_TOO_MANY_EVENTS,
                LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, AcceptsValidLightIds)
{
    TEST_ASSERT_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    TEST_ASSERT_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    TEST_ASSERT_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

TEST(LightScheduler, RejectsInvalidLightIds)
{
    TEST_ASSERT_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    TEST_ASSERT_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot)
{
    int i;
    for (i = 0; i < 128; i++)
        TEST_ASSERT_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    TEST_ASSERT_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

