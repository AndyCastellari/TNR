/*
 * FormattedTextReadWriteIf.cpp
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

#include "FormattedTextReadWriteIf.h"
#include <iomanip>      // std::setfill, std::setw

using namespace std;

namespace tnr {


tnr::FormattedTextWriteIf::FormattedTextWriteIf(boost::shared_ptr<std::ostream> _stream): m_level(0), m_stream(_stream), m_PreviousFormats()
{
	// To save checking for an empty stack, we start off with a value of NewLine On
	m_PreviousFormats.push(true);
}

tnr::FormattedTextWriteIf::~FormattedTextWriteIf()
{
}

std::string tnr::FormattedTextWriteIf::padding()
{
		return std::string(m_level * 2, ' ');
}

std::string tnr::FormattedTextWriteIf::NewLineDebug()
{
#if 0
	return std::string("<NoCr>");
#else
	return std::string("");
#endif
}

/**
 * All numbers go through this function
 * It allows formatting control of the output by allowing the item
 * - to be on its own line - padding at start and newline at the end
 * - with our without the description/name of the item
 * (e.g. turn off description of items in an array since they all have same description)
 */
int tnr::FormattedTextWriteIf::writeNumber(U32 value, U8 width, std::string &description, tnr_format &format)
{
	int result = 0;

	if (format.getOutputNewline())
	{
		*m_stream << padding();
	}

	if (format.getOutputDescription())
	{
		*m_stream << description;
	}

	if (format.getOutputNewline() == false)
	{
		// Just finished a section with NewLine off so output a newline
		*m_stream << NewLineDebug();
	}


	// TBC add controlling the formatting of the number
	*m_stream << " : " << "0x" << std::hex << std::setw(width) << std::setfill('0') << value << ' ';

	if (format.getOutputNewline())
	{
		*m_stream << endl;
	}

	return result;
}

/**
 * Write a textual description of a string value enclosed with double quotes
 * TBC Currently can't cope with a double quote in the string itself
 */
int tnr::FormattedTextWriteIf::write(std::string &value, std::string &description, tnr_format &format)
{
	int result = 0;

	if (format.getOutputNewline())
	{
		*m_stream << padding();
	}

	if (format.getOutputDescription())
	{
		*m_stream << description;
	}

	if (format.getOutputNewline() == false)
	{
		// Just finished a section with NewLine off so output a newline
		*m_stream << NewLineDebug();
	}

	// TODO escape double quotes in string
	*m_stream << " : " << '"';
	for (unsigned int i = 0; i < value.length(); i++)
	{
		char c = value[i];
		switch (c)
		{
		case '\\':
		case '"':
			*m_stream << '\\';
			*m_stream << c;
			break;
		default:
			*m_stream << c;
			break;
		}
	}
	*m_stream << '"' << " ";

	if (format.getOutputNewline())
	{
		*m_stream << endl;
	}


	return result;

}

