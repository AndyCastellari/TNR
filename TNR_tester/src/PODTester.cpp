/*
 * PODTester.cpp
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

#include "tnr.h"
#include "PODTester.h"
#include "StreamReadWriteIf.h"
#include "TextLogWriteIf.h"
#include "SimpleTextReadWriteIf.h"
#include "ObjectMap.h"

#include <stdio.h>

using namespace std;
using namespace tnr;

//! Quick print a string of binary values out
void printString(const char * title, const std::string &s)
{
    printf("%s : ", title);
    for (char c: s)
    {
        printf("%02x", (U8)c);
    }
    printf("\n");
}

bool POD_Tester::testTextLogWriteIf()
{
    bool result = true;
    std::shared_ptr<std::stringstream> wstream1(new std::stringstream());
    TextLogWriteIf tlwif(wstream1);
    result = testTextWriteIf(tlwif);
    cout << wstream1->str() << endl;
    return result;
}

bool POD_Tester::testSimpleTextWriteIf()
{
    bool result = true;
    std::shared_ptr<std::stringstream> wstream2(new std::stringstream());
    SimpleTextWriteIf stwif(wstream2);
    result = testTextWriteIf(stwif);
    cout << wstream2->str() << endl;
    return result;
}


bool POD_Tester::testTextWriteIf(tnr::tnr_write_interface & wif)
{
    bool result = true;

    TNRContainer_ptr tnrcontainer1(new TNRContainer("Nested Container1"));
    TNRContainer_ptr tnrcontainer2(new TNRContainer("Nested Container2"));
    TNRContainer_ptr tnrcontainer3(new TNRContainer("Nested Container3"));
    TNRContainer_ptr tnrcontainer4(new TNRContainer("Nested Container4"));
    TNRContainer_ptr tnrcontainer5(new TNRContainer("Nested Container5"));

    // Create one of each type of variable
    POD_U8_ptr u8(new POD_U8(0x45, "U8"));
    POD_U16_ptr u16( new POD_U16 (0xA012, "U16"));
    POD_U24_ptr u24( new POD_U24 (0x132790, "U24"));
    POD_U32_ptr u32( new POD_U32 (0x87654321, "U32"));
    POD_S8_ptr s8( new POD_S8 (0xb0, "S8"));
    POD_S16_ptr s16( new POD_S16 (0x8765, "S16"));
    POD_S24_ptr s24a( new POD_S24 (-1, "S24"));
    POD_S24_ptr s24b( new POD_S24 (0xba9876, "S24"));
    POD_S24_ptr s24c( new POD_S24 (0x765432, "S24"));
    POD_S24_ptr s24d( new POD_S24 (-200000, "S24"));
    POD_S24_ptr s24e( new POD_S24 (200000, "S24"));        // 200000=0x030d40, 200256=0x030e40 no CR in bytes
    POD_S32_ptr s32a( new POD_S32 (0xffffffff, "S32"));
    POD_S32_ptr s32b( new POD_S32 (0x12345678, "S32"));
    POD_S32_ptr s32c( new POD_S32 (0xc2345678, "S32"));


    // Build the nested containers
    // 1 = 2 + 3
    // 3 = POD + 4
    // 4 = POD + 5
    // Add in the POD data and then nest the containers to produce the same output stream
    tnrcontainer1->Add(u8);
    tnrcontainer2->Add(u16);
    tnrcontainer2->Add(u24);
    tnrcontainer3->Add(u32);
    tnrcontainer3->Add(s8);
    tnrcontainer3->Add(s16);
    tnrcontainer3->Add(s24a);
    tnrcontainer3->Add(s24b);
    tnrcontainer4->Add(s24c);
    tnrcontainer4->Add(s24d);
    tnrcontainer5->Add(s24e);
    tnrcontainer5->Add(s32a);
    tnrcontainer5->Add(s32b);
    tnrcontainer5->Add(s32c);

    tnrcontainer4->Add(tnrcontainer5);
    tnrcontainer3->Add(tnrcontainer4);
    tnrcontainer1->Add(tnrcontainer2);
    tnrcontainer1->Add(tnrcontainer3);

    tnrcontainer1->write(wif);

    return result;
}

bool POD_Tester::testTNRNestedContainer()
{
    bool result = true;
    // Avoiding any 0x00 bytes as these will terminate the string
    const unsigned char testBytes[] = { 0x45, 0x12, 0xA0, 0x90, 0x27, 0x13, 0x21, 0x43, 0x65, 0x87,
            // Signed value testing
                0xb0,
                0x65, 0x87,
                0xff, 0xff, 0xff,
                0x76, 0x98, 0xba,
                0x32, 0x54, 0x76,
                0xc0, 0xf2, 0xfc,
                0x40, 0x0d, 0x03,                // CR
                0xff, 0xff, 0xff, 0xff,
                0x78, 0x56, 0x34, 0x12,
                0x78, 0x56, 0x34, 0xc2
    };

    std::string rhs((const char *)testBytes);

    std::shared_ptr<std::stringstream> _wstream(new std::stringstream());
    std::shared_ptr<std::stringstream> _rstream(new std::stringstream(rhs));

    StreamWriteIf mswif(_wstream);
    StreamReadIf msrif(_rstream);

    TNRContainer_ptr tnrcontainer1(new TNRContainer("Nested Container1"));
    TNRContainer_ptr tnrcontainer2(new TNRContainer("Nested Container2"));
    TNRContainer_ptr tnrcontainer3(new TNRContainer("Nested Container3"));
    TNRContainer_ptr tnrcontainer4(new TNRContainer("Nested Container4"));
    TNRContainer_ptr tnrcontainer5(new TNRContainer("Nested Container4"));

    // Create one of each type of variable
    POD_U8_ptr u8(new POD_U8(0x45, "U8"));
    POD_U16_ptr u16( new POD_U16 (0xA012, "U16"));
    POD_U24_ptr u24( new POD_U24 (0x132790, "U24"));
    POD_U32_ptr u32( new POD_U32 (0x87654321, "U32"));
    POD_S8_ptr s8( new POD_S8 (0xb0, "S8"));
    POD_S16_ptr s16( new POD_S16 (0x8765, "S16"));
    POD_S24_ptr s24a( new POD_S24 (-1, "S24"));
    POD_S24_ptr s24b( new POD_S24 (0xba9876, "S24"));
    POD_S24_ptr s24c( new POD_S24 (0x765432, "S24"));
    POD_S24_ptr s24d( new POD_S24 (-200000, "S24"));
    POD_S24_ptr s24e( new POD_S24 (200000, "S24"));        // 200000=0x030d40, 200256=0x030e40 no CR in bytes
    POD_S32_ptr s32a( new POD_S32 (0xffffffff, "S32"));
    POD_S32_ptr s32b( new POD_S32 (0x12345678, "S32"));
    POD_S32_ptr s32c( new POD_S32 (0xc2345678, "S32"));


    // Build the nested containers
    // 1 = 2 + 3
    // 3 = POD + 4
    // 4 = POD + 5
    // Add in the POD data and then nest the containers to produce the same output stream
    tnrcontainer1->Add(u8);
    tnrcontainer2->Add(u16);
    tnrcontainer2->Add(u24);
    tnrcontainer3->Add(u32);
    tnrcontainer3->Add(s8);
    tnrcontainer3->Add(s16);
    tnrcontainer3->Add(s24a);
    tnrcontainer3->Add(s24b);
    tnrcontainer4->Add(s24c);
    tnrcontainer4->Add(s24d);
    tnrcontainer5->Add(s24e);
    tnrcontainer5->Add(s32a);
    tnrcontainer5->Add(s32b);
    tnrcontainer5->Add(s32c);

    tnrcontainer4->Add(tnrcontainer5);
    tnrcontainer3->Add(tnrcontainer4);
    tnrcontainer1->Add(tnrcontainer2);
    tnrcontainer1->Add(tnrcontainer3);

    tnrcontainer1->write(mswif);

    // Check memory stream equals predicted stream
    result = result && (_wstream->str() == rhs);

    // Now that we have written what we expected to the stream, we should read it back
    // Create one of each type of variable with 0 values
    POD_U8_ptr read_u8(new POD_U8(0x00, "U8"));
    POD_U16_ptr read_u16(new POD_U16(0x00, "U16"));
    POD_U24_ptr read_u24(new POD_U24(0x000000, "U24"));
    POD_U32_ptr read_u32(new POD_U32(0x00000000, "U32"));
    POD_S8_ptr read_s8(new POD_S8(0x00, "S8"));
    POD_S16_ptr read_s16(new POD_S16(0x0000, "S16"));
    POD_S24_ptr read_s24a(new POD_S24(0, "S24"));
    POD_S24_ptr read_s24b(new POD_S24(0x000000, "S24"));
    POD_S24_ptr read_s24c(new POD_S24(0x000000, "S24"));
    POD_S24_ptr read_s24d(new POD_S24(0, "S24"));
    POD_S24_ptr read_s24e(new POD_S24(0, "S24"));
    POD_S32_ptr read_s32a(new POD_S32(0x00, "S32"));
    POD_S32_ptr read_s32b(new POD_S32(0x00, "S32"));
    POD_S32_ptr read_s32c(new POD_S32(0x00, "S32"));

    TNRContainer_ptr read_tnrcontainer1(new TNRContainer("Readback Nested Container1"));
    TNRContainer_ptr read_tnrcontainer2(new TNRContainer("Readback Nested Container2"));
    TNRContainer_ptr read_tnrcontainer3(new TNRContainer("Readback Nested Container3"));
    TNRContainer_ptr read_tnrcontainer4(new TNRContainer("Readback Nested Container4"));
    TNRContainer_ptr read_tnrcontainer5(new TNRContainer("Readback Nested Container5"));

    // Build the nested containers
    // 1 = 2 + 3
    // 3 = POD + 4
    // 4 = POD + 5
    // Add in the POD data and then nest the containers to produce the same output stream
    read_tnrcontainer1->Add(read_u8);
    read_tnrcontainer2->Add(read_u16);
    read_tnrcontainer2->Add(read_u24);
    read_tnrcontainer3->Add(read_u32);
    read_tnrcontainer3->Add(read_s8);
    read_tnrcontainer3->Add(read_s16);
    read_tnrcontainer3->Add(read_s24a);
    read_tnrcontainer3->Add(read_s24b);
    read_tnrcontainer4->Add(read_s24c);
    read_tnrcontainer4->Add(read_s24d);
    read_tnrcontainer5->Add(read_s24e);
    read_tnrcontainer5->Add(read_s32a);
    read_tnrcontainer5->Add(read_s32b);
    read_tnrcontainer5->Add(read_s32c);

    read_tnrcontainer4->Add(read_tnrcontainer5);
    read_tnrcontainer3->Add(read_tnrcontainer4);
    read_tnrcontainer1->Add(read_tnrcontainer2);
    read_tnrcontainer1->Add(read_tnrcontainer3);

    read_tnrcontainer1->read(msrif);

    // Check the readback matches the original
    result = result && (*read_u8 == *u8);
    result = result && (*read_u16 == *u16);
    result = result && (read_u24->getValue() == u24->getValue());
    result = result && (*read_u32 == *u32);

    result = result && (*read_s8 == *s8);
    result = result && (*read_s16 == *s16);
    result = result && (read_s24a->getValue() == s24a->getValue());
    result = result && (read_s24b->getValue() == s24b->getValue());
    result = result && (read_s24c->getValue() == s24c->getValue());
    result = result && (read_s24d->getValue() == s24d->getValue());
    result = result && (read_s24e->getValue() == s24e->getValue());

    result = result && (read_s32a->getValue() == s32a->getValue());
    result = result && (read_s32b->getValue() == s32b->getValue());
    result = result && (*read_s32c == s32c->getValue());

    return result;
}

/**
 * This test builds on the memory stream interface test: that test writes and reads the stream
 * from individual POD variables. This test repeats write and read but puts the variables
 * into a TNRContainer first.
 */
