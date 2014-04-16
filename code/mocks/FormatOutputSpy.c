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


#include "FormatOutputSpy.h"
#include "CppUTest/TestHarness_c.h"
#include <stdio.h>
#include <stdarg.h>
#define WINDOWS_VSNPRINTF_OVERWRITE -1
#if WIN32
#define vsnprintf _vsnprintf
#endif

#include <stdlib.h>
#include <stdarg.h>
static char * buffer = 0;
static size_t buffer_size = 0;
static int buffer_offset = 0;
static int buffer_used = 0;

void FormatOutputSpy_Create(int size)
{
    FormatOutputSpy_Destroy();
    buffer_size = size+1;
    buffer = (char *)calloc(buffer_size, sizeof(char));
    buffer_offset = 0;
    buffer_used = 0;
    buffer[0] = '\0';
}

void FormatOutputSpy_Destroy(void)
{
    if (buffer == 0)
        return;

    free(buffer);
    buffer = 0;
}

int FormatOutputSpy(const char * format, ...)
{
    int written_size;
    va_list arguments;
    va_start(arguments, format);
    written_size = vsnprintf(buffer + buffer_offset,
                buffer_size - buffer_used, format, arguments);

	if (written_size == WINDOWS_VSNPRINTF_OVERWRITE)
    {
        written_size = buffer_size - buffer_used;
        buffer[buffer_offset + written_size - 1] = 0;
    }

    buffer_offset += written_size;
    buffer_used += written_size;
    va_end(arguments);
    return 1;
}
const char * FormatOutputSpy_GetOutput(void)
{
    return buffer;
}
