//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------

extern "C"
{
#include "Thread.h"
#include "common.h"
}

#include "CppUTest/TestHarness.h"

//START: entry2
static int threadRan = FALSE;
static int threadResult = 42;
static void * threadEntry(void * p)
{
    threadRan = TRUE;
    return &threadResult;
}
//END: entry2

#if 0 //START: entry1
static int threadRan = FALSE;
static void * threadEntry(void * p)
{
    threadRan = TRUE;
    return 0;
}
#endif //END: entry1

//START: fixture1
TEST_GROUP(Thread)
{
    Thread thread;

    void setup()
    {
        threadRan = FALSE;
    }

    void teardown()
    {
    }
};
//END: fixture1

// START: CreateDoesNotStartThread
TEST(Thread, CreateDoesNotStartThread)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Destroy(thread);
    CHECK(FALSE == threadRan);
}
//END: CreateDoesNotStartThread

//START: ThreadStartsAfterStart
TEST(Thread, StartedThreadRunsBeforeItIsDestroyed)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Destroy(thread);
    CHECK(TRUE == threadRan);
}
//END: ThreadStartsAfterStart

TEST(Thread, Join)
{
	void * result;
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Join(thread, &result);
    Thread_Destroy(thread);
    LONGS_EQUAL(42, *((int *)result));
}
