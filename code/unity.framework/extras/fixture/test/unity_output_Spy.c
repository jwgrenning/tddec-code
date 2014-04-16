/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
//- Copyright (c) 2010 James Grenning and Contributed to Unity Project
/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */


#include "unity_output_Spy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int size;
static int count;
static char* buffer;
static int spy_enable;

void UnityOutputCharSpy_Create(int s)
{
    size = s;
    count = 0;
    spy_enable = 0;
    buffer = malloc(size);
    memset(buffer, 0, size);
}

void UnityOutputCharSpy_Destroy()
{
    size = 0;
    free(buffer);
}

int UnityOutputCharSpy_OutputChar(int c)
{
    if (spy_enable)
    {
        if (count < (size-1))
            buffer[count++] = c;
    }
    else
    {
        putchar(c);
    }
    return c;
}

const char * UnityOutputCharSpy_Get()
{
    return buffer;
}

void UnityOutputCharSpy_Enable(int enable)
{
    spy_enable = enable;
}
