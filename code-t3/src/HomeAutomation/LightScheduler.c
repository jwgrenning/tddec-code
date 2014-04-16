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
    MAX_EVENTS = 64, UNUSED = -1
};

typedef struct
{
    int id;
    Day day;
    long int minuteOfDay;
    int event;
    int randomize;
    int randomMinutes;

} ScheduledLightEvent;

static ScheduledLightEvent eventList[MAX_EVENTS];

void LightScheduler_Create(void)
{
    int i;
    ScheduledLightEvent * event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        event->id = UNUSED;
    }
}

void LightScheduler_Destroy(void)
{
}

static void resetRandomize(ScheduledLightEvent * e);

#if 1 
static void setEventSchedule(ScheduledLightEvent * event,
        int id, Day day, long int minute, int control, int randomize)
{
        event->id = id;
        event->day = day;
        event->minuteOfDay = minute;
        event->event = control;
        event->randomize = randomize;
        resetRandomize(event);
}
#endif 

static BOOL isInUse(ScheduledLightEvent * event)
{
    return event->id != UNUSED;
}

#if 1 
static ScheduledLightEvent * findUnusedEvent(void)
{
    int i;
    ScheduledLightEvent * event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        if (!isInUse(event))
            return event;
    }
    return NULL;
}
#endif 

#if 0 
static ScheduledLightEvent * findUnusedEvent(void)
{
    int i;
    ScheduledLightEvent * event = 0;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
        {
            event = &eventList[i];
            return event;
        }
    }
    return NULL;
}
#endif 

#if 1 
static void scheduleEvent(int id, Day day, long int minute, int control,
        int randomize)
{

    ScheduledLightEvent * event = findUnusedEvent();

    if (event)
        setEventSchedule(event, id, day, minute, control, randomize);
}
#endif 

#if 0 
static void scheduleEvent(int id, Day day, long int minuteOfDay, int control,
        int randomize)
{

    ScheduledLightEvent * event = findUnusedEvent(void);

    if (event)
    {
         event->id = id;
         event->day = day;
         event->minuteOfDay = minuteOfDay;
         event->event = control;
         event->randomize = randomize;
         resetRandomize(event);

    }
}
#endif 


void LightScheduler_ScheduleTurnOn(int id, Day day, long int minute)
{
    scheduleEvent(id, day, minute, TURN_ON, RANDOM_OFF);
}

void LightScheduler_ScheduleTurnOff(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURN_OFF, RANDOM_OFF);
}

static BOOL matchEvent(ScheduledLightEvent * e, int id, Day day, long int minute)
{
    return e->id == id && e->day == day && e->minuteOfDay == minute;
}

void LightScheduler_Randomize(int id, Day day, long int minute)
{
    int i;
    ScheduledLightEvent * event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        if (matchEvent(event, id, day, minute))
        {
            event->randomize = RANDOM_ON;
            resetRandomize(event);
        }
    }
}

void LightScheduler_ScheduleRemove(int id, Day day, long int minute)
{
    int i;
    ScheduledLightEvent * event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        if (matchEvent(event, id, day, minute))
            event->id = UNUSED;
    }
}

static void operateLight(ScheduledLightEvent * event)
{
    if (event->event == TURN_ON)
        LightController_TurnOn(event->id);
    else if (TURN_OFF == event->event)
        LightController_TurnOff(event->id);
}

static void resetRandomize(ScheduledLightEvent * event)
{
    if (event->randomize == RANDOM_ON)
        event->randomMinutes = RandomMinute_Get();
    else
        event->randomMinutes = 0;
}

#if 0 
static void scheduleEvent(int id, Day day, long int minuteOfDay, int control,
        int randomize)
{
    int i;
    ScheduledLightEvent * event = 0;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
       {
            event = &eventList[i];
            break;
        }
    }

    if (event)
    {
        event->id = id;
        event->day = day;
        event->minuteOfDay = minuteOfDay;
        event->event = control;
        event->randomize = randomize;
        resetRandomize(event);
    }
}
#endif 

#if 0 
static void scheduleEvent(int id, Day day, long int minuteOfDay, int control,
        int randomize)
{
    int i;
    ScheduledLightEvent * event = 0;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
        {
            event = &eventList[i];
            event->id = id;
            event->day = day;
            event->minuteOfDay = minuteOfDay;
            event->event = control;
            event->randomize = randomize;
            resetRandomize(event);
            break;
        }
    }
}
#endif 

#if 0 
static void scheduleEvent(int id, Day day, long int minuteOfDay, int control,
        int randomize)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minuteOfDay = minuteOfDay;
            eventList[i].event = control;
            eventList[i].randomize = randomize;
            resetRandomize(&eventList[i]);
            break;
        }
    }
}
#endif 

#if 0 
BOOL Time_MatchesMinuteOfDay(Time * time, int minuteOfDay)
{
     return time->minuteOfDay == minuteOfDay;
}
#endif 

