/*
 * TextLogWriteIf.cpp
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

#include "TextLogWriteIf.h"

using namespace std;

namespace tnr {

TextLogWriteIf::TextLogWriteIf(std::shared_ptr<std::ostream> _stream): m_level(0), m_stream(_stream)
{
	// TODO Auto-generated constructor stub

}

TextLogWriteIf::~TextLogWriteIf()
{
	// TODO Auto-generated destructor stub
}

int TextLogWriteIf::write(U8 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << (U16)value << endl;
	return 0;
}

int TextLogWriteIf::write(S8 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << (S16)value << endl;
	return 0;
}

int TextLogWriteIf::write(U16 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
	return 0;
}

int TextLogWriteIf::write(S16 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
	return 0;
}

int TextLogWriteIf::write(U24 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
	return 0;
}

int TextLogWriteIf::write(S24 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
	return 0;
}

int TextLogWriteIf::write(U32 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
	return 0;
}

int TextLogWriteIf::write(S32 value, std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << " : " << std::hex << "0x" << value << endl;
	return 0;
}

/**
 * Write a textual description of a string enclosing with double quotes
 * TBC Currently can't cope with a double quote in the string itself
 */
int tnr::TextLogWriteIf::write(std::string &value, std::string &description, tnr_format &format)
{
	int result = 0;
	*m_stream << padding() << description << " : " << '"' << value << '"' << endl;
	return result;

}

int TextLogWriteIf::write(std::string &description, tnr_format &format)
{
	*m_stream << padding() << description << endl;
	return 0;
}

/**
 * nextLevel creates a new brace level at the current indent and then increases the indent level
 */
void TextLogWriteIf::nextLevel(tnr_format &format)
{
	*m_stream << padding() << "{" << endl;
	m_level++;
}

/**
 * previousLevel ends a nested section, so the brace should be at the same level as the matching
 * nextLevel - hence decrease level then write brace.
 */
void TextLogWriteIf::previousLevel(tnr_format &format)
{
	if (m_level > 0)
	{
		m_level--;
	}
	else
	{
//		TODO deal with error
	}
	*m_stream << padding() << "}" << endl;
}

std::string TextLogWriteIf::padding()
{
	return std::string(m_level * 2, ' ');
}

} /* namespace tnr */
