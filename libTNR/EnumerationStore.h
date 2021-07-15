/*
 * tnrtool.cpp
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

#ifndef TNR_ENUMERATIONSTORE_H
#define TNR_ENUMERATIONSTORE_H


#include <string>
#include <memory>
#include <vector>

class EnumerationStore
{
public:
    EnumerationStore();
    virtual ~EnumerationStore();

public:
    //! Adds the identifier to the list of enumerations with the next value
    void AddEnumValue(const std::string &enumName);
    //! Sets last enumeration to enumValue and future enums will increment the value
    void SetEnumValue(uint32_t enumValue);
    //! Returns name corresponding to the value or an empty string
    std::string GetEnumName(uint32_t enumValue);
    //! Debug method
    void PrintEnumStore();
private:
    std::vector<std::pair<uint32_t, std::string>> m_enumeration;

};

typedef std::shared_ptr<EnumerationStore> EnumerationStore_ptr;

#endif //TNR_ENUMERATIONSTORE_H
