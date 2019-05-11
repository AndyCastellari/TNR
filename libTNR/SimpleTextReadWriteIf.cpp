/*
 * SimpleTextReadWriteIf.cpp
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

#include "SimpleTextReadWriteIf.h"
#include <iomanip>      // std::setfill, std::setw

using namespace std;

namespace tnr {


tnr::SimpleTextWriteIf::SimpleTextWriteIf(std::shared_ptr<std::ostream> _stream): m_level(0), m_stream(_stream)
{
}

std::string tnr::SimpleTextWriteIf::padding()
{
        return std::string(m_level * 2, ' ');
}

int tnr::SimpleTextWriteIf::write(U8 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << std::setw(2) << "0x" << (U16)value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(S8 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << (U16)value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(U16 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << (U16)value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(S16 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << (U16)value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(U24 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(S24 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(U32 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
    return result;
}

int tnr::SimpleTextWriteIf::write(S32 value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
    return result;
}

/**
 * Write a textual description of a string enclosing with double quotes
 * TBC Currently can't cope with a double quote in the string itself
 */
int tnr::SimpleTextWriteIf::write(std::string &value, std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << " : " << '"' << value << '"' << endl;
    return result;

}

void tnr::SimpleTextWriteIf::nextLevel(tnr_format &)
{
    m_level++;
}

void tnr::SimpleTextWriteIf::previousLevel(tnr_format &)
{
    if (m_level > 0)
    {
        m_level--;
    }
    else
    {
//        TODO deal with error
    }
}

int tnr::SimpleTextWriteIf::write(std::string &description, tnr_format &)
{
    int result = 0;
    *m_stream << padding() << description << endl;
    return result;
}

/**
 * Read interface is intended to read from a text file, for example, one written by the write interface.
 * When the caller object calls a read method, the result is a number, so find the next number in the text
 * The way text is written, each value is after the colon on a line. The parser reads a line of text,
 * if there is a colon, it reads a number after the colon
 */
tnr::SimpleTextReadIf::SimpleTextReadIf(std::shared_ptr<std::istream> _stream): m_level(0), m_stream(_stream)
{
}

int tnr::SimpleTextReadIf::read(U8& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (U8)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(S8& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (S8)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(U16& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (U16)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(S16& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (S16)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(U24& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (U24)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(S24& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (S24)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(U32& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (U32)temp;
    return result;
}

int tnr::SimpleTextReadIf::read(S32& value, tnr_format &format)
{
    int result = 0;
    U32 temp = 0;
    result = getNextNumber(temp, format);
    value = (S32)temp;
    return result;
}


/**
 * Reading a string consists of reading until the " : " then
 * skipping the
 */
int tnr::SimpleTextReadIf::read(std::string &value, tnr_format &)
{
    int result = 0;

    std::string temp;
    do
    {
        *m_stream >> temp;
    } while (temp != ":");
    char c = '\0';

    // Skip 0x then read the hex number following
    *m_stream >> c;    // skip opening double quote
    while (c != '"')
    {
        *m_stream >> c;
        // Add character to string
        char tempstr[2] = { 0, 0 };
        tempstr[0] = c;
        value.append(tempstr);
    }

    cout << "Read " << '"' << value << '"' << " from m_stream" << std::endl;

    return result;
}

void tnr::SimpleTextReadIf::nextLevel(tnr_format &)
{
}

void tnr::SimpleTextReadIf::previousLevel(tnr_format &)
{
}

int tnr::SimpleTextReadIf::getNextNumber(U32 & value, tnr_format &)
{
    std::string temp;
    do
    {
        *m_stream >> temp;
    } while (temp != ":");
    char c;

    // Skip 0x then read the hex number following
    *m_stream >> c;
    *m_stream >> c;
    *m_stream >> std::hex >> value;

    cout << "Read " << std::hex << value << " from m_stream" << std::endl;

    return (U32)0;
}

} /* namespace tnr */

