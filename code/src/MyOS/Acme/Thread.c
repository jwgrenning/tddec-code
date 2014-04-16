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
#include "MyOsPrivate.h"
#include "src/MyOS/Acme/AcmeOs.h"

typedef struct ThreadStruct
{
    AcmeThreadStruct acmeThread;
} ThreadStruct;

Thread Thread_Create(ThreadEntryFunction entry, void * parameter)
{
     Thread self = calloc(1, sizeof(ThreadStruct));
     AcmeThread_create(&self->acmeThread, entry, parameter, 5, 1000);
     return self;
}

void Thread_Destroy(Thread self)
{
    AcmeThread_waitEnd(&self->acmeThread);
    free(self);
}

void Thread_Start(Thread self)
{
    AcmeThread_start(&self->acmeThread);
}

void Thread_Exit(void * result)
{
    result = result;
    AcmeThread_exit(0);
}

void * Thread_Join(Thread self)
{
    AcmeThread_waitEnd(&self->acmeThread);
    return NULL;
}
