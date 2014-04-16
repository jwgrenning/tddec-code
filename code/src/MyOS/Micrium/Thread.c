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
#include  <os.h>

OS_MEM AppMemTask;

typedef struct ThreadStruct
{
    ThreadEntryFunction entry;
    void * parameter;
    BOOL started;
    OS_TCB TCB;
    OS_SEM Sem;
    CPU_STK Stk[APP_TASK_SIMPLE_STK_SIZE];
} ThreadStruct;



Thread Thread_Create (ThreadEntryFunction entry, void *parameter)
{
    OS_ERR err;

    Thread self = OSMemGet(&AppMemTask, &err);
    self->entry = entry;
    self->parameter = parameter;
    self->started = FALSE;
    OSSemCreate (&(self->Sem), "Test Sem", 0, &err);
    return self;
}

void  Thread_Destroy (Thread self)
{
    OS_ERR err;
    OSSemPend(&(self->Sem), 0, OS_OPT_PEND_BLOCKING, 0, &err);
    OSTaskDel(&(self->TCB), &err);
    OSSemDel(&(self->Sem));
    OSMemPut (&AppMemTask, self, &err);
}

static void MicriumTaskShell(void *p_arg)
{
    Thread thread;
    OS_ERR err;

    thread = (Thread) p_arg;
    thread->entry(thread->parameter);
    OSSemPost(&(thread->Sem), OS_OPT_POST_ALL, &err);
    while (DEF_ON)
    {
        OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}

void Thread_Start(Thread self)
{
    OS_ERR err;

    self->started = TRUE;

    OSTaskCreate(&(self->TCB), "App Task",
                 MicriumTaskShell, (void *)self,
                 APP_TASK_SIMPLE_PRIO,
                 self->Stk, APP_TASK_SIMPLE_STK_SIZE / 10,
                 APP_TASK_SIMPLE_STK_SIZE,
                 0,
                 0,
                 0,
                 (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 &err);
}