bool POD_Tester::testTNRContainer()
{
    bool result = true;    // test passed

    // Avoiding any 0x00 bytes as these will terminate the string
    const unsigned char testBytes[] = { 0x45, 0x12, 0xA0, 0x90, 0x27, 0x13, 0x21, 0x43, 0x65, 0x87,
            // Signed value testing
                0xb0,
                0x65, 0x87,
                0xff, 0xff, 0xff,
                0x76, 0x98, 0xba,
                0x32, 0x54, 0x76,
                0xc0, 0xf2, 0xfc,
                0x40, 0x0d, 0x03,                // CR
                0xff, 0xff, 0xff, 0xff,
                0x78, 0x56, 0x34, 0x12,
                0x78, 0x56, 0x34, 0xc2
    };

    std::string rhs((const char *)testBytes);

    std::shared_ptr<std::stringstream> _wstream(new std::stringstream());
    std::shared_ptr<std::stringstream> _rstream(new std::stringstream(rhs));

    StreamWriteIf mswif(_wstream);
    StreamReadIf msrif(_rstream);

    TNRContainer tnrcontainer("Test Container");

    // Create one of each type of variable
    POD_U8_ptr u8(new POD_U8(0x45, "U8"));
    POD_U16_ptr u16( new POD_U16 (0xA012, "U16"));
    POD_U24_ptr u24( new POD_U24 (0x132790, "U24"));
    POD_U32_ptr u32( new POD_U32 (0x87654321, "U32"));
    POD_S8_ptr s8( new POD_S8 (0xb0, "S8"));
    POD_S16_ptr s16( new POD_S16 (0x8765, "S16"));
    POD_S24_ptr s24a( new POD_S24 (-1, "S24"));
    POD_S24_ptr s24b( new POD_S24 (0xba9876, "S24"));
    POD_S24_ptr s24c( new POD_S24 (0x765432, "S24"));
    POD_S24_ptr s24d( new POD_S24 (-200000, "S24"));
    POD_S24_ptr s24e( new POD_S24 (200000, "S24"));        // 200000=0x030d40, 200256=0x030e40 no CR in bytes
    POD_S32_ptr s32a( new POD_S32 (0xffffffff, "S32"));
    POD_S32_ptr s32b( new POD_S32 (0x12345678, "S32"));
    POD_S32_ptr s32c( new POD_S32 (0xc2345678, "S32"));

    tnrcontainer.Add(u8);
    tnrcontainer.Add(u16);
    tnrcontainer.Add(u24);
    tnrcontainer.Add(u32);
    tnrcontainer.Add(s8);
    tnrcontainer.Add(s16);
    tnrcontainer.Add(s24a);
    tnrcontainer.Add(s24b);
    tnrcontainer.Add(s24c);
    tnrcontainer.Add(s24d);
    tnrcontainer.Add(s24e);
    tnrcontainer.Add(s32a);
    tnrcontainer.Add(s32b);
    tnrcontainer.Add(s32c);

    tnrcontainer.write(mswif);

    // Check memory stream equals predicted stream
    result = result && (_wstream->str() == rhs);

    printString("rstream ", _rstream->str());

    // Now push the contents of the write stream into the input stream

    // Now that we have written what we expected to the stream, we should read it back
    // Create one of each type of variable with 0 values
    POD_U8_ptr read_u8(new POD_U8(0x00, "U8"));
    POD_U16_ptr read_u16(new POD_U16(0x00, "U16"));
    POD_U24_ptr read_u24(new POD_U24(0x000000, "U24"));
    POD_U32_ptr read_u32(new POD_U32(0x00000000, "U32"));
    POD_S8_ptr read_s8(new POD_S8(0x00, "S8"));
    POD_S16_ptr read_s16(new POD_S16(0x0000, "S16"));
    POD_S24_ptr read_s24a(new POD_S24(0, "S24"));
    POD_S24_ptr read_s24b(new POD_S24(0x000000, "S24"));
    POD_S24_ptr read_s24c(new POD_S24(0x000000, "S24"));
    POD_S24_ptr read_s24d(new POD_S24(0, "S24"));
    POD_S24_ptr read_s24e(new POD_S24(0, "S24"));
    POD_S32_ptr read_s32a(new POD_S32(0x00, "S32"));
    POD_S32_ptr read_s32b(new POD_S32(0x00, "S32"));
    POD_S32_ptr read_s32c(new POD_S32(0x00, "S32"));

    // Read back into these from the stream - not using a container
    result = result && (read_u8->read(msrif) == 0);
    result = result && (read_u16->read(msrif) == 0);
    result = result && (read_u24->read(msrif) == 0);
    result = result && (read_u32->read(msrif) == 0);
    result = result && (read_s8->read(msrif) == 0);
    result = result && (read_s16->read(msrif) == 0);
    result = result && (read_s24a->read(msrif) == 0);
    result = result && (read_s24b->read(msrif) == 0);
    result = result && (read_s24c->read(msrif) == 0);
    result = result && (read_s24d->read(msrif) == 0);
    result = result && (read_s24e->read(msrif) == 0);
    result = result && (read_s32a->read(msrif) == 0);
    result = result && (read_s32b->read(msrif) == 0);
    result = result && (read_s32c->read(msrif) == 0);

    // Check the readback matches the original
    result = result && (*read_u8 == *u8);
    result = result && (*read_u16 == *u16);
    result = result && (read_u24->getValue() == u24->getValue());
    result = result && (*read_u32 == *u32);

    result = result && (*read_s8 == *s8);
    result = result && (*read_s16 == *s16);
    result = result && (read_s24a->getValue() == s24a->getValue());
    result = result && (read_s24b->getValue() == s24b->getValue());
    result = result && (read_s24c->getValue() == s24c->getValue());
    result = result && (read_s24d->getValue() == s24d->getValue());
    result = result && (read_s24e->getValue() == s24e->getValue());

    result = result && (read_s32a->getValue() == s32a->getValue());
    result = result && (read_s32b->getValue() == s32b->getValue());
    result = result && (*read_s32c == s32c->getValue());

    // Now test reading back using a tnr container
    // Create a stream from a string, create a matching container,
    // read it back and check the values again

    // Make the string stream that msrif uses contain the reference string again
    _rstream->str(rhs);

    // Read back from the test string
    tnrcontainer.read(msrif);

    // Check that the values match
    result = result && (*read_u8 == *u8);
    result = result && (*read_u16 == *u16);
    result = result && (read_u24->getValue() == u24->getValue());
    result = result && (*read_u32 == *u32);

    result = result && (*read_s8 == *s8);
    result = result && (*read_s16 == *s16);
    result = result && (read_s24a->getValue() == s24a->getValue());
    result = result && (read_s24b->getValue() == s24b->getValue());
    result = result && (read_s24c->getValue() == s24c->getValue());
    result = result && (read_s24d->getValue() == s24d->getValue());
    result = result && (read_s24e->getValue() == s24e->getValue());

    result = result && (read_s32a->getValue() == s32a->getValue());
    result = result && (read_s32b->getValue() == s32b->getValue());
    result = result && (*read_s32c == s32c->getValue());

    return result;
}

