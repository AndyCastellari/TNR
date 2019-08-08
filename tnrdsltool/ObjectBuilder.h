/*
 * ObjectBuilder.h
 *
 *      Author: Andy Castellari
 *
 *      COPYRIGHT AND PERMISSION NOTICE
 *
 * Copyright (c) 2015 - 2019, Andy Castellari.
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


#ifndef TNR_OBJECTBUILER_H
#define TNR_OBJECTBUILER_H

#include "tnr.h"
#include <string>
#include <stack>
#include <ObjectMap.h>

class ObjectBuilder
{
public:
    ObjectBuilder(tnr::ObjectMap &objectMap) : m_indent(0), m_objectStack(),
                                                m_objectMap(objectMap),
                                                m_newTypeName(), m_dbg(false) {};
    ~ObjectBuilder() = default;

    //! Return a string that indents by number of spaces times 4
    std::string printIndent() { return std::string((m_indent * 4) + 4, ' '); };
    //! Increase indentation
    void indent() { m_indent++; };
    //! Decrease indentation
    void unindent() { if (m_indent > 0) { m_indent--; } }

public:
    //! Start a new type with an empty object
    virtual void StartNewType(const std::string &typeName);
    //! New type is now complete and can be added to the ObjectMap
    virtual void AddNewType();

    virtual void SetDescriptionOnTopOfStack(const std::string &description);
    virtual void SetPrintDescriptionOnTopOfStack(bool);
    virtual void SetFormatOnTopOfStack(const std::string &description);
    virtual void SetNewlineOnTopOfStack(bool);

    virtual void PushEmptyCompoundObject();
    virtual void PushEmptyExistingType(const std::string &typeName);
    virtual void PushEmptyFixedArray();
    virtual void PushEmptyCountedArray();

    virtual void PopObjectToParentObject();

    virtual void SetFixedArrayLength(uint32_t size);
    virtual void PopElementToFixedArray();

    virtual void PopCounterAndElementToCountedArray();

    //! Put empty variant on stack
    virtual void PushEmptyVariant();
    //! Set value in the selector
    virtual void SetVariantSelectorValue(uint32_t value);
    //! Add the stack[tos] to variant stack[tos-2] with value in selector stack [tos-1]
    virtual void PopElementToVariantWithSelectorValue();
    //! Set selector object in variant
    virtual void SetSelectorTypeInVariant();

    virtual void AddEnumNameToTopOfStack(const std::string &typeName);
    virtual void SetEnumValueToTopOfStack(uint32_t value);

    //! Debug routine to watch stack size
    virtual void PrintStackSize();
protected:
    uint32_t m_indent;
    std::stack<tnr::tnr_baseData_ptr> m_objectStack;
    tnr::ObjectMap &m_objectMap;
    std::string m_newTypeName;
    bool m_dbg;
};


#endif //TNR_OBJECTBUILER_H
