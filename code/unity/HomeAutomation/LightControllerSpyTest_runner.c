/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/* Generated code, edit at your own risk */

#include "unity_fixture.h"

/* Make sure you invoke RUN_TEST_GROUP(LightControllerSpy) from unity main */

TEST_GROUP_RUNNER(LightControllerSpy)
{
    RUN_TEST_CASE(LightControllerSpy, Create);
    RUN_TEST_CASE(LightControllerSpy, RememberTheLastLightIdControlled);
    RUN_TEST_CASE(LightControllerSpy, RememberAllLightStates);
}