#if 0 
BOOL Time_MatchesDayOfWeek(Time * time, Day day)
{
    int today = time->dayOfWeek;

    if (day == EVERYDAY)
        return TRUE;
    if (day == today)
        return TRUE;
    if (day == WEEKEND && (today == SATURDAY || today == SUNDAY))
        return TRUE;
    if (day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}
#endif 

#if 0 
static BOOL daysMatch(Day today, Day scheduledDay)
{
    if (scheduledDay == EVERYDAY)
        return TRUE;
    if (scheduledDay == today)
        return TRUE;
    if (scheduledDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
        return TRUE;
    if (scheduledDay == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
        return TRUE;
    return FALSE;
}
#endif 

#if 0 
static BOOL daysMatch(Day scheduledDay, Day today)
{
    if (scheduledDay == EVERYDAY)
        return TRUE;
    if (scheduledDay == today)
        return TRUE;
    if (scheduledDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
        return TRUE;
    if (scheduledDay == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
        return TRUE;
    return FALSE;
}
#endif 

#if 0 
static BOOL daysMatch(Day scheduledDay, Day today)
{
    if ((day == EVERYDAY) || (day == today)
             || (day == WEEKEND &&
                (today == SATURDAY || today == SUNDAY))
             || (day == WEEKDAY && (today >= MONDAY
             && today <= FRIDAY)))
        return TRUE;
    return FALSE;
}
#endif 

#if 0 
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    int minuteOfDay = time->minuteOfDay;
    Day day = event->day;

    if (minuteOfDay != event->minuteOfDay + event->randomMinutes)
        return FALSE;

    if (!Time_MatchesDayOfWeek(time, day))
        return FALSE;

    return TRUE;
}
#endif 

#if 0 
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    int minuteOfDay = time->minuteOfDay;
    Day day = event->day;

    if (minuteOfDay != event->minuteOfDay + event->randomMinutes)
        return FALSE;

    if (!daysMatch(time, day))
        return FALSE;

    return TRUE;
}
#endif 

#if 0 
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;
    Day day = event->day;

    if (minuteOfDay != event->minuteOfDay + event->randomMinutes)
        return FALSE;

#if 1
    if (daysMatch(today, day))
        return TRUE;
#else
    if ( (day == EVERYDAY) || (day == today)
             || (day == WEEKEND &&
             (today == SATURDAY || today == SUNDAY))
             || (day == WEEKDAY && (today >= MONDAY
             && today <= FRIDAY)))
        return TRUE;
#endif
    return FALSE;
}
#endif 

#if 0 
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;
    Day day = event->day;

    if (minuteOfDay != event->minuteOfDay + event->randomMinutes)
        return FALSE;

    if ( (day == EVERYDAY) || (day == today)
            || (day == WEEKEND &&
               (today == SATURDAY || today == SUNDAY))
            || (day == WEEKDAY && (today >= MONDAY
            && today <= FRIDAY)))
        return TRUE;

    return FALSE;
}
#endif 

#if 0 
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;
    Day day = event->day;
    if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
        (today == SATURDAY || today == SUNDAY)) ||
        (day == WEEKDAY && (today >= MONDAY
                        && today <= FRIDAY)))
    {
        if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
            return TRUE;
    }
    return FALSE;
}
#endif 

#if 1 
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    int todaysMinute = event->minuteOfDay + event->randomMinutes;
    Day day = event->day;

    if (!Time_MatchesMinuteOfDay(time, todaysMinute))
        return FALSE;

    if (!Time_MatchesDayOfWeek(time, day))
        return FALSE;

    return TRUE;
}
#endif 

#if 1 
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    if (isInUse(event))
    {
        if (isEventDueNow(time, event))
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif  

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
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    if (event->id != UNUSED)
    {
        if (isEventDueNow(time, event))
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif  

#if 0 
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        /* if (isEventDueNow()) */
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                (today == SATURDAY || today == SUNDAY)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
            if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
            {
                operateLight(event);

                /* resetRandomize(); */
                if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                else
                    event->randomMinutes = 0;
            }
        }
    }
}
#endif  

#if 0
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        /* if (isEventDueNow()) */
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                (today == SATURDAY || today == SUNDAY)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
            if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
            {
                /* operateLight(event); */
                if (event->event == TURN_ON)
                    LightController_TurnOn(event->id);
                else if (event->event == TURN_OFF)
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
#endif



#if 0 
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        /* if (isEventDueNow()) */
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                (today == SATURDAY || today == SUNDAY)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
            if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
            {
                /* operateLight(); */
                if (event->event == TURN_ON)
                    LightController_TurnOn(event->id);
                else if (event->event == TURN_OFF)
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
#endif 

#if 0 
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minuteOfDay = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                (today == SATURDAY || today == SUNDAY)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
            /* it's the right day */
            if (minuteOfDay == event->minuteOfDay + event->randomMinutes)
            {
                if (event->event == TURN_ON)
                    LightController_TurnOn(event->id);
                else if (event->event == TURN_OFF)
                    LightController_TurnOff(event->id);

                if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                else
                    event->randomMinutes = 0;
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
    Day td = time.dayOfWeek;
    int min = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent * se = &eventList[i];
        if (se->id != UNUSED)
        {
            Day d = se->day;
            if ( (d == EVERYDAY) || (d == td) || (d == WEEKEND &&
                    (td == SATURDAY || td == SUNDAY)) ||
                    (d == WEEKDAY && (td >= MONDAY
                                    && td <= FRIDAY)))
            {
                /* it's the right day */
                if (min == se->minuteOfDay + se->randomMinutes)
                {
                    if (se->event == TURN_ON)
                        LightController_TurnOn(se->id);
                    else if (se->event == TURN_OFF)
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

