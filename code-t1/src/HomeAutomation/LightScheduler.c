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

static void resetRandomize(ScheduledLightEvent * e);

static void scheduleEvent(int id, Day day, int minuteOfDay, int event,
        int randomize)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minuteOfDay = minuteOfDay;
            eventList[i].event = event;
            eventList[i].randomize = randomize;
            resetRandomize(&eventList[i]);
            break;
        }
    }
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_ON, RANDOM_OFF);
}

void LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_OFF, RANDOM_OFF);
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
            resetRandomize(e);
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

#if 0 
BOOL TimeService_MatchesDayOfWeek(const Time * time, Day day)
{
    int today = time->dayOfWeek;

    if (day == EVERYDAY)
        return TRUE;
    if (day == today)
        return TRUE;
    if (day == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}
#endif 

static BOOL matchesDay(Time * time, ScheduledLightEvent * event)
{
    return TimeService_MatchesDayOfWeek(time, event->day);
}

#if 0
static BOOL matchesDay(Time * time, ScheduledLightEvent * event)
{
    int today = time->dayOfWeek;
    Day day = event->day;

    if (day == EVERYDAY)
        return TRUE;
    if (day == today)
        return TRUE;
    if (day == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}
#endif

static void operateLight(ScheduledLightEvent * lightEvent)
{
    if (TURN_ON == lightEvent->event)
        LightController_TurnOn(lightEvent->id);
    else if (TURN_OFF == lightEvent->event)
        LightController_TurnOff(lightEvent->id);
}

static void resetRandomize(ScheduledLightEvent * e)
{
    if (e->randomize == RANDOM_ON)
        e->randomMinutes = RandomMinute_Get();
    else
        e->randomMinutes = 0;
}

static BOOL eventIsReadyToExecute(Time * time, ScheduledLightEvent * event)
{
    int minute = time->minuteOfDay;

    if (event->id == UNUSED)
        return FALSE;
    if (!matchesDay(time, event))
        return FALSE;
    if (minute != event->minuteOfDay + event->randomMinutes)
        return FALSE;
    return TRUE;
}


#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day td = time.dayOfWeek;
    int min = time.minuteOfDay;

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

#endif

#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minuteOfDay = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * event = &eventList[i];
        if (event->id != UNUSED)
        {
            Day day = event->day;
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            {
                /* it's the right day */
                if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
                {
                    if (TURN_ON == event->event)
                    LightController_TurnOn(event->id);
                    else if (TURN_OFF == event->event)
                    LightController_TurnOff(event->id);

                    if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                    else
                    event->randomMinutes = 0;

                }
            }
        }
    }
}
#endif

#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minuteOfDay = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * event = &eventList[i];
        if (event->id != UNUSED)
        {
            Day day = event->day;
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            {
                /* it's the right day */
                if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
                {
                    if (TURN_ON == event->event)
                        LightController_TurnOn(event->id);
                    else if (TURN_OFF == event->event)
                        LightController_TurnOff(event->id);

                    if (event->randomize == RANDOM_ON)
                        event->randomMinutes = RandomMinute_Get();
                    else
                        event->randomMinutes = 0;
                }
            }
        }
    }
}
#endif

#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minuteOfDay = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        /* if (eventIsReadyToExecute()) */
        /*     operateLight(); */
        ScheduledLightEvent * event = &eventList[i];
        if (event->id != UNUSED)
        {
            Day day = event->day;
            /* if (matchesDay()) */
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            {
                /* it's the right day */
                if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
                {
                    /* operateLight() */
                    if (TURN_ON == event->event)
                        LightController_TurnOn(event->id);
                    else if (TURN_OFF == event->event)
                        LightController_TurnOff(event->id);

                    /* resetRandomize(); */
                    if (event->randomize == RANDOM_ON)
                        event->randomMinutes = RandomMinute_Get();
                    else
                        event->randomMinutes = 0;
                }
            }
        }
    }
}
#endif

#if 0
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minuteOfDay = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        /* if (eventIsReadyToExecute()) */
        /*     operateLight(); */
        ScheduledLightEvent * event = &eventList[i];
        if (event->id != UNUSED)
        {
            /* if (matchesDay(time, event)) */
            Day day = event->day;
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))

            {
                /* it's the right day */
                if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
                {
                    /* operateLight(event); */
                    if (TURN_ON == event->event)
                        LightController_TurnOn(event->id);
                    else if (TURN_OFF == event->event)
                        LightController_TurnOff(event->id);

                    /* resetRandomize(event); */
                    if (event->randomize == RANDOM_ON)
                        event->randomMinutes = RandomMinute_Get();
                    else
                        event->randomMinutes = 0;

                }
            }
        }
    }
}
#endif

#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minuteOfDay = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * event = &eventList[i];
        /* if (eventIsReadyToExecute(&time, event)) */
        /*     operateLight(event); */
        if (event->id != UNUSED)
        {
            if (matchesDay(&time, event))
            {
                /* it's the right day */
                if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
                {
                    operateLight(event);
                    resetRandomize(event);
                }
            }
        }
    }
}
#endif

#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minuteOfDay = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * event = &eventList[i];
        /* if (eventIsReadyToExecute(&time, event)) */
        /*     operateLight(event); */
        /*     resetRandomize(event); */
        if (event->id == UNUSED)
            continue;
        if (!matchesDay(&time, event))
            continue;
        if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif

void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    if (eventIsReadyToExecute(time, event))
    {
        operateLight(event);
        resetRandomize(event);
    }
}

#if 1 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventsDueNow(&time, &eventList[i]);
    }
}
#endif 

#if 0 
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * event = &eventList[i];
        if (eventIsReadyToExecute(&time, event))
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif 

#if 0
#if 0
Day day = event->day;
if (!(day == EVERYDAY || day == today
                ||(day == WEEKEND && (SATURDAY == today
                                || SUNDAY == today)) || (day == WEEKDAY
                        && today >= MONDAY && today <= FRIDAY)))
return;
#else
if (!matchesToday(event))
return;
#endif
#endif

