/*
 * BasicJSONParser.h
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

#ifndef BASICJSONPARSER_H_
#define BASICJSONPARSER_H_

#include "tnr.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "ObjectMap.h"

namespace tnr {

class BasicJSONParser {
public:
    explicit BasicJSONParser(ObjectMap & om);
    virtual ~BasicJSONParser();

    // TBC fix this daft name
    //! From the type name, retrieve an object of that type from the Object (Type) Map and assign it the name passed in
    bool FindTypeFromName(const char * name, const char * type, tnr_baseData_ptr &retObj);

    //! From the type name, retrieve an object, name it, apply the format and add it to the container
    bool AddItemToContainer(TNRContainer_ptr &c, const char * name, const char * type,
            tnr_format &output_format);

    bool AddFixedArrayToContainer(const char * containerName, const TNRContainer_ptr& c, U32 count,
            rapidjson::Value &recordType, int depth, bool addToOM, std::string ObjectName,
            tnr_format &output_format);

    bool AddCountedArrayToContainer(const char * containerName, const TNRContainer_ptr& c, rapidjson::Value &count,
            rapidjson::Value &recordType, int depth, bool addToOM, std::string ObjectName,
            tnr_format &output_format);

    bool parseTNRObject(const char * containerName, const TNRContainer_ptr& c, const char * input_json, int depth,
            tnr_format &output_format);

    bool parseJSONToTNR(const char * containerName, TNRContainer_ptr c, const char * input_json, int depth);

protected:
    ObjectMap &m_om;
};

} /* namespace tnr */
#endif /* BASICJSONPARSER_H_ */
