/*
 * tnr.cpp
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

namespace tnr
{
void tnr_format::printFormat(const char * name)
{
    printf("Object (%s) - Description(%s), NewLine(%s)\n",  name, this->m_outputDescription ? "on" : "off", this->m_outputNewline ? "on" : "off");
}

tnr_format::tnr_format(const tnr_format &)
{
}

    //======================================================
tnr_baseData::tnr_baseData(const std::string description) : m_description(description)
{
}

tnr::TNRContainer::TNRContainer(const std::string description) : tnr_baseData(description), m_values()
{
}

/**
 * This method adds new values (which are not necessarily the same type)
 * to the vector to make a collection of types
 */
void tnr::TNRContainer::Add(tnr_baseData_ptr value)
{
    m_values.push_back(value);
}

int tnr::TNRContainer::write(tnr_write_interface& write_if)
{
    int result = 0;

    write_if.startSection(m_format);

    write_if.write(m_description, m_format);
    write_if.nextLevel(m_format);

    for (const auto &value: m_values)
    {
        result = value->write(write_if);
    }

    write_if.previousLevel(m_format);

    write_if.endSection(m_format);

    return result;
}

int tnr::TNRContainer::read(tnr_read_interface& read_if)
{
    int result = 0;

    for (const auto &value: m_values)
    {
        result = value->read(read_if);
    }

    return result;
}


tnr_baseData_ptr TNRContainer::clone()
{
    std::shared_ptr< TNRContainer > c(new TNRContainer(m_description));
    c->m_format = this->m_format;

    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (auto &m_value : m_values) {
        if (m_value != nullptr)
        {
            tnr_baseData_ptr newRecord = m_value->clone();
            c->Add(newRecord);
        }
    }

    return c;
}

U32 TNRContainer::getItemCount() { return m_values.size(); }

//===============================================================================================

TNRFixedArray::TNRFixedArray():
        tnr_baseData(""), m_count(0), m_recordType(), m_values()
{
    m_recordType = std::make_shared<POD_U8>(0, "");
    createArray();
}

void TNRFixedArray::createArray()
{
    m_values.clear();

    // Fill array with correct number of items (we don't know what type these items are)
    for (unsigned int i = 0; i < m_count; i++)
    {
        tnr_baseData_ptr newRecord = m_recordType->clone();
        m_values.push_back(newRecord);
    }
}

tnr::TNRFixedArray::TNRFixedArray(    const std::string description, U32 count, tnr_baseData_ptr recordType) :
                                                    tnr_baseData(description),
                                                    m_count(count),
                                                    m_recordType(recordType),
                                                    m_values()
{
    createArray();
}

tnr_baseData_ptr & tnr::TNRFixedArray::operator [](U32 index)
{
    return m_values[index];
}

/**
 * Call write on each of the objects in m_values
 */
int tnr::TNRFixedArray::write(tnr_write_interface& write_if)
{
    int result = 0;
    write_if.startSection(m_format);
    write_if.write(m_description, m_format);
    write_if.nextLevel(m_format);
    for (const auto &value: m_values)
    {
        result = value->write(write_if);
    }
    write_if.previousLevel(m_format);
    write_if.endSection(m_format);
    return result;
}

/**
 * Call read on each of the objects in m_values
 */
int tnr::TNRFixedArray::read(tnr_read_interface& read_if)
{
    int result = 0;
    read_if.nextLevel(m_format);
    for (const tnr_baseData_ptr &value: m_values)
    {
        result = value->read(read_if);
    }
    read_if.previousLevel(m_format);
    return result;
}

/**
 * Create a new empty FixedArray, then copy array values across from source to destination.
 * Can't use BOOST_FOREACH because we need to iterate both arrays
 */
tnr_baseData_ptr TNRFixedArray::clone()
{
    std::shared_ptr< TNRFixedArray > c(new TNRFixedArray(m_description, m_count, m_recordType));
    c->m_format = this->m_format;

    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (U32 i = 0; i < m_values.size(); i++)
    {
        c->m_values[i] = m_values[i]->clone();
    }

    return c;
}

U32 TNRFixedArray::getItemCount() { U32 result = m_values.size(); return result; }

void TNRFixedArray::SetNumberOfElements(uint32_t count)
{
    m_count = count;
    createArray();
}

void TNRFixedArray::SetRecordType(tnr_baseData_ptr recordType)
{
    m_recordType = recordType->clone();
    createArray();
}

