/*
 * ObjectMap.h
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

#ifndef OBJECTMAP_H_
#define OBJECTMAP_H_

#include "tnr.h"
#include <map>

namespace tnr {

class ObjectMap
{
public:
    ObjectMap() = default;
    virtual ~ObjectMap() = default;
    //! Adds a clone of the object to the map with the given name
    bool AddObject(tnr_baseData_ptr & object);
    //! Returns a clone of the object with the name
    bool FindObject(const std::string& objectName, tnr_baseData_ptr& object);
    //! Print the contents of the map
    void PrintMap();
protected:
    std::map<std::string, tnr_baseData_ptr> m_objectDirectory;
};

} /* namespace tnr */
#endif /* OBJECTMAP_H_ */
