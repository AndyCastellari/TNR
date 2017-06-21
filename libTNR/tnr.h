/*
 * tnr.h
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

#ifndef TNR_H_
#define TNR_H_

#include "tnr_portability.h"
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <typeinfo>
#include <stdio.h>


namespace tnr
{

/**
 * Define a class to hold formatting information
 * Initially this will only extend to whether to print the
 * description of a variable and whether to output a newline
 *
 * Not virtualised at present
 */

class tnr_format
{
	public:
		tnr_format() : m_outputNewline(true), m_outputDescription(true) {};
		tnr_format(const tnr_format &c) : m_outputNewline(c.m_outputNewline), m_outputDescription(c.m_outputDescription) {};
		~tnr_format() {};

		// Setters and getters for format booleans
		// There could more later on and not necessarily booleans, for example, make the " : " able to specified
		void setOutputNewline(bool onOff) { m_outputNewline = onOff; };
		bool getOutputNewline() { return m_outputNewline; };
		void setOutputDescription( bool onOff) { m_outputDescription = onOff; };
		bool getOutputDescription() { return m_outputDescription; };
		// For debugging, write the contents of the format
		void printFormat(const char * name);
	protected:
		bool m_outputNewline;
		bool m_outputDescription;
};

/**
 * Define the read and write interfaces that allow data objects
 * to export themselves or import themselves
 */

class tnr_write_interface
{
protected:
	tnr_write_interface() { };
	virtual ~tnr_write_interface() { };
public:
	virtual int write(U8 value, std::string &description, tnr_format &format) = 0;
	virtual int write(S8 value, std::string &description, tnr_format &format) = 0;
	virtual int write(U16 value, std::string &description, tnr_format &format) = 0;
	virtual int write(S16 value, std::string &description, tnr_format &format) = 0;
	virtual int write(U24 value, std::string &description, tnr_format &format) = 0;
	virtual int write(S24 value, std::string &description, tnr_format &format) = 0;
	virtual int write(U32 value, std::string &description, tnr_format &format) = 0;
	virtual int write(S32 value, std::string &description, tnr_format &format) = 0;
	virtual int write(std::string &value, std::string &description, tnr_format &format) = 0;

	// Method to describe the object itself - this may not actually be written (e.g. not written for binary stream but written for textual stream)
	virtual int write(std::string &description, tnr_format &format) = 0;

	// Methods to indicate when a new level of nesting is starting/ending
	virtual void nextLevel(tnr_format &format) = 0;
	virtual void previousLevel(tnr_format &format) = 0;

	// Methods to indicate when a set of data (like the values in an array) are going to be written
	virtual void startSection(tnr_format &) {};
	virtual void endSection(tnr_format &) {};
};

class tnr_read_interface
{
protected:
	tnr_read_interface() { };
	virtual ~tnr_read_interface() { };
public:
	virtual int read(U8 &value, tnr_format &format) = 0;
	virtual int read(S8 &value, tnr_format &format) = 0;
	virtual int read(U16 &value, tnr_format &format) = 0;
	virtual int read(S16 &value, tnr_format &format) = 0;
	virtual int read(U24 &value, tnr_format &format) = 0;
	virtual int read(S24 &value, tnr_format &format) = 0;
	virtual int read(U32 &value, tnr_format &format) = 0;
	virtual int read(S32 &value, tnr_format &format) = 0;
	virtual int read(std::string &value, tnr_format &format) = 0;

	// Methods to indicate when a new level of nesting is starting/ending
	virtual void nextLevel(tnr_format &format) = 0;
	virtual void previousLevel(tnr_format &format) = 0;
};

/**
 * Define the _basic_ data class interface, basically a TNR object
 * that supports reading and writing the tnr_read/write_interface
 */

class tnr_baseData;
typedef boost::shared_ptr<tnr_baseData> tnr_baseData_ptr;

//! Common base class - covers common data for all classes
class tnr_baseData
{
public:
	//! Construct from a string
	tnr_baseData(const std::string &description);
	//! Construct from a null terminated string (for convenience)
	tnr_baseData(const char * description);
	//! Destructor is virtual to force all the derived classes to be virtual
	virtual ~tnr_baseData();