bool POD_Tester::testPODType()
{
    bool result = true;    // test passed
    POD_U8 u8(0x45, "U8");
    POD_U16 u16(0xA012, "U16");
    POD_U24 u24(0x132790, "U24");
    POD_U32 u32(0x87654321, "U32");
    POD_S8 s8(-80, "S8");
    POD_S16 s16(-768, "S16");
    POD_S24 s24a(-1, "S24");
    POD_S24 s24b(-1024, "S24");
    POD_S24 s24c(1024, "S24");
    POD_S24 s24d(-200000, "S24");
    POD_S24 s24e(200000, "S24");
    POD_S32 s32(0xffffffff, "S32");

    result = result && (u8.getValue() == 0x45);
    result = result && (u16.getValue() == 0xA012);
    U32 a = u24.getValue();
    result = result && (0x132790 == a);
    result = result && (u32.getValue() == 0x87654321);

    result = result && (s8.getValue() == -80);
    result = result && (s16.getValue() == -768);
    auto ba = (S32)s24a.getValue();
    auto bb = (S32)s24b.getValue();
    auto bc = (S32)s24c.getValue();
    auto bd = (S32)s24d.getValue();
    auto be = (S32)s24e.getValue();
    result = result && (ba == -1);
    result = result && (bb == -1024);
    result = result && (bc == 1024);
    result = result && (bd == -200000);
    result = result && (be == 200000);
    result = result && (s32.getValue() == (S32)0xffffffff);

    return result;
}

