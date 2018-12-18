/*
 * SimpleTextReadWriteIf.h
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

#ifndef SIMPLETEXTREADWRITEIF_H_
#define SIMPLETEXTREADWRITEIF_H_

#include "tnr.h"

namespace tnr {

class SimpleTextWriteIf: public tnr::tnr_write_interface {
public:
    explicit SimpleTextWriteIf(std::shared_ptr<std::ostream> _stream);
    ~SimpleTextWriteIf() override;

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
    //! Method to return the number of spaces corresponding to the indent level
    std::string padding();

    unsigned int m_level;
    std::shared_ptr<std::ostream> m_stream;
};

class SimpleTextReadIf: public tnr::tnr_read_interface {
public:
    explicit SimpleTextReadIf(std::shared_ptr<std::istream> _stream);
    ~SimpleTextReadIf() override;

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

protected:
    int getNextNumber(U32 & value, tnr_format &format);

    unsigned int m_level;
    std::shared_ptr<std::istream> m_stream;
};

} /* namespace tnr */
#endif /* SIMPLETEXTREADWRITEIF_H_ */
