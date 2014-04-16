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


#include "string.h"
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "RandomMinute.h"
#include <stdio.h>
}

//START: TestGroup
enum { BOUND=30 };

TEST_GROUP(RandomMinute)
{
    int minute;
    void setup()
    {
        RandomMinute_Create(BOUND);
        srand(1);
    }
    void AssertMinuteIsInRange()
    {
        if (minute < -BOUND || minute > BOUND)
         {
             printf("bad minute value: %d\n", minute);
             FAIL("Minute out of range");
         }
    }
};
//END: TestGroup

//START: InRange
TEST(RandomMinute, GetIsInRange)
{
    for (int i = 0; i < 100; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
    }
}
//END: InRange

//START: AllValues
TEST(RandomMinute, AllValuesPossible)
{
    int hit[2*BOUND + 1];
    memset(hit, 0, sizeof(hit));
	int i;
    for (i = 0; i < 300; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
        hit[minute + BOUND]++;
    }
    for (i = 0; i < 2* BOUND + 1; i++) {
        CHECK(hit[i] > 0);
    }
}
//END: AllValues