/**
 * Write bytes to the interface and see if we get what we expected back out again
 */
bool POD_Tester::testMemoryStreamIf()
{
    bool result = true;
    std::shared_ptr<std::ostream> _wstream(new std::stringstream);

    StreamWriteIf mswif(_wstream);

    // Create one of each type of variable
    POD_U8 u8(0x45, "U8");
    POD_U16 u16(0xA012, "U16");
    POD_U24 u24(0x132790, "U24");
    POD_U32 u32(0x87654321, "U32");
    POD_S8 s8(0xb0, "S8");
    POD_S16 s16(0x8765, "S16");
    POD_S24 s24a(-1, "S24a");
    POD_S24 s24b(0xba9876, "S24b");
    POD_S24 s24c(0x765432, "S24c");
    POD_S24 s24d(-200000, "S24d");
    POD_S24 s24e(200000, "S24e");
    POD_S32 s32a(0xffffffff, "S32a");
    POD_S32 s32b(0x12345678, "S32b");
    POD_S32 s32c(0xc2345678, "S32c");

    // Avoiding any 0x00 bytes as these will terminate the string
    const unsigned char testBytes[] = { 0x45, 0x12, 0xA0, 0x90, 0x27, 0x13, 0x21, 0x43, 0x65, 0x87,
            // Signed value testing
                0xb0,
                0x65, 0x87,
                0xff, 0xff, 0xff,
                0x76, 0x98, 0xba,
                0x32, 0x54, 0x76,
                0xc0, 0xf2, 0xfc,
                0x40, 0x0d, 0x03,
                0xff, 0xff, 0xff, 0xff,
                0x78, 0x56, 0x34, 0x12,
                0x78, 0x56, 0x34, 0xc2
    };

    std::string rhs((const char *)testBytes);

    result = result && (u8.write(mswif) == 0);
    result = result && (u16.write(mswif) == 0);
    result = result && (u24.write(mswif) == 0);
    result = result && (u32.write(mswif) == 0);
    result = result && (s8.write(mswif) == 0);
    result = result && (s16.write(mswif) == 0);
    result = result && (s24a.write(mswif) == 0);
    result = result && (s24b.write(mswif) == 0);
    result = result && (s24c.write(mswif) == 0);
    result = result && (s24d.write(mswif) == 0);
    result = result && (s24e.write(mswif) == 0);
    result = result && (s32a.write(mswif) == 0);
    result = result && (s32b.write(mswif) == 0);
    result = result && (s32c.write(mswif) == 0);

    // Is the string in the output stream equal to the predicted stream?
    // Tricky casting to turn the generic ostream pointer into the actual stringstream
    result = result && (std::dynamic_pointer_cast<std::stringstream>(_wstream)->str() == rhs);

    std::shared_ptr<std::istream> _rstream(new std::stringstream(rhs));
    StreamReadIf msrif(_rstream);
    printString("rstream ", std::dynamic_pointer_cast<std::stringstream>(_rstream)->str());

    // Now push the contents of the write stream into the input stream

    // Now that we have written what we expected to the stream, we should read it back
    // Create one of each type of variable with 0 values
    POD_U8 read_u8(0x00, "U8");
    POD_U16 read_u16(0x00, "U16");
    POD_U24 read_u24(0x000000, "U24");
    POD_U32 read_u32(0x00000000, "U32");
    POD_S8 read_s8(0x00, "S8");
    POD_S16 read_s16(0x0000, "S16");
    POD_S24 read_s24a(0, "S24");
    POD_S24 read_s24b(0x000000, "S24");
    POD_S24 read_s24c(0x000000, "S24");
    POD_S24 read_s24d(0, "S24");
    POD_S24 read_s24e(0, "S24");
    POD_S32 read_s32a(0x00, "S32");
    POD_S32 read_s32b(0x00, "S32");
    POD_S32 read_s32c(0x00, "S32");

    // Read back into these from the stream
    result = result && (read_u8.read(msrif) == 0);
    result = result && (read_u16.read(msrif) == 0);
    result = result && (read_u24.read(msrif) == 0);
    result = result && (read_u32.read(msrif) == 0);
    result = result && (read_s8.read(msrif) == 0);
    result = result && (read_s16.read(msrif) == 0);
    result = result && (read_s24a.read(msrif) == 0);
    result = result && (read_s24b.read(msrif) == 0);
    result = result && (read_s24c.read(msrif) == 0);
    result = result && (read_s24d.read(msrif) == 0);
    result = result && (read_s24e.read(msrif) == 0);
    result = result && (read_s32a.read(msrif) == 0);
    result = result && (read_s32b.read(msrif) == 0);
    result = result && (read_s32c.read(msrif) == 0);

    result = result && (read_u8 == u8);
    result = result && (read_u16 == u16);
    result = result && (read_u24.getValue() == u24.getValue());
    result = result && (read_u32 == u32);
    result = result && (read_s8 == s8);
    result = result && (read_s16 == s16);
    result = result && (read_s24a.getValue() == s24a.getValue());
    result = result && (read_s24b.getValue() == s24b.getValue());
    result = result && (read_s24c.getValue() == s24c.getValue());
    result = result && (read_s24d.getValue() == s24d.getValue());
    result = result && (read_s24e.getValue() == s24e.getValue());

    result = result && (read_s32a.getValue() == s32a.getValue());
    result = result && (read_s32b.getValue() == s32b.getValue());
    result = result && (read_s32c.getValue() == s32c.getValue());

    return result;
}