//===============================================================================================

TNRCountedArray::TNRCountedArray() : tnr_baseData(""), m_count(), m_recordType(), m_values()
{
    m_count = std::make_shared<POD_U8>(0, "");
    m_recordType = std::make_shared<POD_U8>(0, "");
    createArray();
}

void TNRCountedArray::createArray()
{
    m_values.clear();

    // Fill array with correct number of items (we don't know what type these items are)
    for (unsigned int i = 0; i < m_count->getCount(); i++)
    {
        tnr_baseData_ptr newRecord = m_recordType->clone();
        m_values.push_back(newRecord);
    }
}


tnr::TNRCountedArray::TNRCountedArray(    const std::string description, tnr_baseData_ptr countType, tnr_baseData_ptr recordType) :
                                                                                    tnr_baseData(description), m_values()
{
    m_count = countType->clone();
    m_recordType = recordType->clone();

    createArray();
//     Fill array with correct number of items (we don't know what type these items are)
//    for (unsigned int i = 0; i < m_count->getCount(); i++)
//    {
//        tnr_baseData_ptr newRecord = m_recordType->clone();
//        m_values.push_back(newRecord);
//    }
}

    tnr_baseData_ptr & tnr::TNRCountedArray::operator [](U32 index)
{
    return m_values[index];
}

int tnr::TNRCountedArray::write(tnr_write_interface& write_if)
{
    int result = 0;

    write_if.startSection(m_format);

    write_if.write(m_description, m_format);
    write_if.nextLevel(m_format);

    m_count->write(write_if);

    for (const tnr_baseData_ptr &value: m_values)
    {
        result = value->write(write_if);
    }

    write_if.previousLevel(m_format);
    write_if.endSection(m_format);

    return result;
}

int tnr::TNRCountedArray::read(tnr_read_interface& read_if)
{
    int result = 0;

    read_if.nextLevel(m_format);

    // Read the count variable
    m_count->read(read_if);

    // Reset the variable array and then populate it with new items read from the stream
    m_values.clear();

    for (U32 i = 0; i < m_count->getCount(); i++)
    {
        tnr_baseData_ptr newRecord = m_recordType->clone();
        newRecord->read(read_if);
        m_values.push_back(newRecord);
    }

    read_if.previousLevel(m_format);
    return result;
}

tnr_baseData_ptr TNRCountedArray::clone()
{
    std::shared_ptr< TNRCountedArray > c(new TNRCountedArray(m_description, m_count, m_recordType));
    c->m_format = this->m_format;

    // New object has same count, record type and array of objects as original but array _may_ not have same values
    for (U32 i = 0; i < m_values.size(); i++)
    {
        c->m_values[i] = m_values[i]->clone();
    }

    return c;
}

U32 TNRCountedArray::getItemCount() { auto result = (U32)m_values.size(); return result; }

void TNRCountedArray::SetNumberOfElements(tnr_baseData_ptr countType)
{
    m_count = countType->clone();
    createArray();
}

void TNRCountedArray::SetRecordType(tnr_baseData_ptr recordType)
{
    m_recordType = recordType->clone();
    createArray();
}

//===============================================================================================
tnr::TNR_C_String::TNR_C_String(const std::string &value, const std::string description) : tnr_baseData(description),
                                                                                            m_Cstring(value)
{
}

    // Define methods that must be implemented by the child classes
int tnr::TNR_C_String::write(tnr_write_interface &write_if)
{
    int result = 0;

    write_if.startSection(m_format);

    // Write the string as text
    result = write_if.write(m_Cstring, m_description, m_format);

    write_if.endSection(m_format);

    return result;
}

int tnr::TNR_C_String::read(tnr_read_interface &read_if)
{
    int result = 0;

    read_if.nextLevel(m_format);

    // Reset the variable array and then populate it with new items read from the stream
    m_Cstring.clear();

    // Read the string
    result = read_if.read(m_Cstring, m_format);

    read_if.previousLevel(m_format);
    return result;
}

tnr_baseData_ptr tnr::TNR_C_String::clone()
{
    std::shared_ptr< TNR_C_String > c(new TNR_C_String(m_Cstring, m_description));
    c->m_format = this->m_format;
    return c;
}

U32 TNR_C_String::getItemCount() { U32 result = m_Cstring.size(); return result; }

//===============================================================================================

}// End of namespace tnr
