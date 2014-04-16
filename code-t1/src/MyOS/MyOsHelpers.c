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

#include "Thread.h"

static Thread * threadTable = 0;
static int maxThreads = 0;
typedef Thread * ThreadTableEntry;


void MyOs_Init(int maxT)
{
     maxThreads = maxT;
     threadTable = calloc(maxThreads, sizeof(Thread));
}

void MyOs_ShutDown(void)
{
    if (threadTable)
        free(threadTable);
    threadTable = NULL;
}

Thread * MyOs_GetThreadEntry(Thread t)
{
    int i;

    for (i = 0; i < maxThreads; i++)
    {
        if (threadTable[i] == t)
        {
            break;
        }
    }

    return &threadTable[i];
}

Thread * MyOs_FindThreadEntry(ThreadFinder finder, void * key)
{
    int i;

    for (i = 0; i < maxThreads; i++)
    {
        Thread t = threadTable[i];
        if (finder(t, key))
            break;
    }

    return &threadTable[i];
}


void MyOS_AddThreadToTable(Thread thread)
{
    Thread * entry = MyOs_GetThreadEntry(NULL);
    *entry = thread;
}

void MyOs_RemoveThreadFromTable(Thread thread)
{
    ThreadTableEntry entry = MyOs_GetThreadEntry(thread);
    *entry = NULL;
}
