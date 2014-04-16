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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "MockIO.h"
#include "CppUTest/TestHarness_c.h"

#if WIN32
#define snprintf _snprintf
#endif



enum
{
    FLASH_READ, FLASH_WRITE, NoExpectedValue = -1
};

typedef struct Expectation
{
    int kind;
    ioAddress addr;
    ioData value;
} Expectation;

static Expectation * expectations = 0;
static int setExpectationCount;
static int getExpectationCount;
static int maxExpectationCount;
static int failureAlreadyReported = 0;

static Expectation expected;
static Expectation actual;

static char * report_expect_write_was_read =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "\t        But was IO_Read(0x%x)";
static char * report_read_wrong_address =
    "Expected IO_Read(0x%x) returns 0x%x;\n"
    "\t        But was IO_Read(0x%x)";
static char * report_expect_read_was_write =
    "Expected IO_Read(0x%x) would return 0x%x)\n"
    "\t        But was IO_Write(0x%x, 0x%x)";
static char * report_write_does_not_match =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "\t        But was IO_Write(0x%x, 0x%x)";
static char * report_too_many_write_expectations =
    "MockIO_Expect_IO_Write: Too many expectations";
static char * report_too_many_read_expectations =
    "MockIO_Expect_IO_Read: Too many expectations";
static char * report_MockIO_not_initialized =
    "MockIO not initialized, call MockIO_Create()";
static char * report_write_but_out_of_expectations =
    "IO_Write(0x%x, 0x%x)";
static char * report_read_but_out_of_expectations =
    "IO_Read(0x%x)";
static const char * report_no_more_expectations =
    "R/W %d: No more expectations but was ";
static const char * report_expectation_number =
    "R/W %d: ";

void MockIO_Create(int maxExpectations)
{
    expectations = calloc(maxExpectations, sizeof(Expectation));
    setExpectationCount = 0;
    getExpectationCount = 0;
    maxExpectationCount = maxExpectations;
    failureAlreadyReported = 0;
}

void MockIO_Destroy(void)
{
    if (expectations)
        free(expectations);
    expectations = 0;
}

static void fail(char * message)
{
    failureAlreadyReported = 1;
    FAIL_TEXT_C(message);
}

static void failWhenNotInitialized(void)
{
    if (expectations == 0)
        fail(report_MockIO_not_initialized);
}

static void failWhenNoRoomForExpectations(char * message)
{
    failWhenNotInitialized();
    if (setExpectationCount >= maxExpectationCount)
        fail(message);
}

void recordExpectation(int kind, ioAddress addr, ioData data)
{
    expectations[setExpectationCount].kind = kind;
    expectations[setExpectationCount].addr = addr;
    expectations[setExpectationCount].value = data;
    setExpectationCount++;
}

void MockIO_Expect_Write(ioAddress addr, ioData value)
{
    failWhenNoRoomForExpectations(report_too_many_write_expectations);
    recordExpectation(FLASH_WRITE, addr, value);
}

void MockIO_Expect_ReadThenReturn(ioAddress addr, ioData value)
{
    failWhenNoRoomForExpectations(report_too_many_read_expectations);
    recordExpectation(FLASH_READ, addr, value);
}

static void failWhenNoUnusedExpectations(char * format)
{
    char message[100];
    int size = sizeof message - 1;

    if (getExpectationCount >= setExpectationCount)
    {
        int offset = snprintf(message, size,
                report_no_more_expectations, getExpectationCount + 1);
        snprintf(message + offset, size - offset,
                format, actual.addr, actual.value);
        fail(message);
    }
}

static void setExpectedAndActual(ioAddress addr, ioData value)
{
    expected.addr = expectations[getExpectationCount].addr;
    expected.value = expectations[getExpectationCount].value;
    actual.addr = addr;
    actual.value = value;
}

static void failExpectation(char * expectationFailMessage)
{
    char message[100];
    int size = sizeof message - 1;
    int offset = snprintf(message, size,
            report_expectation_number, getExpectationCount + 1);
    snprintf(message + offset, size - offset,
            expectationFailMessage, expected.addr, expected.value,
            actual.addr, actual.value);
    fail(message);
}

static void failWhen(int condition, char * expectationFailMessage)
{
    if (condition)
        failExpectation(expectationFailMessage);
}

static int expectationIsNot(int kind)
{
    return kind != expectations[getExpectationCount].kind;
}

static int expectedAddressIsNot(ioAddress addr)
{
    return expected.addr != addr;
}

static int expectedDataIsNot(ioData data)
{
    return expected.value != data;
}

void IO_Write(ioAddress addr, ioData value)
{
    setExpectedAndActual(addr, value);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_write_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_WRITE), report_expect_read_was_write);
    failWhen(expectedAddressIsNot(addr), report_write_does_not_match);
    failWhen(expectedDataIsNot(value), report_write_does_not_match);
    getExpectationCount++;
}

ioData IO_Read(ioAddress addr)
{
    setExpectedAndActual(addr, NoExpectedValue);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_read_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_READ), report_expect_write_was_read);
    failWhen(expectedAddressIsNot(addr), report_read_wrong_address);

    return expectations[getExpectationCount++].value;
}

static void failWhenNotAllExpectationsUsed(void)
{
    char format[] = "Expected %d reads/writes but got %d";
    char message[sizeof format + 5 + 5];

    if (getExpectationCount == setExpectationCount)
        return;

    snprintf(message, sizeof message, format, setExpectationCount,
            getExpectationCount);
    fail(message);
}


void MockIO_Verify_Complete(void)
{
    if (failureAlreadyReported)
        return;
    failWhenNotAllExpectationsUsed();
}
