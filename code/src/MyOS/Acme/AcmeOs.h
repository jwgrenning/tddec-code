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

#ifndef D_AcmeOs_H
#define D_AcmeOs_H
/*
 * There is no Acme
 * so pretend with these test stubs are really the acme header and implementation
 *
 * If you want to run this code instead of the POSIX version, change
 * MakefileUnity.mk SRC_DIRS to build src/MyOS/Acme instead of src/MyOS/posix.
 *
 */
typedef struct AcmeThreadStruct * AcmeThread;
typedef int (*AcmeThreadEntryFunction)(void *);

int AcmeThread_waitEnd(AcmeThread thread);
void AcmeThread_start(AcmeThread thread);
void AcmeThread_exit(int result);
AcmeThread AcmeThread_currentThread(void);
void AcmeThread_create(AcmeThread thread, AcmeThreadEntryFunction, void * p, int priority, int stacksize);

/* private */

typedef struct AcmeThreadStruct
{
    AcmeThreadEntryFunction entry;
    void * parameter;
    int priority;
    int stacksize;
} AcmeThreadStruct;



#endif  /* D_AcmeOs_H */
