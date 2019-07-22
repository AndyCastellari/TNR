/*
 * TNR_tester.cpp
 *
 *      Author: Andy Castellari
 *
 *      COPYRIGHT AND PERMISSION NOTICE
 *
 * Copyright (c) 2015 - 2016, Andy Castellari.
 *
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written authorization of the copyright holder.
 *
 */

#include <iostream>
#include "StreamReadWriteIf.h"
#include <stdio.h>
using namespace std;

#include "tnr.h"
#include "PODTester.h"
#include "JSONTester.h"
#include <rapidjson/rapidjson.h>
#include <gtest/gtest.h>

#include "TextLogWriteIf.h"
#include "SimpleTextReadWriteIf.h"

#include "EnumerationStore.h"

TEST(TNRTestCase, testPODType)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testPODType());
}

TEST(TNRTestCase, testFixedArray)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testFixedArray());
}

TEST(TNRTestCase, testCountedArray)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testCountedArray());
}

TEST(TNRTestCase, testMemoryStreamIf)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testMemoryStreamIf());
}
TEST(TNRTestCase, testTNRContainer)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testTNRContainer());
}
TEST(TNRTestCase, testTNRNestedContainer)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testTNRNestedContainer());
}
TEST(TNRTestCase, testTextLogWriteIf)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testTextLogWriteIf());
}
TEST(TNRTestCase, testSimpleTextWriteIf)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testSimpleTextWriteIf());
}
TEST(TNRTestCase, testTNR_C_String)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testTNR_C_String());
}
TEST(TNRTestCase, testObjectMap)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testObjectMap());
}

TEST(TNRTestCase, JSONTesterTestParsing)
{
    JSONTester jt;
    ASSERT_TRUE(jt.testParsing());
}


TEST(TNRTestCase, testJSON_to_Container)
{
    JSONTester jt;
    ASSERT_TRUE(jt.testJSON_to_Container());
}

TEST(TNRTestCase, testTNR_Variant)
{
    POD_Tester pt;
    ASSERT_TRUE(pt.testVariant());
}

// Special value for test to prevent updating the enum value
const uint32_t DontChangeEnumValue = 0xffff;

// Load enumStore with value from test vector, names and optionally values
void LoadEnumerationStore(const std::vector<std::pair<std::string, uint32_t>> &testVector, EnumerationStore_ptr &enumStore)
{
    for (auto element: testVector)
    {
        enumStore->AddEnumValue(element.first);
        if (element.second != DontChangeEnumValue)
        {
            enumStore->SetEnumValue(element.second);
        }
    }
}

// Check enumStore with value from test vector, names and optionally values
void CheckEnumerationStore(const std::vector<std::pair<std::string, uint32_t>> &testVector, EnumerationStore_ptr &enumStore)
{
    uint32_t expectedValue = 0;
    std::string actual;

    for (auto element: testVector)
    {
        // Calculate what the next actual should be
        // either the enum actual was set or it just increments
        if (element.second != DontChangeEnumValue)
        {
            expectedValue = element.second;
            actual = enumStore->GetEnumName(expectedValue);
        }
        else
        {
            actual = enumStore->GetEnumName(expectedValue);
        }
        expectedValue++;

        EXPECT_EQ(element.first, actual);
    }
}

void ProcessEnumTestVector(const std::vector<std::pair<std::string, uint32_t>> &testVector)
{
    EnumerationStore_ptr enumStore = std::make_shared<EnumerationStore>();

    LoadEnumerationStore(testVector, enumStore);
//    enumStore->PrintEnumStore();
    CheckEnumerationStore(testVector, enumStore);
}

TEST(TNRTestCase, testBasicIncrementingFromZeroEnumeration)
{
    std::vector<std::pair<std::string, uint32_t>> testVector =
            {
                    {"Red", DontChangeEnumValue},
                    {"Green", DontChangeEnumValue},
                    {"Blue", DontChangeEnumValue},
                    {"Yellow", DontChangeEnumValue},
                    {"Purple", DontChangeEnumValue},
            };

    ProcessEnumTestVector(testVector);
}

TEST(TNRTestCase, testIncrementingFromThenChangingEnumeration)
{
    std::vector<std::pair<std::string, uint32_t>> testVector =
            {
                    {"Red", DontChangeEnumValue},
                    {"Green", DontChangeEnumValue},
                    {"Blue", DontChangeEnumValue},
                    {"Yellow", 10},
                    {"Purple", DontChangeEnumValue},
            };

    ProcessEnumTestVector(testVector);
}

TEST(TNRTestCase, testChangingFirstValueThenIncrementingEnumeration)
{
    std::vector<std::pair<std::string, uint32_t>> testVector =
            {
                    {"Red", 12},
                    {"Green", DontChangeEnumValue},
                    {"Blue", DontChangeEnumValue},
                    {"Yellow", DontChangeEnumValue},
                    {"Purple", DontChangeEnumValue},
            };
    ProcessEnumTestVector(testVector);
}


TEST(TNRTestCase, testChangingFirstValueThenIncrementingThenChangingAgainEnumeration)
{
    std::vector<std::pair<std::string, uint32_t>> testVector =
            {
                    {"Red", 12},
                    {"Green", DontChangeEnumValue},
                    {"Blue", DontChangeEnumValue},
                    {"Yellow", 7},
                    {"Purple", DontChangeEnumValue},
            };
    ProcessEnumTestVector(testVector);
}


#if 0
int main() {
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    POD_Tester pt;
    JSONTester jt;
    bool b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12;
    bool allTests;

    printf("Test testPODType %s\n", (b1 = pt.testPODType()) ? "PASSED" : "FAILED");
    printf("Test testFixedArray %s\n", (b2 = pt.testFixedArray()) ? "PASSED" : "FAILED");
    printf("Test testCountedArray %s\n", (b3 = pt.testCountedArray()) ? "PASSED" : "FAILED");
    printf("Test testMemoryStreamIf %s\n", (b4 = pt.testMemoryStreamIf()) ? "PASSED" : "FAILED");
    printf("Test testTNRContainer %s\n", (b5 = pt.testTNRContainer()) ? "PASSED" : "FAILED");
    printf("Test testTNRNestedContainer %s\n", (b6 = pt.testTNRNestedContainer()) ? "PASSED" : "FAILED");
    printf("Test testTextLogWriteIf %s\n", (b7 = pt.testTextLogWriteIf()) ? "PASSED" : "FAILED");
    printf("Test testSimpleTextWriteIf %s\n", (b8 = pt.testSimpleTextWriteIf()) ? "PASSED" : "FAILED");

    printf("Test testTNR_C_String %s\n", (b9 = pt.testTNR_C_String()) ? "PASSED" : "FAILED");

    printf("Test testObjectMap %s\n", (b10 = pt.testObjectMap()) ? "PASSED" : "FAILED");

    printf("Test JSONTester::testParsing %s\n", (b11 = jt.testParsing()) ? "PASSED" : "FAILED");
    printf("Test JSONTester::testJSON_to_Container %s\n", (b12 = jt.testJSON_to_Container()) ? "PASSED" : "FAILED");

    allTests = (b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8 && b9 && b10 && b11 && b12);

    printf("\nOverall Test %s\n\n", allTests ? "PASSED" : "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<FAILED>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");


    return 0;
}
#endif
