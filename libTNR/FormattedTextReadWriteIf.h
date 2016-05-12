/*
 * FormattedTextReadWriteIf.h
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

#ifndef FORMATTEDTEXTREADWRITEIF_H_
#define FORMATTEDTEXTREADWRITEIF_H_

#include "tnr.h"

namespace tnr {

class FormattedTextWriteIf: public tnr::tnr_write_interface
{
public:
	FormattedTextWriteIf(boost::shared_ptr<std::ostream> _stream);
	virtual ~FormattedTextWriteIf();

	virtual int write(U8 value, std::string &description, tnr_format &format );
	virtual int write(S8 value, std::string &description, tnr_format &format );
	virtual int write(U16 value, std::string &description, tnr_format &format);
	virtual int write(S16 value, std::string &description, tnr_format &format);
	virtual int write(U24 value, std::string &description, tnr_format &format);
	virtual int write(S24 value, std::string &description, tnr_format &format);
	virtual int write(U32 value, std::string &description, tnr_format &format);
	virtual int write(S32 value, std::string &description, tnr_format &format);
	virtual int write(std::string &value, std::string &description, tnr_format &format);

	// Methods to indicate when a new level of nesting is starting/ending - not relevant to plain binary streams
	virtual void nextLevel(tnr_format &format);
	virtual void previousLevel(tnr_format &format);

	// Methods to indicate when a set of data (like the values in an array) are going to be written
	virtual void startSection(tnr_format &format);
	virtual void endSection(tnr_format &format);

	// Methods to describe an object when this data may not be part of the output stream - not relevant to plain binary streams
	virtual int write(std::string &description, tnr_format &format);
protected:
	//! Method to return the number of spaces corresponding to the indent level
	std::string padding();
	//! Method to return a string indicating NewLine
	std::string NewLineDebug();
	//! Check if stream needs to add padding for items with NewLine==false
	void CheckForPadding(tnr_format &format);
	//! Check if stream needs to NewLine for items with NewLine==false
	void CheckForNewLine(tnr_format &format);

	//! Method to write a number in the correct format
	virtual int writeNumber(U32 value, U8 width, std::string &description, tnr_format &format);

	//! Tracks how many levels we are nested to allow indenting text output
	unsigned int m_level;
	//! The output stream where output is written
	boost::shared_ptr<std::ostream> m_stream;
	//! Keeps a stack of whether the higher level had newline enabled or not
	std::stack<bool> m_PreviousFormats;
};

class FormattedTextReadIf: public tnr::tnr_read_interface {
public:
	FormattedTextReadIf(boost::shared_ptr<std::istream> _stream);
	virtual ~FormattedTextReadIf();

	virtual int read(U8 & value, tnr_format &format );
	virtual int read(S8 & value, tnr_format &format );
	virtual int read(U16 & value, tnr_format &format);
	virtual int read(S16 & value, tnr_format &format);
	virtual int read(U24 & value, tnr_format &format);
	virtual int read(S24 & value, tnr_format &format);
	virtual int read(U32 & value, tnr_format &format);
	virtual int read(S32 & value, tnr_format &format);
	virtual int read(std::string &value, tnr_format &format);

	// Methods to indicate when a new level of nesting is starting/ending - not relevant to plain binary streams
	virtual void nextLevel(tnr_format &format);
	virtual void previousLevel(tnr_format &format);

protected:
	//! Search for the next number in text stream
	int getNextNumber(U32 & value, tnr_format &format);

	unsigned int m_level;
	boost::shared_ptr<std::istream> m_stream;
};

} /* namespace tnr */
#endif /* FORMATTEDTEXTREADWRITEIF_H_ */
