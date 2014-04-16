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

/*
 * There is no Acme
 * so pretend with these test stubs are really the acme header and implementation
 *
 * If you want to run this code instead of the POSIX version, change
 * MakefileUnity.mk SRC_DIRS to build src/MyOS/Acme instead of src/MyOS/posix.
 *
 */
#include "src/MyOS/Acme/AcmeOs.h"

/* fake implementation to get the tests to pass */
AcmeThread theThread = 0;
int AcmeThread_waitEnd(AcmeThread thread) { return 0; }
void AcmeThread_start(AcmeThread thread) { thread->entry(thread->parameter); }
void AcmeThread_nanoSleep(unsigned long ns) { ns = ns; }
void AcmeThread_exit(int result) { result = result; }
AcmeThread AcmeThread_currentThread(void) { return theThread; }
/* End of Acme stubs */

void AcmeThread_create(AcmeThread thread, AcmeThreadEntryFunction f, void * p, int priority, int stacksize)
{
    thread->priority = priority;
    thread->stacksize = stacksize;
    thread->entry = f;
    thread->parameter = p;
    theThread = thread;
}
/*
 * end of acme
 */
