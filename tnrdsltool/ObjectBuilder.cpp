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
    std::cout << std::endl;
    std::cout << printIndent() << __FUNCTION__ << " " << typeName << std::endl;
    m_newTypeName = typeName;
    PrintStackSize();
}

void ObjectBuilder::AddNewType()
{
    std::cout << printIndent() << __FUNCTION__ << " " << m_newTypeName << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr object = m_objectStack.top();
        m_objectStack.pop();
        object->setDescription(m_newTypeName);
        m_objectMap.AddObject(object);
    }

    PrintStackSize();
}

void ObjectBuilder::SetDescriptionOnTopOfStack(const std::string& description)
{
    std::cout << printIndent() << __FUNCTION__ << " " << description << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr object = m_objectStack.top();
        object->setDescription(description);
    }
}

void ObjectBuilder::SetPrintDescriptionOnTopOfStack(bool showDescription)
{
    std::cout << printIndent() << __FUNCTION__ << " " << (showDescription ? "On" : "Off") << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr object = m_objectStack.top();
        object->setOutputDescription(showDescription);
    }
}

void ObjectBuilder::SetFormatOnTopOfStack(const std::string &description)
{
    std::cout << printIndent() << __FUNCTION__ << " " << description << std::endl;
}

void ObjectBuilder::SetNewlineOnTopOfStack(bool newLine)
{
    std::cout << printIndent() << __FUNCTION__ << " " << (newLine ? "On" : "Off") << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr object = m_objectStack.top();
        object->setOutputNewline(newLine);
    }
}


void ObjectBuilder::PushEmptyCompoundObject()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    indent();
    tnr::tnr_baseData_ptr o = std::make_shared<tnr::TNRContainer>("");
    m_objectStack.push(o);
    PrintStackSize();
}

void ObjectBuilder::PushEmptyExistingType(const std::string& typeName)
{
    std::cout << printIndent() << __FUNCTION__ << " " << typeName << std::endl;
    tnr::tnr_baseData_ptr retObj;
    if (m_objectMap.FindObject(typeName, retObj))
    {
        m_objectStack.push(retObj);
        PrintStackSize();
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
    PrintStackSize();
}

void ObjectBuilder::PushEmptyCountedArray()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    tnr::tnr_baseData_ptr o = std::make_shared<tnr::TNRCountedArray>();
    m_objectStack.push(o);
    PrintStackSize();
}

void ObjectBuilder::PopObjectToParentObject()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        std::shared_ptr<tnr::TNRContainer> parent;
        std::shared_ptr<tnr::tnr_baseData> object;

        object = m_objectStack.top();
        m_objectStack.pop();
        PrintStackSize();

        parent = std::dynamic_pointer_cast<tnr::TNRContainer>(m_objectStack.top());
        parent->Add(object);
    }
    else
    {
        std::cout << __FUNCTION__ << " m_objectStack is empty" << std::endl;
    }
}

void ObjectBuilder::SetFixedArrayLength(uint32_t size)
{
    std::cout << printIndent() << __FUNCTION__ << " size=" << size << std::endl;
    if (!m_objectStack.empty())
    {
        std::shared_ptr<tnr::TNRFixedArray> fixedArray;
        fixedArray = std::dynamic_pointer_cast<tnr::TNRFixedArray>(m_objectStack.top());
        fixedArray->SetNumberOfElements(size);
    }
    else
    {
        std::cout << __FUNCTION__ << " m_objectStack is empty" << std::endl;
    }
}

void ObjectBuilder::PopElementToFixedArray()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        tnr::tnr_baseData_ptr element = m_objectStack.top();
        m_objectStack.pop();

        if (!m_objectStack.empty())
        {
            std::shared_ptr<tnr::TNRFixedArray> fixedArray;
            fixedArray = std::dynamic_pointer_cast<tnr::TNRFixedArray>(m_objectStack.top());
            fixedArray->SetRecordType(element);
        }
    }
}

void ObjectBuilder::PopCounterAndElementToCountedArray()
{
    tnr::tnr_baseData_ptr element;
    tnr::tnr_baseData_ptr counter;

    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        element = m_objectStack.top();
        m_objectStack.pop();
    }
    if (!m_objectStack.empty())
    {
        counter = m_objectStack.top();
        m_objectStack.pop();
    }
    if (!m_objectStack.empty())
    {
        std::shared_ptr<tnr::TNRCountedArray> countedArray;
        countedArray = std::dynamic_pointer_cast<tnr::TNRCountedArray>(m_objectStack.top());
        countedArray->SetNumberOfElements(counter);
        countedArray->SetRecordType(element);
    }
}

void ObjectBuilder::PrintStackSize()
{
//    std::cout << "Stack is " << m_objectStack.size() << " deep" << std::endl;
}

void ObjectBuilder::PushEmptyVariant()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    tnr::tnr_baseData_ptr o = std::make_shared<tnr::TNR_Variant>();
    m_objectStack.push(o);
    PrintStackSize();

}

void ObjectBuilder::SetVariantSelectorValue(uint32_t value)
{
    std::cout << printIndent() << __FUNCTION__ << " " << "value:" << value << std::endl;
    tnr::tnr_baseData_ptr selector;
    selector = m_objectStack.top();
    selector->setValue(value);

    PrintStackSize();
}

void ObjectBuilder::PopElementToVariantWithSelectorValue()
{
    tnr::tnr_baseData_ptr element;
    tnr::tnr_baseData_ptr selector;

    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    if (!m_objectStack.empty())
    {
        element = m_objectStack.top();
        m_objectStack.pop();
    }
    if (!m_objectStack.empty())
    {
        selector = m_objectStack.top();
        m_objectStack.pop();
    }
    if (!m_objectStack.empty())
    {
        std::shared_ptr<tnr::TNR_Variant> variant;
        variant = std::dynamic_pointer_cast<tnr::TNR_Variant>(m_objectStack.top());
        variant->addObject(selector->getCount(), element);
        selector->setValue(selector->getCount() + 1);
        m_objectStack.push(selector);
    }
    PrintStackSize();
}

void ObjectBuilder::SetSelectorTypeInVariant()
{
    std::cout << printIndent() << __FUNCTION__ << " " << std::endl;
    tnr::tnr_baseData_ptr selector;
    if (!m_objectStack.empty())
    {
        selector = m_objectStack.top();
        m_objectStack.pop();
    }
    if (!m_objectStack.empty())
    {
        std::shared_ptr<tnr::TNR_Variant> variant;
        variant = std::dynamic_pointer_cast<tnr::TNR_Variant>(m_objectStack.top());
        variant->setSelector(selector);
    }
}

void ObjectBuilder::AddEnumNameToTopOfStack(const std::string& typeName)
{
    std::cout << printIndent() << __FUNCTION__ << " " << typeName << std::endl;
}

void ObjectBuilder::SetEnumValueToTopOfStack(uint32_t value)
{
    std::cout << printIndent() << __FUNCTION__ << " " << "value:" << value << std::endl;
}