bool POD_Tester::testFixedArray()
{
    bool result = true;
    std::shared_ptr<std::ostream> _stream(new std::stringstream);
    StreamWriteIf mswif(_stream);

    POD_U32_ptr val1(new POD_U32(0x11111111, "val"));
    POD_U32_ptr val2(new POD_U32(0x22222222, "val"));
    POD_U32_ptr val3(new POD_U32(0x33333333, "val"));

    // Create FixedArrays, one with 6 copies of val1 and one with {val3, val2, val1}
    tnr_baseData_ptr recordType1(new POD_U32(0, "POD_U32 recordType1"));
    TNRFixedArray u32array1("Array of 6 U32", 6, recordType1);

    for (int i = 0; i < 6; i++)
    {
        u32array1[i] = val1;
    }

    tnr_baseData_ptr recordType2(new POD_U32(0, "POD_U32 recordType2"));
    TNRFixedArray u32array2("Array of 3 U32", 3, recordType2);

    u32array2[0] = val3;
    u32array2[1] = val2;
    u32array2[2] = val1;

    // Avoiding any 0x00 bytes as these will terminate the string
    const U32 testBytes[] = {
            0x11111111,
            0x11111111,
            0x11111111,
            0x11111111,
            0x11111111,
            0x11111111,
            0x33333333,
            0x22222222,
            0x11111111,
            0x00000000
    };

    std::string rhs((const char *)testBytes);

    // Write both values to stream
    result = result && (u32array1.write(mswif) == 0);
    result = result && (u32array2.write(mswif) == 0);

    // Is the string in the output stream equal to the predicted stream?
    printString("stream", std::dynamic_pointer_cast<std::stringstream>(_stream)->str());
    printString("rhs   ", rhs);

    // Is the string in the output stream equal to the predicted stream?
    // Tricky casting to turn the generic ostream pointer into the actual stringstream
    result = result && (std::dynamic_pointer_cast<std::stringstream>(_stream)->str() == rhs);

    // Readback test - create a new empty FixedArray and read it back from the stream
    TNRFixedArray read_u32array1("Readback Array of U32", 6, recordType1);
    TNRFixedArray read_u32array2("Array of 3 U32", 3, recordType2);
    std::shared_ptr<std::istream> _rstream(new std::stringstream(rhs));
    StreamReadIf msrif(_rstream);

    result = result && (read_u32array1.read(msrif) == 0);
    result = result && (read_u32array2.read(msrif) == 0);

    // Check the result of this
    result = result && (read_u32array1.getItemCount() == 6);
    result = result && (read_u32array2.getItemCount() == 3);

    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (U32 i = 0; i < read_u32array1.getItemCount(); i++)
    {
        result = result && (read_u32array1[i]->getCount() == u32array1[i]->getCount());
    }
    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (U32 i = 0; i < read_u32array2.getItemCount(); i++)
    {
        result = result && (read_u32array2[i]->getCount() == u32array2[i]->getCount());
    }

    return result;
}

