// (C) 2019 Transport for London
// All rights reserved.  This information is confidential.  You may not
// reproduce, adapt or disclose this information or any part of the
// information, for any purpose without TfL’s written permission.  TfL
// makes no warranties or representations, and expressly disclaims all
// liability concerning this information

#include <iostream>
#include "EnumerationStore.h"

EnumerationStore::EnumerationStore() : m_enumeration()
{}

EnumerationStore::~EnumerationStore()
{

}

void EnumerationStore::AddEnumValue(const std::string& enumName)
{
    const uint32_t firstEnumValue = 0;

    if (m_enumeration.empty())
    {
        std::pair<uint32_t, std::string> p1(firstEnumValue, enumName);
        m_enumeration.push_back(p1);
    }
    else
    {
        auto p1 = m_enumeration.back();
        std::pair<uint32_t, std::string> p2(p1.first+1, enumName);
        m_enumeration.push_back(p2);
    }
}

void EnumerationStore::SetEnumValue(uint32_t enumValue)
{
    if (m_enumeration.empty())
    {
        // TODO error
    }
    else
    {
        m_enumeration.back().first = enumValue;
    }
}

std::string EnumerationStore::GetEnumName(uint32_t enumValue)
{
    std::string result;

    for (auto e: m_enumeration)
    {
        if (e.first == enumValue)
        {
            result = e.second;
        }
    }

    return result;
}

void EnumerationStore::PrintEnumStore()
{
    for (auto e: m_enumeration)
    {
        std::cout << "Value: " << e.first << " has string " << e.second << std::endl;
    }
}
