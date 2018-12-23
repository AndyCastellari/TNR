/*
 * PODTester.h
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

#ifndef PODTESTER_H_
#define PODTESTER_H_

class POD_Tester
{
public:
    POD_Tester() = default;
    virtual ~POD_Tester() = default;

    bool testPODType();

    bool testFixedArray();

    bool testCountedArray();

    bool testMemoryStreamIf();

    bool testTNRContainer();

    bool testTNRNestedContainer();

    bool testTNR_C_String();

    bool testTextLogWriteIf();
    bool testSimpleTextWriteIf();
    bool testTextWriteIf(tnr::tnr_write_interface & wif);

    bool testObjectMap();
};

#endif /* PODTESTER_H_ */
