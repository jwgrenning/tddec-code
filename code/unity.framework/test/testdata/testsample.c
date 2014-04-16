/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
// This is just a sample test file to be used to test the generator script
#ifndef TEST_SAMPLE_H
#define TEST_SAMPLE_H

#include <setjmp.h>
#include "unity.h"
#include "funky.h"
#include "stanky.h"

void setUp(void)
{
  CustomSetupStuff();
}

void tearDown(void)
{
  CustomTeardownStuff
}

//Yup, nice comment
void test_TheFirstThingToTest(void)
{
    TEST_ASSERT(1);

    TEST_ASSERT_TRUE(1);
}

/*
void test_ShouldBeIgnored(void)
{
    DoesStuff();
}
*/

//void test_ShouldAlsoNotBeTested(void)
//{
//    Call_An_Expect();
//    
//    CallAFunction();
//    test_CallAFunctionThatLooksLikeATest();
//}

void test_TheSecondThingToTest(void)
{
    Call_An_Expect();
    
    CallAFunction();
    test_CallAFunctionThatLooksLikeATest();
}

#endif //TEST_SAMPLE_H
