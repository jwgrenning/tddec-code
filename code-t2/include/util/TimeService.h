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


#ifndef D_TimeService_H
#define D_TimeService_H

#include "common.h"

typedef enum Day {
    EVERYDAY=-3, WEEKDAY=-2, WEEKEND=-1,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Day;

typedef enum Month {
    JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
} Month;

typedef struct Time Time;

struct Time
{
    int usec;
    int sec;
    int minuteOfDay;
    int minuteOfHour;
    Day dayOfWeek;
    int dayOfMonth;
    Month month;
};

void TimeService_Create(void);
void TimeService_Destroy(void);
int TimeService_GetMinute(void);
int TimeService_GetDay(void);

void TimeService_GetTime(Time *);

BOOL Time_MatchesDayOfWeek(Time *, Day day);
BOOL Time_MatchesMinuteOfDay(Time *, int minute);

#endif  /* D_TimeService_H */
