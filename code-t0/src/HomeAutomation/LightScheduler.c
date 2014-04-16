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


#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"
#include "RandomMinute.h"
#include <stdlib.h>
#include <string.h>

enum
{
    TURN_ON, TURN_OFF, DIM, RANDOM_ON, RANDOM_OFF
};

enum
{
    MAX_EVENTS = 128, UNUSED = -1
};

typedef struct
{
    int id;
    Day day;
    int minuteOfDay;
    int event;
    int randomize;
    int randomMinutes;

} ScheduledLightEvent;

static ScheduledLightEvent eventList[MAX_EVENTS];

void LightScheduler_Create(void)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        eventList[i].id = UNUSED;
    }
}

void LightScheduler_Destroy(void)
{
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    int i;

    if (id < 0 || id >= MAX_LIGHTS)
        return LS_ID_OUT_OF_BOUNDS;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minuteOfDay = minuteOfDay;
            eventList[i].event = TURN_ON;
            eventList[i].randomize = RANDOM_OFF;
            eventList[i].randomMinutes = 0;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    int i;

    if (id < 0 || id >= MAX_LIGHTS)
        return LS_ID_OUT_OF_BOUNDS;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minuteOfDay = minuteOfDay;
            eventList[i].event = TURN_OFF;
            eventList[i].randomize = RANDOM_OFF;
            eventList[i].randomMinutes = 0;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

void LightScheduler_Randomize(int id, Day day, int minuteOfDay)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * e = &eventList[i];
        if (e->id == id && e->day == day && e->minuteOfDay == minuteOfDay)
        {
            e->randomize = RANDOM_ON;
            e->randomMinutes = RandomMinute_Get();
        }
    }
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == id && eventList[i].day == day
                && eventList[i].minuteOfDay == minuteOfDay)
        {
            eventList[i].id = UNUSED;
        }
    }
}

void LightScheduler_WakeUp(void)
{
    int i;
    Time time;
    Day td;
    int min;

    TimeService_GetTime(&time);
    td = time.dayOfWeek;
    min = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * se = &eventList[i];
        if (se->id != UNUSED)
        {
            Day d = se->day;
            if ( (d == EVERYDAY) || (d == td) || (d == WEEKEND &&
                            (SATURDAY == td || SUNDAY == td)) ||
                    (d == WEEKDAY && (td >= MONDAY
                                    && td <= FRIDAY)))
            {
                /* it's the right day */
                if (min == se->minuteOfDay + se->randomMinutes)
                {
                    if (TURN_ON == se->event)
                        LightController_TurnOn(se->id);
                    else if (TURN_OFF == se->event)
                        LightController_TurnOff(se->id);

                    if (se->randomize == RANDOM_ON)
                        se->randomMinutes = RandomMinute_Get();
                    else
                        se->randomMinutes = 0;

                }
            }
        }
    }
}