bool POD_Tester::testCountedArray()
{
    bool result = true;
    std::shared_ptr<std::ostream> _stream(new std::stringstream);
    StreamWriteIf mswif(_stream);

    POD_U16_ptr val1(new POD_U16(0x1234, "val"));
    POD_U16_ptr val2(new POD_U16(0x5678, "val"));
    POD_U16_ptr val3(new POD_U16(0x9ABC, "val"));

    // Create FixedArrays, one with 6 copies of val1 and one with {val3, val2, val1}
    tnr_baseData_ptr countType1(new POD_U8(6, "POD_U8 countType1"));
    tnr_baseData_ptr recordType1(new POD_U16(0, "POD_U16 recordType1"));
    TNRCountedArray u16array1("Array of 6 U32", countType1, recordType1);

    for (int i = 0; i < 6; i++)
    {
        u16array1[i] = val1;
    }

    tnr_baseData_ptr countType2(new POD_U8(3, "POD_U8 countType2"));
    tnr_baseData_ptr recordType2(new POD_U16(0, "POD_U16 recordType2"));
    TNRCountedArray u16array2("Array of 3 U32", countType2, recordType1);

    u16array2[0] = val3;
    u16array2[1] = val2;
    u16array2[2] = val1;

    // Avoiding any 0x00 bytes as these will terminate the string
    const U8 testBytes[] = {
            0x06,            // count
            0x34, 0x12,
            0x34, 0x12,
            0x34, 0x12,
            0x34, 0x12,
            0x34, 0x12,
            0x34, 0x12,
            0x03,            // count
            0xBC, 0x9A,
            0x78, 0x56,
            0x34, 0x12,
            0x00
    };

    std::string rhs((const char *)testBytes);

    // Write both values to stream
    result = result && (u16array1.write(mswif) == 0);
    result = result && (u16array2.write(mswif) == 0);

    // Is the string in the output stream equal to the predicted stream?
    printString("stream", std::dynamic_pointer_cast<std::stringstream>(_stream)->str());
    printString("rhs   ", rhs);

    // Tricky casting to turn the generic ostream pointer into the actual stringstream
    result = result && (std::dynamic_pointer_cast<std::stringstream>(_stream)->str() == rhs);

    // Readback test - create a new empty CountedArray and read it back from the stream
    tnr_baseData_ptr read_countType1(new POD_U8(0, "POD_U8 countType1"));
    tnr_baseData_ptr read_recordType1(new POD_U16(0, "POD_U16 recordType1"));
    TNRCountedArray read_u16array1("Array of U32", read_countType1, read_recordType1);

    tnr_baseData_ptr read_countType2(new POD_U8(0, "POD_U8 countType2"));
    tnr_baseData_ptr read_recordType2(new POD_U16(0, "POD_U16 recordType2"));
    TNRCountedArray read_u16array2("Array of U32", read_countType2, read_recordType1);

    std::shared_ptr<std::istream> _rstream(new std::stringstream(rhs));
    StreamReadIf msrif(_rstream);

    result = result && (read_u16array1.read(msrif) == 0);
    result = result && (read_u16array2.read(msrif) == 0);

    // Check the result of this
//    U32 temp = read_u16array1.getItemCount();
//    result = result && (temp == 6);
    result = result && (read_u16array1.getItemCount() == 6);
    result = result && (read_u16array2.getItemCount() == 3);

    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (U32 i = 0; i < read_u16array1.getItemCount(); i++)
    {
        result = result && (read_u16array1[i]->getCount() == u16array1[i]->getCount());
    }
    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (U32 i = 0; i < read_u16array2.getItemCount(); i++)
    {
        result = result && (read_u16array2[i]->getCount() == u16array2[i]->getCount());
    }



    return result;
}