	// Define methods that must be implemented by the child classes
	virtual int write(tnr_write_interface &write_if) = 0;
	virtual int read(tnr_read_interface &read_if) = 0;
	//! The object provides a copy of itself: the same class and contents
	virtual tnr_baseData_ptr clone() = 0;
	//! This method is used when using the class as a counter of a counted array
	virtual U32 getCount() { return 0; };		// TBC - this could be pure virtual
	//! Return name of object
	virtual void setDescription(std::string &s) { m_description = s; };
	//! Return name of object
	virtual std::string & getDescription() { return m_description; };
	//! This method is used for containers/arrays to find out how many items are in them - POD returns 1
	virtual U32 getItemCount() { return 1; };

	// Setters and getters for format booleans
	// There could more later on and not necessarily booleans, for example, make the " : " able to specified
	void setOutputNewline(bool onOff) { m_format.setOutputNewline(onOff); };
	bool getOutputNewline() { return m_format.getOutputNewline(); };
	void setOutputDescription(bool onOff) { m_format.setOutputDescription(onOff); };
	bool getOutputDescription() { return m_format.getOutputDescription(); };
	//! Apply an existing format to the object
	void setFormat(tnr_format output_format) { m_format = output_format; };

protected:
	std::string m_description;
	tnr_format m_format;
};

/**
 * Implementing the different classes to manage U8,U16,U32, etc. is repetitive and cumbersome
 * so use a template to define the construction and read/write,
 * then typedef various implementations
 */
template <class T> class POD : public tnr_baseData
{
public:
	//! Create an object to hold a simple POD type with a string description
	POD(T value, const std::string &description) : tnr_baseData(description), m_value(value)
	{
	}
	//! Create an object to hold a simple POD type with a null terminated string description
	POD(T value, const char * description) : tnr_baseData(description), m_value(value)
	{
	}
	//!  Nothing dynamic so destructor doesn't need to do anything
	virtual ~POD()
	{
	}

	//! Output the POD type to the write interface
	virtual int write(tnr_write_interface &write_if)
	{
		return write_if.write(m_value, m_description, m_format);
	}

	//! Read the POD type from the read interface
	virtual int read(tnr_read_interface &read_if)
	{
		int result = read_if.read(m_value, m_format);
		return result;
	}

	//! Create a deep copy of the variable
	virtual tnr_baseData_ptr clone()
	{
		boost::shared_ptr< POD<T> > c(new POD<T>(m_value, m_description));
		// In case the default format was changed, copy that over as well
		c->m_format = this->m_format;
		return c;
	}

	//! This method is used when using the class as a counter of a counted array
	virtual U32 getCount() { return (U32)m_value; };

	virtual T getValue() { return m_value; };
//	virtual std::string & getDescription() { return m_description; };

	//! Can't remember why I wrote this one
	operator T() { return getValue(); };

protected:
	T m_value;
};

// Make a set of predefined types for the basic integer types
typedef POD<U8> POD_U8;
typedef POD<U16> POD_U16;
typedef POD<U24> POD_U24;
typedef POD<U32> POD_U32;
typedef POD<S8> POD_S8;
typedef POD<S16> POD_S16;
typedef POD<S24> POD_S24;
typedef POD<S32> POD_S32;

typedef boost::shared_ptr<POD_U8>  POD_U8_ptr;
typedef boost::shared_ptr<POD_U16> POD_U16_ptr;
typedef boost::shared_ptr<POD_U24> POD_U24_ptr;
typedef boost::shared_ptr<POD_U32> POD_U32_ptr;
typedef boost::shared_ptr<POD_S8>  POD_S8_ptr;
typedef boost::shared_ptr<POD_S16> POD_S16_ptr;
typedef boost::shared_ptr<POD_S24> POD_S24_ptr;
typedef boost::shared_ptr<POD_S32> POD_S32_ptr;

//typedef POD<CHAR> POD_CHAR;
//typedef boost::shared_ptr<POD_CHAR>  POD_CHAR_ptr;

// TODO Define composite data class containers

/**
 * Several composites of POD are immediately necessary
 * 1.	Standard fixed array, defined by fixed count N of items and array of these items
 *      Reading/writing the array will just read/write N individual items
 * 2.	Counted array of items, defined by a count at the beginning followed by count x items
 *      Reading/writing a counted array will read/write the count N, then read/write N items
 * 3.	Delimited array, which holds a variable number of items but ends with a predetermined end value
 *      For example, a c-type string which is NULL terminated would be a delimited array of U8 with
 *      terminating character 0x00
 */

