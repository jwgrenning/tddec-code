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
#define NONSENSE_POINTER (void *)~0
void * threadParameter = NONSENSE_POINTER;
static int threadRan = FALSE;
#define THREAD_RETURN_CODE 999
static int returnCode = THREAD_RETURN_CODE;
static void * threadEntry(void * p)
{
    threadRan = TRUE;
    threadParameter = p;
    Thread_Exit(&returnCode);
    return 0;
}
//END: entry2

//START: fixture2
TEST_GROUP(Thread)
{
    Thread thread;

    void setup()
    {
        MyOs_Init(10);
        threadRan = FALSE;
        threadParameter = NONSENSE_POINTER;
    }

    void teardown()
    {
        MyOs_ShutDown();
    }
};
//END: fixture2

// START: CreateDoesNotStartThread
TEST(Thread, CreateDoesNotStartThread)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Destroy(thread);
    CHECK_EQUAL(FALSE, threadRan);
}
//END: CreateDoesNotStartThread

//START: ThreadStartsAfterStart
TEST(Thread, StartedThreadRunsBeforeItIsDestroyed)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Destroy(thread);
    CHECK_EQUAL(TRUE, threadRan);
}
//END: ThreadStartsAfterStart

//START: ThreadGetsParameter
TEST(Thread, ThreadGetsParameter)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Destroy(thread);
    POINTERS_EQUAL(0, threadParameter);

}
//END: ThreadGetsParameter

//START: joinReturnCode
TEST(Thread, joinReturnCode1)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    int i = 10;
    int * result = &i;
    Thread_Join(thread, (void **)&result);
    LONGS_EQUAL(THREAD_RETURN_CODE, *result);
    Thread_Destroy(thread);
    CHECK_EQUAL(TRUE, threadRan);
}
//END: joinReturnCode

//START: joinReturnCode
TEST(Thread, joinReturnCode)
{
    thread = Thread_Create(threadEntry, 0);
    Thread_Start(thread);
    Thread_Join(thread, NULL);
    int * result = (int *)Thread_Result(thread);
    CHECK(result != 0);
    LONGS_EQUAL(THREAD_RETURN_CODE, *result);
    Thread_Destroy(thread);
    CHECK_EQUAL(TRUE, threadRan);
}
//END: joinReturnCode