bool POD_Tester::testTNR_C_String()
{
    bool result = true;

    // Make the expected binary output stream
    std::string rhs;
    rhs.append("Teddy");
    rhs.push_back('\0');
    rhs.append("Roger");
    rhs.push_back('\0');
    rhs.append("Teddy");
    rhs.push_back('\0');

    std::shared_ptr<std::stringstream> _wstream(new std::stringstream());
    std::shared_ptr<std::stringstream> _rstream(new std::stringstream(rhs));

//    std::shared_ptr<std::ostream> _stream(new std::stringstream);
    StreamWriteIf mswif(_wstream);
    StreamReadIf msrif(_rstream);

    // Create two strings and clone one of them
    TNR_C_String_ptr string1(new TNR_C_String("Teddy", "Name"));
    TNR_C_String_ptr string2(new TNR_C_String("Roger", "Name"));
    TNR_C_String_ptr string3(new TNR_C_String(string1->getValue(), "Name"));

    result = result && (string1->write(mswif) == 0);
    result = result && (string2->write(mswif) == 0);
    result = result && (string3->write(mswif) == 0);

    // Check that the streams match
    printString("wstream ", _wstream->str());
    printString("rstream ", _rstream->str());
    result = result && (_wstream->str() == rhs);

    // Test reading back from the input stream, which matches the written stream
    TNR_C_String_ptr read_string1(new TNR_C_String("", ""));
    TNR_C_String_ptr read_string2(new TNR_C_String("", ""));
    TNR_C_String_ptr read_string3(new TNR_C_String("", ""));

    // Read back from stream
    result = result && (read_string1->read(msrif) == 0);
    result = result && (read_string2->read(msrif) == 0);
    result = result && (read_string3->read(msrif) == 0);

    // Check that readback matches input
    result = result && (string1->getValue() == read_string1->getValue());
    result = result && (string2->getValue() == read_string2->getValue());
    result = result && (string3->getValue() == read_string3->getValue());

    // Some diagnostics
    cout << "string1 <" << string1->getValue() << "> read back <" << read_string1->getValue() << ">" << endl;
    cout << "string2 <" << string2->getValue() << "> read back <" << read_string2->getValue() << ">" << endl;
    cout << "string3 <" << string3->getValue() << "> read back <" << read_string3->getValue() << ">" << endl;

    return result;
}

