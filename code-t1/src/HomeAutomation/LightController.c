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

#include "LightController.h"
#include <stdlib.h>
#include <memory.h>
#include "X10LightDriver.h"
#include "LightDriverSpy.h"
#include "AcmeWirelessLightDriver.h"
#include "MemMappedLightDriver.h"
#include "common.h"

int lightType = 0;

static LightDriver lightDrivers[MAX_LIGHTS] =
{ NULL };

void LightController_Create(void)
{
    memset(lightDrivers, 0, sizeof lightDrivers);
}

static void destroy(LightDriver driver)
{
    if (!driver)
        return;

    switch (driver->type)
    {
    case X10:
        X10LightDriver_Destroy(driver);
        break;
    case AcmeWireless:
        AcmeWirelessLightDriver_Destroy(driver);
        break;
    case MemoryMapped:
        MemMappedLightDriver_Destroy(driver);
        break;
    case TestLightDriver:
        LightDriverSpy_Destroy(driver);
        break;
    default:
        /* now what? */
        break;
    }
}

void LightController_Destroy(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver driver = lightDrivers[i];
        destroy(driver);
        lightDrivers[i] = NULL;
    }
}

BOOL LightController_Add(int id, LightDriver lightDriver)
{
    if (id < 0 || id >= MAX_LIGHTS)
        return FALSE;

    destroy(lightDrivers[id]);

    lightDrivers[id] = lightDriver;
    return TRUE;
}

void LightController_TurnOn(int id)
{
    LightDriver driver = lightDrivers[id];
    if (NULL == driver)
        return;

    switch (driver->type)
    {
    case X10:
        X10LightDriver_TurnOn(driver);
        break;
    case AcmeWireless:
        AcmeWirelessLightDriver_TurnOn(driver);
        break;
    case MemoryMapped:
        MemMappedLightDriver_TurnOn(driver);
        break;
    case TestLightDriver:
        LightDriverSpy_TurnOn(driver);
        break;
    default:
        /* now what? */
        break;
    }
}

void LightController_TurnOff(int id)
{
    LightDriver driver = lightDrivers[id];
    if (NULL == driver)
        return;

    switch (driver->type)
    {
    case X10:
        X10LightDriver_TurnOff(driver);
        break;
    case AcmeWireless:
        AcmeWirelessLightDriver_TurnOff(driver);
        break;
    case MemoryMapped:
        MemMappedLightDriver_TurnOff(driver);
        break;
    case TestLightDriver:
        LightDriverSpy_TurnOff(driver);
        break;
    default:
        /* now what? */
        break;
    }
}

