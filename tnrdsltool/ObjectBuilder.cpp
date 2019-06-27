/*
 * ObjectBuilder.cpp
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

#include <iostream>
#include "ObjectBuilder.h"

void ObjectBuilder::StartNewType(const std::string& typeName)
{
    std::cout << printIndent() << __FUNCTION__ << " " << typeName << std::endl;
}

void ObjectBuilder::AddNewType()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl << std::endl;
}

void ObjectBuilder::SetDescriptionOnTopOfStack(const std::string& description)
{
    std::cout << printIndent() << __FUNCTION__ << " " << description << std::endl;
}

void ObjectBuilder::SetPrintDescriptionOnTopOfStack(bool showDescription)
{
    std::cout << printIndent() << __FUNCTION__ << " " << (showDescription ? "On" : "Off") << std::endl;
}

void ObjectBuilder::SetFormatOnTopOfStack(const std::string &description)
{
    std::cout << printIndent() << __FUNCTION__ << " " << description << std::endl;
}

void ObjectBuilder::SetNewlineOnTopOfStack(bool newLine)
{
    std::cout << printIndent() << __FUNCTION__ << " " << (newLine ? "On" : "Off") << std::endl;
}


void ObjectBuilder::PushEmptyCompoundObject()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    indent();
    tnr::tnr_baseData_ptr o = std::make_shared<tnr::TNRContainer>("");
    m_objectStack.push(o);
}

void ObjectBuilder::PushEmptyExistingType(const std::string& typeName)
{
    std::cout << printIndent() << __FUNCTION__ << " " << typeName << std::endl;
    tnr::tnr_baseData_ptr retObj;
    if (m_objectMap.FindObject(typeName, retObj))
    {
        m_objectStack.push(retObj);
    }
    else
    {
        std::cout << "type " << typeName << " not found in object map" << std::endl;
    }
}

void ObjectBuilder::PushEmptyFixedArray()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    tnr::tnr_baseData_ptr o = std::make_shared<tnr::TNRFixedArray>();
    m_objectStack.push(o);
}

void ObjectBuilder::PushEmptyCountedArray()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    tnr::tnr_baseData_ptr o = std::make_shared<tnr::TNRCountedArray>();
    m_objectStack.push(o);
}

void ObjectBuilder::PopObjectToParentObject()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr object = m_objectStack.top();
        m_objectStack.pop();
    }
}

void ObjectBuilder::SetFixedArrayLength(uint32_t size)
{
    std::cout << printIndent() << __FUNCTION__ << " size=" << size << std::endl;
}

void ObjectBuilder::PopElementToFixedArray()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr element = m_objectStack.top();
        m_objectStack.pop();
    }
}

void ObjectBuilder::PopCounterAndElementToCountedArray()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr element = m_objectStack.top();
        m_objectStack.pop();
    }
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr counter = m_objectStack.top();
        m_objectStack.pop();
    }
}

