/*
 * TextLogWriteIf.h
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

#ifndef TEXTLOGWRITEIF_H_
#define TEXTLOGWRITEIF_H_

#include "tnr.h"

namespace tnr {

class TextLogWriteIf: public tnr::tnr_write_interface {
public:
    explicit TextLogWriteIf(std::shared_ptr<std::ostream> _stream);
    ~TextLogWriteIf() override;

    int write(U8 value, std::string &description, tnr_format &format ) override;
    int write(S8 value, std::string &description, tnr_format &format ) override;
    int write(U16 value, std::string &description, tnr_format &format) override;
    int write(S16 value, std::string &description, tnr_format &format) override;
    int write(U24 value, std::string &description, tnr_format &format) override;
    int write(S24 value, std::string &description, tnr_format &format) override;
    int write(U32 value, std::string &description, tnr_format &format) override;
    int write(S32 value, std::string &description, tnr_format &format) override;
    int write(std::string &value, std::string &description, tnr_format &format) override;

    // Methods to describe an object when this data may not be part of the output stream
    int write(std::string &description, tnr_format &format) override;

    // Methods to indicate when a new level of nesting is starting/ending
    void nextLevel(tnr_format &format) override;
    void previousLevel(tnr_format &format) override;
protected:
    //! Method to return the number of spaces corresponding to the indent level
    std::string padding();

    unsigned int m_level;
    std::shared_ptr<std::ostream> m_stream;
};

} /* namespace tnr */
#endif /* TEXTLOGWRITEIF_H_ */
