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


#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include <string.h>
#include "RandomMinute.h"
}

enum { BOUND=30 };

TEST_GROUP(RandomMinute)
{

    void setup()
    {
        RandomMinute_Create(BOUND);
        srand(1);
    }

    void teardown()
    {
    }
}
;

TEST(RandomMinute, GetIsInRange)
{
    int minute;

    for (int i = 0; i < 100; i++)
    {
        minute = RandomMinute_Get();
        if (minute < -BOUND || minute > BOUND)
        {
            printf("bad minute value: %d\n", minute);
            FAIL("Minute out of range");
        }
    }
}

TEST(RandomMinute, AllValuesPossible)
{
    int minute;
    int hit[2*BOUND + 1];
    memset(hit, 0, sizeof(hit));

    for (int i = 0; i < 300; i++)
    {
        minute = RandomMinute_Get();
        if (minute < -BOUND || minute > BOUND)
        {
            printf("bad minute value: %d\n", minute);
            FAIL("Minute out of range");
        }
        hit[minute + BOUND]++;
    }

    //using j for vc6 compatibility
    for (int j = 0; j < 2*(BOUND) + 1; j++) {
        CHECK(hit[j] > 0);
    }
}