int tnr::FormattedTextWriteIf::write(U8 value, std::string &description, tnr_format &format)
{
	U8 width = 2;	// 8-bit value output in 2 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(S8 value, std::string &description, tnr_format &format)
{
	U8 width = 2;	// 8-bit value output in 2 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(U16 value, std::string &description, tnr_format &format)
{
	U8 width = 4;	// 16-bit value output in 4 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(S16 value, std::string &description, tnr_format &format)
{
	U8 width = 4;	// 16-bit value output in 4 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(U24 value, std::string &description, tnr_format &format)
{
	U8 width = 6;	// 24-bit value output in 6 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(S24 value, std::string &description, tnr_format &format)
{
	U8 width = 6;	// 24-bit value output in 6 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(U32 value, std::string &description, tnr_format &format)
{
	U8 width = 8;	// 32-bit value output in 8 characters
	return writeNumber((U32)value, width, description, format);
}

int tnr::FormattedTextWriteIf::write(S32 value, std::string &description, tnr_format &format)
{
	U8 width = 8;	// 32-bit value output in 8 characters
	return writeNumber((U32)value, width, description, format);
}


// Check if stream needs to add padding for items with NewLine==false
void tnr::FormattedTextWriteIf::CheckForPadding(tnr_format &format)
{
	bool NewLineOn = format.getOutputNewline();

	if (m_PreviousFormats.top() && (NewLineOn == false))
	{
		// NewLine was ON but is now OFF so need to output the padding
		*m_stream << padding();
	}
}

// Check if stream needs to add NewLine for items with NewLine==false
void tnr::FormattedTextWriteIf::CheckForNewLine(tnr_format &format)
{
	bool NewLineOn = format.getOutputNewline();

	if ((m_PreviousFormats.top() == true) && (NewLineOn == false))
	{
		// Just finished a section with NewLine off so output a newline
		*m_stream << endl;
	}
}

void tnr::FormattedTextWriteIf::nextLevel(tnr_format &format)
{
	m_level++;
}

void tnr::FormattedTextWriteIf::previousLevel(tnr_format &format)
{
	if (m_level > 0)
	{
		m_level--;
	}
	else
	{
//		TODO deal with error
	}
}

void tnr::FormattedTextWriteIf::startSection(tnr_format &format)
{
	bool NewLineOn = format.getOutputNewline();
	CheckForPadding(format);
	m_PreviousFormats.push(NewLineOn);
}

void tnr::FormattedTextWriteIf::endSection(tnr_format &format)
{
	m_PreviousFormats.pop();
	CheckForNewLine(format);
}

int tnr::FormattedTextWriteIf::write(std::string &description, tnr_format &format)
{
	int result = 0;
	// If NewLine is off, padding is provided elsewhere
	if (format.getOutputNewline())
	{
		*m_stream << padding();
	}

	// Write description if it is turned on
//	if (format.getOutputDescription())
	{
		*m_stream << description << ' ';
	}

	// Debugging to show if object has correct NewLine attribute
	if (format.getOutputNewline() == false)
	{
		// Just finished a section with NewLine off so output a newline
		*m_stream << NewLineDebug();
	}

	// Write NewLine
	if (format.getOutputNewline())
	{
		*m_stream << endl;
	}

	format.printFormat(description.c_str());
	return result;
}

/**
 * Read interface is intended to read from a text file, for example, one written by the write interface.
 * When the caller object calls a read method, the result is a number, so find the next number in the text
 * The way text is written, each value is after the colon on a line. The parser reads a line of text,
 * if there is a colon, it reads a number after the colon
 */
tnr::FormattedTextReadIf::FormattedTextReadIf(boost::shared_ptr<std::istream> _stream): m_level(0), m_stream(_stream)
{
}

tnr::FormattedTextReadIf::~FormattedTextReadIf()
{
}

int tnr::FormattedTextReadIf::read(U8& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (U8)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(S8& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (S8)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(U16& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (U16)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(S16& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (S16)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(U24& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (U24)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(S24& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (S24)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(U32& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (U32)temp;
	return result;
}

int tnr::FormattedTextReadIf::read(S32& value, tnr_format &format)
{
	int result = 0;
	U32 temp = 0;
	result = getNextNumber(temp, format);
	value = (S32)temp;
	return result;
}

/**
 * Reading a string consists of reading until the " : " then
 * skipping the opening double quote. Normal stream processing skips whitespace
 * so only characters are detected but this turned off to read the interior
 * of the string as it may contain whitespace.
 */
int tnr::FormattedTextReadIf::read(std::string &value, tnr_format &format)
{
	int result = 0;

	std::string temp;
	// Read until : is found
	do
	{
		*m_stream >> temp;
	} while (temp != ":" && m_stream->good());
	char c;

	*m_stream >> c;	// skip opening double quote

	*m_stream >> std::noskipws;			// Stop skipping whitespace

	c = ' ';
	while (m_stream->good() && (c != '"'))
	{
		*m_stream >> c;
		// If this is not the end of the string add the character to value
		if (c != '"')
		{
			// If this is an escaped character, get the following character whatever it is
			if (c == '\\')
			{
				// Get next character and append it to value
				*m_stream >> c;
				value.push_back(c);
				// Set c to a non double quote value
				c = '\0';
			}
			else
			{
				// Add character to string
				value.push_back(c);
			}
		}
	}

	*m_stream >> std::skipws;			// Start skipping whitespace again

//	cout << "Read " << '"' << value << '"' << " from m_stream" << std::endl;

	return result;	// TODO
}

void tnr::FormattedTextReadIf::nextLevel(tnr_format &format)
{
}

void tnr::FormattedTextReadIf::previousLevel(tnr_format &format)
{
}

int tnr::FormattedTextReadIf::getNextNumber(U32 & value, tnr_format &format)
{
	std::string temp;
	do
	{
		*m_stream >> temp;
	} while (temp != ":");
	char c;

	*m_stream >> c;
	*m_stream >> c;
	*m_stream >> std::hex >> value;

//	cout << "Read " << std::hex << value << " from m_stream" << std::endl;

	return (U32)0;
}

} /* namespace tnr */