bool POD_Tester::testObjectMap()
{
    bool result = true;
    ObjectMap m;
    tnr_baseData_ptr val1(new POD_U16(0x1234, "val1"));
    tnr_baseData_ptr val2(new POD_U8(0x12, "val2"));
    tnr_baseData_ptr val3(new POD_U24(0x123400, "val3"));
    tnr_baseData_ptr val4(new POD_U32(0x00001234, "val4"));
    tnr_baseData_ptr val5(new POD_U32(200000, "val5"));
    tnr_baseData_ptr j;

    // Add different objects - should succeed
    result = result && m.AddObject(val1);
    result = result && m.AddObject(val2);

    m.PrintMap();
    result = result && m.AddObject(val3);
    result = result && m.AddObject(val4);

    // Try and add existing objects - should fail
    result = result && !m.AddObject(val3);
    result = result && !m.AddObject(val4);

    result = result && m.AddObject(val5);

    // Try and add existing objects - should fail
    result = result && !m.AddObject(val1);
    result = result && !m.AddObject(val2);

    m.PrintMap();

    if (m.FindObject(val5->getDescription(), j))
    {
        result = (j->getCount() == val5->getCount());
    }

    return result;
}

bool testVariantWithSelector(tnr_baseData_ptr selector, std::vector<unsigned char> &input)
{
    bool result = true;

    // Make a variant with U8 selector
    TNR_Variant_ptr v = make_shared<TNR_Variant>();
//    v->setSelector(make_shared<POD_U8>(0, "Selector"));
    v->setSelector(selector);

    v->addObject(1, make_shared<POD_U8>(0, "Variant 1"));
    v->addObject(2, make_shared<POD_U16>(0, "Variant 2"));
    v->addObject(3, make_shared<POD_U24>(0, "Variant 3"));
    v->addObject(4, make_shared<POD_U32>(0, "Variant 4"));


    // Make the expected binary output stream
    std::string rhs;
    std::string lhs;
//    std::vector<unsigned char> input = {
//            0x01, 0xaa,
//            0x02, 0xaa, 0xbb,
//            0x03, 0xaa, 0xbb, 0xcc,
//            0x04, 0xaa, 0xbb, 0xcc, 0xdd };

    for (char c: input)
    {
        rhs += c;
    }

    std::shared_ptr<std::stringstream> _wstream(new std::stringstream());
    std::shared_ptr<std::stringstream> _rstream(new std::stringstream(rhs));

    StreamWriteIf mswif(_wstream);
    StreamReadIf msrif(_rstream);

    // Read a variant, then write it - at the end the output should match the input
    v->read(msrif);
    v->write(mswif);
    v->read(msrif);
    v->write(mswif);
    v->read(msrif);
    v->write(mswif);
    v->read(msrif);
    v->write(mswif);

    lhs = _wstream->str();

    return (lhs == rhs);
}

bool POD_Tester::testVariant()
{
    bool result = true;

    std::vector<unsigned char> inputU8Selector = {
            0x01, 0xaa,
            0x02, 0xaa, 0xbb,
            0x03, 0xaa, 0xbb, 0xcc,
            0x04, 0xaa, 0xbb, 0xcc, 0xdd };

    result = testVariantWithSelector(make_shared<POD_U8>(0, "Selector"), inputU8Selector);

    std::vector<unsigned char> inputU16Selector = {
            0x01, 0x00, 0xaa,
            0x02, 0x00, 0xaa, 0xbb,
            0x03, 0x00, 0xaa, 0xbb, 0xcc,
            0x04, 0x00, 0xaa, 0xbb, 0xcc, 0xdd };

    result = testVariantWithSelector(make_shared<POD_U16>(0, "Selector"), inputU16Selector);

    std::vector<unsigned char> inputU24Selector = {
            0x01, 0x00, 0x00, 0xaa,
            0x02, 0x00, 0x00, 0xaa, 0xbb,
            0x03, 0x00, 0x00, 0xaa, 0xbb, 0xcc,
            0x04, 0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xdd };

    result = testVariantWithSelector(make_shared<POD_U24>(0, "Selector"), inputU24Selector);

    std::vector<unsigned char> inputU32Selector = {
            0x01, 0x00, 0x00, 0x00, 0xaa,
            0x02, 0x00, 0x00, 0x00, 0xaa, 0xbb,
            0x03, 0x00, 0x00, 0x00, 0xaa, 0xbb, 0xcc,
            0x04, 0x00, 0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xdd };

    result = testVariantWithSelector(make_shared<POD_U32>(0, "Selector"), inputU32Selector);

    return result;
}

