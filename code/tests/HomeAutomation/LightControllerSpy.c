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


#include "LightControllerSpy.h"
#include "memory.h"

static int lastId;
static int lastState;
static int count;
static int lights[MAX_LIGHTS];

void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    count = 0;
    memset(lights, LIGHT_STATE_UNKNOWN, sizeof lights);
}

void LightController_Destroy(void)
{
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastState;
}

static int isIdInRange(int id)
{
    return id >= 0 && id <= 31;
}
void LightController_On(int id)
{
    lastId = id;
    lastState = 1;
    count++;
    if (isIdInRange(id))
        lights[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastId = id;
    lastState = 0;
    count++;
    if (isIdInRange(id))
        lights[id] = LIGHT_OFF;
}

int LightControllerSpy_GetEventCounts(void)
{
    return count;
}

int LightControllerSpy_GetLightState(int id)
{
    if (!isIdInRange(id))
        return LIGHT_STATE_UNKNOWN;
    return lights[id];
}

#if 0
#include "LightControllerSpy.h"

static int lastId;
static int lastState;

void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
}

void LightController_On(int id)
{
    lastId = id;
    lastState = LIGHT_ON;
}
void LightController_Off(int id)
{
    lastId = id;
    lastState = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}
int LightControllerSpy_GetLastState(void)
{
    return lastState;
}

#endif
