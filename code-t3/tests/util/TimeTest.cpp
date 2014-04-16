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
#include <memory.h>
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"
//START: Time
TEST_GROUP(Time)
{
    Time time;
     void setup()
    {
      TimeService_Create();
    }

    void givenThatItIs(Day day)
    {
        FakeTimeService_SetDay(day);
    }

    void CheckThatTimeMatches(Day day)
    {
        TimeService_GetTime(&time);
        CHECK(Time_MatchesDayOfWeek(&time, day));
    }

    void CheckThatTimeDoesNotMatch(Day day)
    {
        TimeService_GetTime(&time);
        CHECK(!Time_MatchesDayOfWeek(&time, day));
    }
};

TEST(Time, ExactMatch)
{
    givenThatItIs(MONDAY);
    CheckThatTimeMatches(MONDAY);
    givenThatItIs(TUESDAY);
    CheckThatTimeMatches(TUESDAY);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeMatches(WEDNESDAY);
    givenThatItIs(THURSDAY);
    CheckThatTimeMatches(THURSDAY);
    givenThatItIs(FRIDAY);
    CheckThatTimeMatches(FRIDAY);
    givenThatItIs(SATURDAY);
    CheckThatTimeMatches(SATURDAY);
    givenThatItIs(SUNDAY);
    CheckThatTimeMatches(SUNDAY);
}

TEST(Time, WeekendDays)
{
    givenThatItIs(SATURDAY);
    CheckThatTimeMatches(WEEKEND);
    givenThatItIs(SUNDAY);
    CheckThatTimeMatches(WEEKEND);
    givenThatItIs(MONDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(TUESDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(THURSDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(FRIDAY);
}

TEST(Time, WeekDays)
{
    givenThatItIs(SATURDAY);
    CheckThatTimeDoesNotMatch(WEEKDAY);
    givenThatItIs(SUNDAY);
    CheckThatTimeDoesNotMatch(WEEKDAY);
    givenThatItIs(MONDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(TUESDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(THURSDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(FRIDAY);
}

TEST(Time, Everyday)
{
    givenThatItIs(SATURDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(SUNDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(MONDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(TUESDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(THURSDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(FRIDAY);
}
//END: Time

