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

#include "unity_fixture.h"


#if 0 
static void RunAllTests(void)
{
    RUN_TEST_GROUP(LedDriver);
}
#endif 

#if 0 
static void RunAllTests(void)
{
    RUN_TEST_GROUP(sprintf);
}
#endif 

static void RunAllTests(void)
{
    /*    RUN_TEST_GROUP(unity); */
    RUN_TEST_GROUP(LedDriver);
    RUN_TEST_GROUP(sprintf);
    RUN_TEST_GROUP(UnityFixture);
    RUN_TEST_GROUP(UnityCommandOptions);
    RUN_TEST_GROUP(LeakDetection);
    RUN_TEST_GROUP(FakeTimeService);
    RUN_TEST_GROUP(LightControllerSpy);
    RUN_TEST_GROUP(LightScheduler);
    RUN_TEST_GROUP(LightSchedulerInitAndCleanup);
}


int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
