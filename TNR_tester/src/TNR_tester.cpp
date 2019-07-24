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
template<class T>
void LoadEnumerationStore(const std::vector<std::pair<std::string, uint32_t>> &testVector, std::shared_ptr<T> &enumStore)
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
template<class T>
void CheckEnumerationStore(const std::vector<std::pair<std::string, uint32_t>> &testVector, std::shared_ptr<T> &enumStore)
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

template <class T>
void ProcessEnumTestVector(const std::vector<std::pair<std::string, uint32_t>> &testVector)
{
    std:shared_ptr<T> enumClass = std::make_shared<T>();

    LoadEnumerationStore(testVector, enumClass);
    CheckEnumerationStore(testVector, enumClass);
}

void ProcessTestVectorOnAllTypes(const std::vector<std::pair<std::string, uint32_t>> &testVector)
{
    ProcessEnumTestVector<EnumerationStore>(testVector);
    ProcessEnumTestVector<tnr::POD_U8>(testVector);
    ProcessEnumTestVector<tnr::POD_U16>(testVector);
    ProcessEnumTestVector<tnr::POD_U24>(testVector);
    ProcessEnumTestVector<tnr::POD_U32>(testVector);
    ProcessEnumTestVector<tnr::POD_S8>(testVector);
    ProcessEnumTestVector<tnr::POD_S16>(testVector);
    ProcessEnumTestVector<tnr::POD_S24>(testVector);
    ProcessEnumTestVector<tnr::POD_S32>(testVector);
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

    ProcessTestVectorOnAllTypes(testVector);
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

    ProcessTestVectorOnAllTypes(testVector);
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
    ProcessTestVectorOnAllTypes(testVector);
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
    ProcessTestVectorOnAllTypes(testVector);
}

const uint32_t MAX_ENUM_TEST_COUNT = 50000;

template<class T>
void testEnumStringsAreAllEmptyWithNoEnumsDefined()
{
    std::shared_ptr<T> enumStore = std::make_shared<T>();
    std::string enumName;

    // Check that nothing is returned while the store is empty
    for (uint32_t counter = 0; counter < MAX_ENUM_TEST_COUNT; counter++)
    {
        enumName = enumStore->GetEnumName(counter);
        ASSERT_TRUE(enumName.empty());
    }
}

TEST(TNRTestCase, testEnumStringsAreAllEmptyWithNoEnumsDefined)
{
    testEnumStringsAreAllEmptyWithNoEnumsDefined<EnumerationStore>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_U8>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_U16>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_U24>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_U32>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_S8>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_S16>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_S24>();
    testEnumStringsAreAllEmptyWithNoEnumsDefined<tnr::POD_S32>();
}

template <class T>
void CheckEnumerationValuesAreAllEmptyApartFromThoseDefined()
{
    // Define enums for values 4 to 8
    std::vector<std::pair<std::string, uint32_t>> testVector =
            {
                    {"Red", 5},
                    {"Green", 7},
                    {"Blue", 4},
                    {"Yellow", 6},
                    {"Purple", 8},
            };

    std::shared_ptr<T> enumStore = std::make_shared<T>();
    std::string enumName;

    LoadEnumerationStore(testVector, enumStore);

    // Check that nothing is returned apart from 4-8 which have enum values
    for (uint32_t counter = 0; counter < MAX_ENUM_TEST_COUNT; counter++)
    {
        enumName = enumStore->GetEnumName(counter);
        if ((counter >= 4) && (counter <= 8))
        {
            ASSERT_FALSE(enumName.empty());
        }
        else
        {
            ASSERT_TRUE(enumName.empty());
        }
    }
}

TEST(TNRTestCase, testNonEnumValuesAreEmptyWithSomeEnumsDefined)
{
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<EnumerationStore>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_U8>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_U16>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_U24>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_U32>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_S8>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_S16>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_S24>();
    CheckEnumerationValuesAreAllEmptyApartFromThoseDefined<tnr::POD_S32>();
}

