/*
 * MemoryStreamWriteIf.cpp
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

#include "StreamReadWriteIf.h"

namespace tnr {

StreamWriteIf::StreamWriteIf(std::shared_ptr<std::ostream> _stream) : LSBBaseBinaryArchiveWrite(), m_stream(_stream)
{
}


/**
 * This method implements writing a byte to some storage medium
 */
int StreamWriteIf::writeOneByte(U8 value)
{
    char temp = (char)value;
    m_stream->write(&temp, 1);
    return m_stream->bad() ? 1 : 0;
}

StreamReadIf::StreamReadIf(std::shared_ptr<std::istream> _stream) : LSBBaseBinaryArchiveRead(), m_stream(_stream)
{
}


/**
 * This method implements reading a byte from some storage medium.
 */
int StreamReadIf::readOneByte(U8 & value)
{
    char temp = 0;
    m_stream->read(&temp, 1);    // TODO deal with errors
    value = (U8)temp;
    return m_stream->bad() ? 1 : 0;
}

} /* namespace tnr */
