/*
 * StreamReadWriteIf.h
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

#ifndef STREAMREADWRITEIF_H_
#define STREAMREADWRITEIF_H_

#include "tnr.h"
#include "BaseBinaryArchiveReadWrite.h"
#include <sstream>

#include <boost/shared_ptr.hpp>

namespace tnr {

class StreamWriteIf: public tnr::LSBBaseBinaryArchiveWrite
{
public:
	StreamWriteIf(boost::shared_ptr<std::ostream> _stream);
	virtual ~StreamWriteIf();

protected:
	//! Write one byte to the actual storage being used
	int writeOneByte(U8 value);

protected:
//	U32 m_level;
	boost::shared_ptr<std::ostream> m_stream;
};

class StreamReadIf: public tnr::LSBBaseBinaryArchiveRead
{
public:
	StreamReadIf(boost::shared_ptr<std::istream> _stream);
	virtual ~StreamReadIf();

//	bool operator==(std::string &rhs);

protected:
	//! Write one byte to the actual storage being used
	int readOneByte(U8 & value);

protected:
//	U32 m_level;
	boost::shared_ptr<std::istream> m_stream;
};

} /* namespace tnr */
#endif /* MEMORYSTREAMWRITEIF_H_ */
