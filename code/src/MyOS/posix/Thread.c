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
#include "common.h"
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>

/*
 * Book readers... I discovered that a started flag is needed on
 * some pthread systems.  This is not discussed in the book
 */

typedef struct ThreadStruct
{
    ThreadEntryFunction entry;
    void * parameter;
    pthread_t pthread;
    BOOL started;

} ThreadStruct;

Thread Thread_Create(ThreadEntryFunction f, void * parameter)
{
     Thread self = calloc(1, sizeof(ThreadStruct));
     self->entry = f;
     self->parameter = parameter;
     self->started = FALSE;;
     return self;
}

void Thread_Destroy(Thread self)
{
    if (self->started)
        pthread_join(self->pthread, NULL);
    free(self);
}

void Thread_Start(Thread self)
{
    self->started = TRUE;
    pthread_create(&self->pthread, NULL, self->entry, self->parameter);
}

void Thread_Join(Thread other, void ** result)
{
    if (other->started)
        pthread_join(other->pthread, result);
    other->started = FALSE;
}

#if 0
typedef struct ThreadStruct
{
    ThreadEntryFunction entry;
    void * parameter;
    pthread_t pthread;
} ThreadStruct;

Thread Thread_Create(ThreadEntryFunction f, void * parameter)
{
     Thread self = calloc(1, sizeof(ThreadStruct));
     self->entry = f;
     self->parameter = parameter;
     return self;
}

void Thread_Destroy(Thread self)
{
    pthread_join(self->pthread, NULL);
    free(self);
}

void Thread_Start(Thread self)
{
    pthread_create(&self->pthread, NULL, self->entry, self->parameter);
}

void Thread_Join(Thread other, void ** result)
{
    pthread_join(other->pthread, result);
}
#endif
