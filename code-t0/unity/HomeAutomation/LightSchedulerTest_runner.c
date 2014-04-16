/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

/* Generated code, edit at your own risk */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightScheduler)
{
    RUN_TEST_CASE(LightScheduler, CreateDoesNotChangeTheLights);
    RUN_TEST_CASE(LightScheduler, CreateStartsOneMinuteAlarm);
    RUN_TEST_CASE(LightScheduler, NoChangeToLightsDuringInitialization);
    RUN_TEST_CASE(LightScheduler, NoScheduleNothingHappens);
    RUN_TEST_CASE(LightScheduler, ScheduleOnTodayNotTimeYet);
    RUN_TEST_CASE(LightScheduler, WeekdayScheduleNotOperatedOnSunday);
    RUN_TEST_CASE(LightScheduler, WeekdayScheduleIsOperatedOnMonday);
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
    RUN_TEST_CASE(LightScheduler, RemoveRecyclesEventSlot);
    RUN_TEST_CASE(LightScheduler, MultipleScheduledEventsSameTime);
    RUN_TEST_CASE(LightScheduler, MultipleScheduledEventsDifferentTimes);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsFriday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsSaturday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsSunday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEndItsMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekEnd);
}
