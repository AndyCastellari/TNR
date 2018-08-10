/*
 * tnr_portability.h
 *
 * File to allow use of typedef for types U8, S8, U16, etc.
 * This file can be replaced (if required) to provide the types
 * in any suitable way.
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

#ifndef TNR_PORTABILITY_H_
#define TNR_PORTABILITY_H_

#include <stdio.h>

typedef signed char S8;
typedef unsigned char U8;
typedef signed short S16;
typedef unsigned short U16;
typedef signed int S32;
typedef unsigned int U32;
//typedef char CHAR;

typedef struct u24
{
public:
    u24(U32 value) { c[0] = value & 0xff; c[1] = (value >> 8) & 0xff; c[2] = (value >> 16) & 0xff; };
    operator U32() { U32 t = 0; t = (c[2] << 16) + (c[1] << 8) + (c[0] << 0); return t; };
//    bool operator==(const U32 rhs) { return U32() == rhs; };
//protected:
    U8 c[3];
} U24;


typedef struct s24
{
public:
    s24(S32 value) { U32 t = (U32)value; c[0] = t & 0xff; c[1] = (t >> 8) & 0xff; c[2] = (t >> 16) & 0xff; };
    operator S32()
            {
        U32 t = 0;
        t = (c[2] << 16) + (c[1] << 8) + (c[0] << 0);
        // Sign extend negative 24-bit value to 32-bits
        if (t & 0x800000) t = t | 0xff000000;
        return (S32)t; };
//    bool operator==(const S32 rhs) { return S32() == rhs; };
//protected:
    U8 c[3];
} S24;


#endif /* TNR_PORTABILITY_H_ */
