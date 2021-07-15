/*
 * BaseBinaryArchiveWrite.cpp
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

#include "BaseBinaryArchiveReadWrite.h"

namespace tnr {

// These methods wrap up sending the correct number of bytes to the derived classes

    int BaseBinaryArchiveWrite::write(U8 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 1);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(S8 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 1);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(U16 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 2);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(S16 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 2);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(U24 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 3);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(S24 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 3);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(U32 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 4);
        return result;
    }

    int tnr::BaseBinaryArchiveWrite::write(S32 value, std::string &, tnr_format &) {
        int result = 0;
        result = writeBytes((U32) value, 4);
        return result;
    }

/**
 * Write a c-style string into the binary stream
 */
    int tnr::BaseBinaryArchiveWrite::write(std::string &value, std::string &, tnr_format &) {
        int result = 0;
        // Output characters in string
        for (U32 i = 0; i < value.length() && (result == 0); i++) {
            result = writeOneByte((U8) value[i]);
        }
        // Null-terminate the string in the output binary data
        result = writeOneByte(0);

        return result;
    }

    void BaseBinaryArchiveWrite::nextLevel(tnr_format &) {
    }

    void BaseBinaryArchiveWrite::previousLevel(tnr_format &) {
    }

    int BaseBinaryArchiveWrite::write(std::string &, tnr_format &) {
        return 0;
    }

//============================================================================================
// LSB Implementation - overrides writeBytes

/**
 * Converts the value passed in to a series of bytes in LSB order and writes them
 * using the pure virtual method writeOneByte(), which is implemented by derived classes
 */
    int tnr::LSBBaseBinaryArchiveWrite::writeBytes(U32 value, U32 noOfBytes) {
        int result = 0;

        // If noOfBytes == 1 loop iterates once with value >> 0
        // If noOfBytes == 4 loop iterates four times with
        // value >> 0 = value >> 0
        // value >> 1 = value >> 1
        // value >> 2 = value >> 2
        // value >> 3 = value >> 3
        for (unsigned int i = 0; i < noOfBytes; i++) {
            if (result == 0) {
                result = writeOneByte((U8) ((value >> (i * 8)) & 0xffU));
            }
        }

        return result;
    }

//============================================================================================
// MSB Implementation - overrides writeBytes

/**
 * Converts the value passed in to a series of bytes in MSB order and writes them
 * using the pure virtual method writeOneByte(), which is implemented by derived classes
 */
    int tnr::MSBBaseBinaryArchiveWrite::writeBytes(U32 value, U32 noOfBytes) {
        int result = 0;

        // If noOfBytes == 1 loop iterates once with value >> (1-1) - 0
        // If noOfBytes == 4 loop iterates four times with
        // value >> (4-1) - 0 = value >> 3
        // value >> (4-1) - 1 = value >> 2
        // value >> (4-1) - 2 = value >> 1
        // value >> (4-1) - 3 = value >> 0
        for (unsigned int i = 0; i < noOfBytes; i++) {
            if (result == 0) {
                result = writeOneByte((U8) ((value >> (((noOfBytes - 1) - i) * 8)) & 0xffU));
            }
        }

        return result;
    }


//================================READ IMPLEMENTATION====================================================================

// These methods wrap up sending the correct number of bytes to the derived classes

    int tnr::BaseBinaryArchiveRead::read(U8 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 1);
        value = (U8) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(S8 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 1);
        value = (S8) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(U16 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 2);
        value = (U16) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(S16 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 2);
        value = (S16) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(U24 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 3);
        value = (U24) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(S24 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 3);
        value = (S24) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(U32 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 4);
        value = (U32) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(S32 &value, tnr_format &) {
        int result = 0;
        U32 temp = 0;
        result = readBytes(temp, 4);
        value = (S32) temp;
        return result;
    }

    int tnr::BaseBinaryArchiveRead::read(std::string &value, tnr_format &) {
        int result = 0;
        U8 c = '\0';
        char temp[2] = {0, 0};

        do {
            result = readOneByte(c);
            if ((result == 0) && (c != '\0')) {
                temp[0] = c;
                value.append(temp);
            }
        } while (c != '\0');

        return result;
    }

    void BaseBinaryArchiveRead::nextLevel(tnr_format &) {
    }

    void BaseBinaryArchiveRead::previousLevel(tnr_format &) {
    }


//============================================================================================
// LSB Implementation - overrides writeBytes

/**
 * Converts the value passed in to a series of bytes in LSB order and writes them
 * using the pure virtual method writeOneByte(), which is implemented by derived classes
 */
    int tnr::LSBBaseBinaryArchiveRead::readBytes(U32 &value, U32 noOfBytes) {
        int result = 0;

        // If noOfBytes == 1 loop iterates once with value >> 0
        // If noOfBytes == 4 loop iterates four times with
        // value >> 0 = value >> 0
        // value >> 1 = value >> 1
        // value >> 2 = value >> 2
        // value >> 3 = value >> 3
        for (unsigned int i = 0; i < noOfBytes; i++) {
            if (result == 0) {
                U8 temp = 0;
                result = readOneByte(temp);
                value = value + (temp << (i * 8));
            }
        }

        return result;
    }

//============================================================================================
// MSB Implementation - overrides writeBytes

/**
 * Converts the value passed in to a series of bytes in MSB order and writes them
 * using the pure virtual method writeOneByte(), which is implemented by derived classes
 */
    int tnr::MSBBaseBinaryArchiveRead::readBytes(U32 &value, U32 noOfBytes) {
        int result = 0;

        // If noOfBytes == 1 loop iterates once with value >> (1-1) - 0
        // If noOfBytes == 4 loop iterates four times with
        // value >> (4-1) - 0 = value >> 3
        // value >> (4-1) - 1 = value >> 2
        // value >> (4-1) - 2 = value >> 1
        // value >> (4-1) - 3 = value >> 0
        for (unsigned int i = 0; i < noOfBytes; i++) {
            if (result == 0) {
                U8 temp = 0;
                result = readOneByte(temp);
                value = value + (temp << (((noOfBytes - 1) - i) * 8));
            }
        }

        return result;
    }

} /* namespace tnr */
