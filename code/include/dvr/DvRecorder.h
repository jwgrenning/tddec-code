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


#ifndef D_DvRecorder_H
#define D_DvRecorder_H

typedef struct Program
{
    const char * name;
    int repeat;
    int channel;
    int startHour;
    int startMinute;
    int durationInMinutes;
    int priority;
    int preferences;
} Program;

enum {
    ALL_EPISODES, NEW_EPISODES, REPEATED_EPISODES,
    REPEAT, NO_REPEAT,
    LOW_PRIORITY, MEDIUM_PRIORITY, HIGH_PRIORITY
};

typedef struct
{
    int programCount;
    Program programs[100];
    /* etc... */
} DvRecorder;

void DvrRecorder_Create(void);
void DvRecorder_RestorePrograms(DvRecorder *);

void DvRecorder_Destroy(void);

#endif  /* D_DvRecorder_H */
