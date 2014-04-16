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

#include "CircularBuffer.h"
#include "Utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct CircularBufferStruct
{
    int count;
    int index;
    int outdex;
    int capacity;
    int * values;
} CircularBufferStruct ;

enum {BUFFER_GUARD = -999};

CircularBuffer CircularBuffer_Create(int capacity)
{
    CircularBuffer self = calloc(capacity, sizeof(CircularBufferStruct));
    self->capacity = capacity;
    self->values = calloc(capacity + 1, sizeof(int));
    self->values[capacity] = BUFFER_GUARD;
    return self;
}

void CircularBuffer_Destroy(CircularBuffer self)
{
    free(self->values);
    free(self);
}

int CircularBuffer_VerifyIntegrity(CircularBuffer self)
{
	return self->values[self->capacity] == BUFFER_GUARD;
}

int CircularBuffer_IsEmpty(CircularBuffer self)
{
    return self->count == 0;
}

int CircularBuffer_IsFull(CircularBuffer self)
{
    return self->count == self->capacity;
}

int CircularBuffer_Put(CircularBuffer self, int value)
{
    if (self->count >= self->capacity)
        return 0;

    self->count++;
    self->values[self->index++] = value;
    if (self->index >= self->capacity)
        self->index = 0;

    return 1;
}

int CircularBuffer_Get(CircularBuffer self)
{
	int value;
    if (self->count <= 0)
        return 0;

    value = self->values[self->outdex++];
    self->count--;
    if (self->outdex >= self->capacity)
        self->outdex = 0;

    return value;
}

int CircularBuffer_Capacity(CircularBuffer self)
{
    return self->capacity;
}

void CircularBuffer_Print(CircularBuffer self)
{
    int i;
    int currentValue;

    currentValue = self->outdex;

    FormatOutput("Circular buffer content:\n<");

    for (i = 0; i < self->count; i++) {
        if (i != 0)
            FormatOutput(", ");
        FormatOutput("%d", self->values[currentValue++]);
        if (currentValue >= self->capacity)
            currentValue = 0;
    }

    FormatOutput(">\n");
}
