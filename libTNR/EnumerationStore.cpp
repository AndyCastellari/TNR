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
