/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/* Generated code, edit at your own risk */

#include "unity_fixture.h"

/* Make sure you invoke RUN_TEST_GROUP(LightScheduler) from unity main */

TEST_GROUP_RUNNER(LightScheduler)
{
    RUN_TEST_CASE(LightScheduler, CreateDoesNotChangeTheLights);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsFriday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsSaturday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsSunday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleTwoEventsAtTheSameTIme);
    RUN_TEST_CASE(LightScheduler, ScheduleEverydayNotTimeYet);
    RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayButItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime);
    RUN_TEST_CASE(LightScheduler, RemoveScheduledEvent);
    RUN_TEST_CASE(LightScheduler, RemoveMultipleScheduledEvent);
    RUN_TEST_CASE(LightScheduler, RejectsTooManyEvents);
    RUN_TEST_CASE(LightScheduler, AcceptsValidLightIds);
    RUN_TEST_CASE(LightScheduler, RejectsInvalidLightIds);
    RUN_TEST_CASE(LightScheduler, RemoveRecyclesScheduleSlot);
}

/* Make sure you invoke RUN_TEST_GROUP(LightSchedulerInitAndCleanup) from unity main */

TEST_GROUP_RUNNER(LightSchedulerInitAndCleanup)
{
    RUN_TEST_CASE(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm);
    RUN_TEST_CASE(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm);
}

