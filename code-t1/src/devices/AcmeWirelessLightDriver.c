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


#include "AcmeWirelessLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

typedef struct AcmeWirelessLightDriverStruct * AcmeWirelessLightDriver;
typedef struct AcmeWirelessLightDriverStruct
{
    LightDriverStruct base;
    const char * ssid;
    const char * key;
    int channel;
} AcmeWirelessLightDriverStruct;


LightDriver AcmeWirelessLightDriver_Create(int id, const char * ssid, const char * key, int channel)
{
     AcmeWirelessLightDriver self = calloc(1, sizeof(AcmeWirelessLightDriverStruct));
     self->base.type = AcmeWireless ;
     self->base.id = id;
     self->ssid = ssid;
     self->key = key;
     self->channel = channel;
     return (LightDriver)self;
}

void AcmeWirelessLightDriver_Destroy(LightDriver super)
{
    free(super);
}

void AcmeWirelessLightDriver_TurnOn(LightDriver super)
{
    explodesInTestEnvironment(super);
}

void AcmeWirelessLightDriver_TurnOff(LightDriver super)
{
    explodesInTestEnvironment(super);
}
