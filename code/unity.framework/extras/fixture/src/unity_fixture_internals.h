/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
//- Copyright (c) 2010 James Grenning and Contributed to Unity Project
/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef UNITY_FIXTURE_INTERNALS_H_
#define UNITY_FIXTURE_INTERNALS_H_

typedef struct _UNITY_FIXTURE_T
{
    int Verbose;
    unsigned int RepeatCount;
    const char* NameFilter;
    const char* GroupFilter;
} UNITY_FIXTURE_T;

typedef void unityfunction();
void UnityTestRunner(unityfunction * setup,
        unityfunction * body,
        unityfunction * teardown,
        const char * printableName,
        const char * group,
        const char * name,
        const char * file, int line);

void UnityIgnoreTest(const char *);
void UnityMalloc_StartTest();
void UnityMalloc_EndTest();
int UnityFailureCount();
int UnityGetCommandLineOptions(int argc, char* argv[]);
void UnityConcludeFixtureTest();

void UnityPointer_Set(void ** ptr, void * newValue);
void UnityPointer_UndoAllSets();
void UnityPointer_Init();

void UnityAssertEqualPointer(const void * expected,
                            const void * actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber);

#endif /* UNITY_FIXTURE_INTERNALS_H_ */
