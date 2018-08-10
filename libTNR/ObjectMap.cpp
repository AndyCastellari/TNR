/*
 * ObjectMap.cpp
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

#include "ObjectMap.h"
#include <stdio.h>

namespace tnr {

ObjectMap::ObjectMap() : m_objectDirectory()
{
    // TODO Auto-generated constructor stub

}

ObjectMap::~ObjectMap()
{
    // TODO Auto-generated destructor stub
}

bool ObjectMap::AddObject(tnr_baseData_ptr& object)
{
    bool result = true;

    std::pair<std::map<std::string, tnr_baseData_ptr>::iterator, bool> check;
//    printf("ObjectMap::AddObject   <%s>\n", object->getDescription().c_str());
    check = m_objectDirectory.insert(std::pair<std::string, tnr_baseData_ptr>(object->getDescription(), object->clone()));

    result = check.second;
    return result;
}

bool ObjectMap::FindObject(std::string& objectName, tnr_baseData_ptr& object)
{
    bool result = true;
    std::map<std::string, tnr_baseData_ptr>::iterator it;
    it = m_objectDirectory.find(objectName);
    if (it != m_objectDirectory.end())
    {
            object = (it->second)->clone();
    }
    else
    {
        result = false;
    }
    return result;
}

void ObjectMap::PrintMap()
{
    std::map<std::string, tnr_baseData_ptr>::iterator it;
    printf("The original key values of m_objectDirectory\n");
    for ( it = m_objectDirectory.begin( ); it != m_objectDirectory.end( ); it++ )
    {
        printf("Key is %s with value %u\n", it -> first.c_str(), it->second->getCount());
    }

}

} /* namespace tnr */
