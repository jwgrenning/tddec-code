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
#include "DvRecorder.h"
#include <memory.h>
}

//START: firstSetup
static DvRecorder recorderData = {
    4,
    {
        {"Rocky and Bullwinkle", REPEAT, 2, 8, 30, 30, HIGH_PRIORITY, ALL_EPISODES},
        {"Bugs Bunny", REPEAT, 9, 8, 30, 30, HIGH_PRIORITY, ALL_EPISODES},
        {"Dr. Who", REPEAT, 11, 23, 0, 90, HIGH_PRIORITY, REPEATED_EPISODES},
        {"Law and Order", REPEAT, 5, 21, 0, 60, HIGH_PRIORITY, ALL_EPISODES},
        { 0 }
    }
};
//END: firstSetup

#if 0 //START: firstSetup
TEST_GROUP(DvRecorder)
{
    DvRecorder recorder;
    void setup()
    {
        memcpy(&recorder, &recorderData, sizeof(recorder));
        DvrRecorder_Create();
        DvRecorder_RestorePrograms(&recorder);
    }
    
    void teardown()
    {
       DvRecorder_Destroy();
    }
};
//END: firstSetup
#endif

//START: twoStageSetup
TEST_GROUP(DvRecorder)
{
    DvRecorder recorder;
    void setup()
    {
        memcpy(&recorder, &recorderData, sizeof(recorder));
        DvrRecorder_Create();
    }
    void teardown()
    {
       DvRecorder_Destroy();
    }
};
TEST(DvRecorder, RestoreSomePrograms)
{
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}
//END: twoStageSetup


//START: overridesDefaultData
TEST(DvRecorder, RestoreNoPrograms)
{
    recorder.programCount = 0;
    recorder.programs[0].name = 0;
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}
TEST(DvRecorder, RecordWithRepeat)
{
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

TEST(DvRecorder, RecordWithNoRepeat)
{
    recorder.programs[0].repeat = NO_REPEAT;
    recorder.programs[1].repeat = NO_REPEAT;
    recorder.programs[2].repeat = NO_REPEAT;
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}
TEST(DvRecorder, RecordConflictFirstHighPriorityWins)
{
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}
TEST(DvRecorder, RecordConflictHighPriorityWins)
{
    recorder.programs[0].priority = LOW_PRIORITY;
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

//END: overridesDefaultData


