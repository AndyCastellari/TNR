/*
 * BaseBinaryArchiveReadWrite.h
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

#ifndef BASEBINARYARCHIVEREADWRITE_H_
#define BASEBINARYARCHIVEREADWRITE_H_

#include "tnr.h"

namespace tnr {

/**
 * This class implements most of the tnr_write_interface, in terms of writing the various
 * data types using writeBytes() method which is not implemented here. This method is
 * implemented in derived classes, which write the value passed in as n bytes in LSB or MSB order
 */
class BaseBinaryArchiveWrite: public tnr::tnr_write_interface {
public:
    BaseBinaryArchiveWrite() = default;
    ~BaseBinaryArchiveWrite() override = default;

    int write(U8 value, std::string &description, tnr_format &format ) override;
    int write(S8 value, std::string &description, tnr_format &format ) override;
    int write(U16 value, std::string &description, tnr_format &format) override;
    int write(S16 value, std::string &description, tnr_format &format) override;
    int write(U24 value, std::string &description, tnr_format &format) override;
    int write(S24 value, std::string &description, tnr_format &format) override;
    int write(U32 value, std::string &description, tnr_format &format) override;
    int write(S32 value, std::string &description, tnr_format &format) override;
    int write(std::string &value, std::string &description, tnr_format &format) override;

    // Methods to indicate when a new level of nesting is starting/ending - not relevant to plain binary streams
    void nextLevel(tnr_format &format) override;
    void previousLevel(tnr_format &format) override;

    // Methods to describe an object when this data may not be part of the output stream - not relevant to plain binary streams
    int write(std::string &description, tnr_format &format) override;
protected:
    //! Function to write a value as N bytes - used to wrap up all the various writes
    virtual int writeBytes(U32 value, U32 noOfBytes) = 0;        // Implemented by derived class to provide LSB or MSB

    //! Write one byte to the actual storage being used
    virtual int writeOneByte(U8 value) = 0;            // Implemented by derived classes to write to the actual storage medium
};

//============================================================================================
// LSB Implementation - implements writeBytes converting the value to a series of LSB bytes
class LSBBaseBinaryArchiveWrite: public tnr::BaseBinaryArchiveWrite
{
public:
    LSBBaseBinaryArchiveWrite() = default;
    ~LSBBaseBinaryArchiveWrite() override = default;
protected:
    //! Function to write a value as N bytes LSB - used to wrap up all the various writes
    int writeBytes(U32 value, U32 noOfBytes) override;
};

//============================================================================================
// MSB Implementation - implements writeBytes converting the value to MSB bytes
class MSBBaseBinaryArchiveWrite: public tnr::BaseBinaryArchiveWrite
{
public:
    MSBBaseBinaryArchiveWrite() = default;
    ~MSBBaseBinaryArchiveWrite() override = default;
protected:
    //! Function to write a value as N bytes MSB - used to wrap up all the various writes
    int writeBytes(U32 value, U32 noOfBytes) override;
};


/**
 * This class implements most of the tnr_read_interface, in terms of reading the various
 * data types using readBytes() method which is not implemented here. This method is
 * implemented in derived classes, which write the value passed in as n bytes in LSB or MSB order
 */
class BaseBinaryArchiveRead: public tnr::tnr_read_interface
{
public:
    BaseBinaryArchiveRead() = default;
    ~BaseBinaryArchiveRead() override = default;

    int read(U8 & value, tnr_format &format ) override;
    int read(S8 & value, tnr_format &format ) override;
    int read(U16 & value, tnr_format &format) override;
    int read(S16 & value, tnr_format &format) override;
    int read(U24 & value, tnr_format &format) override;
    int read(S24 & value, tnr_format &format) override;
    int read(U32 & value, tnr_format &format) override;
    int read(S32 & value, tnr_format &format) override;
    int read(std::string &value, tnr_format &format) override;

    // Methods to indicate when a new level of nesting is starting/ending - not relevant to plain binary streams
    void nextLevel(tnr_format &format) override;
    void previousLevel(tnr_format &format) override;

//     Methods to describe an object when this data may not be part of the output stream - not relevant to plain binary streams
//    virtual int read(std::string & description);
protected:
    //! Function to write a value as N bytes - used to wrap up all the various writes
    virtual int readBytes(U32 & value, U32 noOfBytes) = 0;        // Implemented by derived class to provide LSB or MSB

    //! Write one byte to the actual storage being used
    virtual int readOneByte(U8 & value) = 0;            // Implemented by derived classes to write to the actual storage medium
};

//============================================================================================
// LSB Implementation - implements writeBytes converting the value to a series of LSB bytes
class LSBBaseBinaryArchiveRead: public tnr::BaseBinaryArchiveRead
{
public:
    LSBBaseBinaryArchiveRead() = default;
    ~LSBBaseBinaryArchiveRead() override = default;
protected:
    //! Function to write a value as N bytes LSB - used to wrap up all the various writes
    int readBytes(U32 & value, U32 noOfBytes) override;
};

//============================================================================================
// MSB Implementation - implements writeBytes converting the value to MSB bytes
class MSBBaseBinaryArchiveRead: public tnr::BaseBinaryArchiveRead
{
public:
    MSBBaseBinaryArchiveRead() = default;
    ~MSBBaseBinaryArchiveRead() override = default;
protected:
    //! Function to write a value as N bytes MSB - used to wrap up all the various writes
    int readBytes(U32 & value, U32 noOfBytes) override;
};



} /* namespace tnr */
#endif /* BASEBINARYARCHIVEWRITE_H_ */
