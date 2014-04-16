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

#include "unity_fixture.h"

static int data = -1;

TEST_GROUP(mygroup);

TEST_SETUP(mygroup)
{
    data = 0;
}

TEST_TEAR_DOWN(mygroup)
{
    data = -1;
}

TEST(mygroup, test1)
{
    TEST_ASSERT_EQUAL_INT(0, data);
}

TEST(mygroup, test2)
{
    TEST_ASSERT_EQUAL_INT(0, data);
    data = 5;
}

TEST(mygroup, test3)
{
    data = 7;
    TEST_ASSERT_EQUAL_INT(7, data);
}