/**
 * Define a basic recursive container that can contain heterogeneous POD data, composites of POD data
 * and other TNRContainers
 */
class TNRContainer : public tnr_baseData
{
public:
	TNRContainer(const std::string &description);
	TNRContainer(const char * description);
	virtual ~TNRContainer();

	//! Add a new field to the container
	void Add(tnr_baseData_ptr value);

	// Methods to describe an object when this data may not be part of the output stream
//	virtual int write(std::string description);
	// Define methods that must be implemented by the child classes
	virtual int write(tnr_write_interface &write_if);
	virtual int read(tnr_read_interface &read_if);
	//! The object provides a copy of itself: the same class and contents
	virtual tnr_baseData_ptr clone();
	//! Return number of items in the array
	virtual U32 getItemCount() { return m_values.size(); };

protected:
	std::vector<tnr_baseData_ptr> m_values;
};

typedef boost::shared_ptr<TNRContainer> TNRContainer_ptr;

class TNRFixedArray : public tnr_baseData
{
public:
	TNRFixedArray(const std::string &description, U32 count, tnr_baseData_ptr recordType);
	TNRFixedArray(const char * description, U32 count, tnr_baseData_ptr recordType);
	virtual ~TNRFixedArray();

	//! Return a reference to the pointer inside the object so we can read or write it or modify the object it points to
	tnr_baseData_ptr & operator[](U32 index);

	// Define methods that must be implemented by the child classes
	virtual int write(tnr_write_interface &write_if);
	virtual int read(tnr_read_interface &read_if);
	virtual tnr_baseData_ptr clone();
	//! Return number of items in the array
	virtual U32 getItemCount() { U32 result = m_values.size(); return result; };
protected:
	//! Number of items in the fixed array - not serialised (needed?)
	U32 m_count;
	//! Item that will be put into the array - its actual type is not known
	tnr_baseData_ptr m_recordType;
	//! Array containing the array members
	std::vector<tnr_baseData_ptr> m_values;
};

typedef boost::shared_ptr<TNRFixedArray> TNRFixedArray_ptr;

class TNRCountedArray : public tnr_baseData
{
public:
	TNRCountedArray(const std::string &description, tnr_baseData_ptr countType, tnr_baseData_ptr recordType);
	TNRCountedArray(const char * description, tnr_baseData_ptr countType, tnr_baseData_ptr recordType);
	virtual ~TNRCountedArray();

	//! Return a reference to the pointer inside the object so we can read or write it or modify the object it points to
	tnr_baseData_ptr & operator[](U32 index);

	// Define methods that must be implemented by the child classes
	virtual int write(tnr_write_interface &write_if);
	virtual int read(tnr_read_interface &read_if);
	virtual tnr_baseData_ptr clone();
	//! Return number of items in the array
	virtual U32 getItemCount() { U32 result = m_values.size(); return result; };
protected:
	//! Number of items in the fixed array - not serialised
	tnr_baseData_ptr m_count;
	//! Item that will be put into the array - its actual type is not known
	tnr_baseData_ptr m_recordType;
	//! Array containing the array members
	std::vector<tnr_baseData_ptr> m_values;
};

typedef boost::shared_ptr<TNRCountedArray> TNRCountedArray_ptr;

// Delimited c-style string
class TNR_C_String : public tnr_baseData
{
public:
	TNR_C_String(const std::string &value, const std::string &description);
//	TNR_C_String(const std::string &description, const char * description);
	virtual ~TNR_C_String();

	// Define methods that must be implemented by the child classes
	virtual int write(tnr_write_interface &write_if);
	virtual int read(tnr_read_interface &read_if);
	virtual tnr_baseData_ptr clone();
	//! Return number of items in the array
	virtual U32 getItemCount() { U32 result = m_Cstring.size(); return result; };
	std::string getValue() { return m_Cstring; };
protected:
	//! Store the string value
	std::string m_Cstring;
};

typedef boost::shared_ptr<TNR_C_String> TNR_C_String_ptr;

}	// end of namespace

#endif /* TNR_H_ */
