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
#include <stdio.h>
namespace tnr
{
void tnr_format::printFormat(const char * name)
{
	printf("Object (%s) - Description(%s), NewLine(%s)\n",  name, this->m_outputDescription ? "on" : "off", this->m_outputNewline ? "on" : "off");
}

//======================================================
tnr_baseData::tnr_baseData(const std::string &description) : m_description(description)
{
}

tnr_baseData::tnr_baseData(const char * description) : m_description(description)
{
}

tnr_baseData::~tnr_baseData()
{
	// Nothing to do - default destructors OK
}

tnr::TNRContainer::TNRContainer(const std::string &description) : tnr_baseData(description), m_values()
{
}

tnr::TNRContainer::TNRContainer(const char * description) : tnr_baseData(description), m_values()
{
}

tnr::TNRContainer::~TNRContainer()
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

	BOOST_FOREACH(tnr_baseData_ptr value, m_values)
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

	BOOST_FOREACH(tnr_baseData_ptr value, m_values)
	{
		result = value->read(read_if);
	}

	return result;
}


tnr_baseData_ptr TNRContainer::clone()
{
	boost::shared_ptr< TNRContainer > c(new TNRContainer(m_description));
	c->m_format = this->m_format;

	// New object has same count, record type and array of objects as original but array _may_ not have same values
	for (U32 i = 0; i < m_values.size(); i++)
	{
		if (m_values[i] != NULL)
		{
			tnr_baseData_ptr newRecord = m_values[i]->clone();
			c->Add(newRecord);
		}
	}

	return c;
}

//===============================================================================================

tnr::TNRFixedArray::TNRFixedArray(	const std::string &description, U32 count, tnr_baseData_ptr recordType) :
														tnr_baseData(description), m_count(count), m_values()
{
	m_recordType = recordType->clone();
	// Fill array with correct number of items (we don't know what type these items are)
	for (unsigned int i = 0; i < m_count; i++)
	{
		tnr_baseData_ptr newRecord = m_recordType->clone();
		m_values.push_back(newRecord);
	}
}

tnr::TNRFixedArray::TNRFixedArray(	const char * description, U32 count, tnr_baseData_ptr recordType) :
														tnr_baseData(description), m_count(count), m_values()
{
	m_recordType = recordType->clone();
	// Fill array with correct number of items (we don't know what type these items are)
	for (unsigned int i = 0; i < m_count; i++)
	{
		tnr_baseData_ptr newRecord = m_recordType->clone();
		m_values.push_back(newRecord);
	}
}

tnr::TNRFixedArray::~TNRFixedArray()
{
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
	BOOST_FOREACH(tnr_baseData_ptr value, m_values)
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
	BOOST_FOREACH(tnr_baseData_ptr value, m_values)
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
	boost::shared_ptr< TNRFixedArray > c(new TNRFixedArray(m_description, m_count, m_recordType));
	c->m_format = this->m_format;

	// New object has same count, record type and array of objects as original but array _may_ not have same values
	for (U32 i = 0; i < m_values.size(); i++)
	{
		c->m_values[i] = m_values[i]->clone();
	}

	return c;
}


//===============================================================================================

tnr::TNRCountedArray::TNRCountedArray(	const std::string &description, tnr_baseData_ptr countType, tnr_baseData_ptr recordType) :
																						tnr_baseData(description), m_values()
{
	m_count = countType->clone();
	m_recordType = recordType->clone();

	// Fill array with correct number of items (we don't know what type these items are)
	for (unsigned int i = 0; i < m_count->getCount(); i++)
	{
		tnr_baseData_ptr newRecord = m_recordType->clone();
		m_values.push_back(newRecord);
	}
}

tnr::TNRCountedArray::TNRCountedArray(	const char * description, tnr_baseData_ptr countType, tnr_baseData_ptr recordType) :
																						tnr_baseData(description), m_values()
{
	m_count = countType->clone();
	m_recordType = recordType->clone();

	// Fill array with correct number of items (we don't know what type these items are)
	for (unsigned int i = 0; i < m_count->getCount(); i++)
	{
		tnr_baseData_ptr newRecord = m_recordType->clone();
		m_values.push_back(newRecord);
	}
}

tnr::TNRCountedArray::~TNRCountedArray()
{
}

tnr_baseData_ptr & tnr::TNRCountedArray::operator [](U32 index)
{
	return m_values[index];
}

int tnr::TNRCountedArray::write(tnr_write_interface& write_if)
{
	int result = 0;

	write_if.startSection(m_format);

	result = write_if.write(m_description, m_format);
	write_if.nextLevel(m_format);

	result = m_count->write(write_if);

	BOOST_FOREACH(tnr_baseData_ptr value, m_values)
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
	boost::shared_ptr< TNRCountedArray > c(new TNRCountedArray(m_description, m_count, m_recordType));
	c->m_format = this->m_format;

	// New object has same count, record type and array of objects as original but array _may_ not have same values
	for (U32 i = 0; i < m_values.size(); i++)
	{
		c->m_values[i] = m_values[i]->clone();
	}

	return c;
}

//===============================================================================================
tnr::TNR_C_String::TNR_C_String(const std::string &value, const std::string &description) : tnr_baseData(description), m_Cstring(value)
{

}

tnr::TNR_C_String::~TNR_C_String()
{

}

// Define methods that must be implemented by the child classes
int tnr::TNR_C_String::write(tnr_write_interface &write_if)
{
	int result = 0;

	write_if.startSection(m_format);
//	write_if.nextLevel(m_format);

	// Write the string as text
	result = write_if.write(m_Cstring, m_description, m_format);

//	write_if.previousLevel(m_format);
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
	boost::shared_ptr< TNR_C_String > c(new TNR_C_String(m_Cstring, m_description));
	c->m_format = this->m_format;

//	c->m_Cstring = this->m_Cstring;

	return c;
}

//===============================================================================================

}// End of namespace tnr
