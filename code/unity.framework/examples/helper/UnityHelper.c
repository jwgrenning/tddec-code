/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#include "unity.h"
#include "UnityHelper.h"
#include <stdio.h>
#include <string.h>

void AssertEqualExampleStruct(const EXAMPLE_STRUCT_T expected, const EXAMPLE_STRUCT_T actual, const unsigned short line)
{
    UNITY_TEST_ASSERT_EQUAL_INT(expected.x, actual.x, line, "Example Struct Failed For Field x");
    UNITY_TEST_ASSERT_EQUAL_INT(expected.y, actual.y, line, "Example Struct Failed For Field y");
}
