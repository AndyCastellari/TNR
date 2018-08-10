/*
 * BasicJSONParser.cpp
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

#include "BasicJSONParser.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;

namespace tnr {

//! Helper to indent while developing
std::string padding(int depth)
{
    return std::string(depth, ' ');
}

BasicJSONParser::BasicJSONParser(ObjectMap & om) : m_om(om)
{
    // Fill the object map with default types - maybe as a test but not sure
    tnr_baseData_ptr  u8(new POD_U8( 0x00, "U8"));
    tnr_baseData_ptr u16(new POD_U16(0x00, "U16"));
    tnr_baseData_ptr u24(new POD_U24(0x00, "U24"));
    tnr_baseData_ptr u32(new POD_U32(0x00, "U32"));

    tnr_baseData_ptr  s8(new POD_S8( 0x00, "S8"));
    tnr_baseData_ptr s16(new POD_S16(0x00, "S16"));
    tnr_baseData_ptr s24(new POD_S24(0x00, "S24"));
    tnr_baseData_ptr s32(new POD_S32(0x00, "S32"));

    tnr_baseData_ptr ascii(new TNR_C_String("", "STRING"));

    m_om.AddObject(u8);
    m_om.AddObject(u16);
    m_om.AddObject(u24);
    m_om.AddObject(u32);

    m_om.AddObject(s8);
    m_om.AddObject(s16);
    m_om.AddObject(s24);
    m_om.AddObject(s32);

    m_om.AddObject(ascii);
}

BasicJSONParser::~BasicJSONParser()
{
    // Nothing dynamic to explicitly delete, everything uses smart pointers
}

/**
 * Find Type from Name looks up a type like U8 and
 * creates an object of that type
 * Name is the name of the object, type is the 'class'
 * e.g. "ApplicationType": "U16" - name is ApplicationType and type is U8
 */
bool BasicJSONParser::FindTypeFromName(const char * name, const char * type, tnr_baseData_ptr &retObj)
{
    bool result = true;
    std::string typeStr(type);
    std::string nameStr(name);

    // FindObject returns a clone of the object in the objectDirectory matching type, e.g ."U8"
    // Set the new objects name to be the name of the item from the JSON, e.g. "ApplicationAllowed"
    if (m_om.FindObject(typeStr, retObj))
    {
        // JSON would be like "MyFieldName" : "PredefinedType"
        // Although retObj is a clone of the type PredefinedType the description must be updated to "MyFieldName"
        retObj->setDescription(nameStr);
    }
    else
    {
        printf("type <%s> not found in object map\n", type);
        result = false;
    }

    return result;
}


/**
 * If this method finds the type passed in, it creates an object of that type
 * with the name passed in and adds it to the container.
 */
bool BasicJSONParser::AddItemToContainer(TNRContainer_ptr &c, const char * name, const char * type, tnr_format &output_format)
{
    bool result = true;

    tnr_baseData_ptr recordObj;
    result = FindTypeFromName(name, type, recordObj);
    if (result)
    {
        recordObj->setFormat(output_format);
        c->Add(recordObj);
    }
    else
    {
        printf("Failure in AddItemToContainer\n");
        result = false;
    }

    return result;
}

/**
 * JSON looks like either
 * 1.    record : {"Count" : 12, "record" : "U32" }
 * or
 * 2.    record : {"Count" : 12, "record" : { ... } }
 * Count is passed in a number
 * In case 1, the value following "record" must be a known type
 * In case 2, the value following "record" is recursively parsed
 */
bool BasicJSONParser::AddFixedArrayToContainer( const char * containerName,
                                                TNRContainer_ptr c,
                                                U32 count,
                                                Value &recordType,
                                                int depth,
                                                bool addToOM,
                                                std::string ObjectName,
                                                tnr_format &output_format)
{
    bool result = true;
    tnr_baseData_ptr recordObj;

    // Parse count as number and record as either String or Object
    if (recordType.IsString())
    {
        // If this is a name value pair, the value must be a known type
        // (in a final parser, we will check an object for known types, for now check for U8, etc.)
        result = FindTypeFromName("item", recordType.GetString(), recordObj);

        recordObj->setFormat(output_format);
    }
    else    // Must be object
    {
        TNRContainer_ptr local_c(new TNRContainer("Record"));
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
        recordType.Accept( writer );

        local_c->setFormat(output_format);

        result = parseTNRObject(containerName, local_c, sb.GetString(), depth + 4, output_format);    // WRONG, this is part of the fixed array, not the parent container

        if (result)
        {
            recordObj = local_c;    // Hack to allow single place addition
        }
    }

    if (result)
    {
        // Create Fixed Array Object with count.GetUint() and item type recordObj and add to container
        TNRFixedArray_ptr fixed(new TNRFixedArray(containerName, count, recordObj));
        fixed->setFormat(output_format);
        c->Add(fixed);

        if (addToOM)
        {
            // Add parent object to dictionary, i.e. c with name found earlier
            tnr_baseData_ptr t = std::dynamic_pointer_cast<tnr_baseData>( fixed );
            t->setDescription(ObjectName);
            result = m_om.AddObject(t);
        }
    }

    return result;
}

/**
 * JSON looks like either
 * 1.    record : {"Count" : "U8", "record" : "U32" }
 * or
 * 2.    record : {"Count" : "U8", "record" : { ... } }
 * In both cases, the value following "Count" must be a known type
 * In case 1, the value following "record" must be a known type
 * In case 2, the value following "record" is recursively parsed
 */
bool BasicJSONParser::AddCountedArrayToContainer(    const char * containerName,
                                                    TNRContainer_ptr c,
                                                    Value &count,
                                                    Value &recordType,
                                                    int depth,
                                                    bool addToOM,
                                                    std::string ObjectName,
                                                    tnr_format &output_format)
{
    bool result = true;
    tnr_baseData_ptr recordObj;

    // Parse count as number and record as either String or Object
    if (recordType.IsString())
    {
        // If this is a name value pair, the value must be a known type
        // (in a final parser, we will check an object for known types, for now check for U8, etc.)
        result = FindTypeFromName("Item", recordType.GetString(), recordObj);

        recordObj->setFormat(output_format);
    }
    else    // Must be object
    {
        TNRContainer_ptr local_c(new TNRContainer("Record"));
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
        recordType.Accept( writer );

        local_c->setFormat(output_format);

        result = parseTNRObject(containerName, local_c, sb.GetString(), depth + 4, output_format);

        if (result)
        {
            recordObj = local_c;    // Hack to allow single place addition
        }
    }

    if (result)
    {
        // Get type of count
        tnr_baseData_ptr countType;
        result = FindTypeFromName("Count", count.GetString(), countType);
        countType->setFormat(output_format);    // This makes count look like first value when Description is turned off

        if (result)
        {
            // Create Counted Array Object with countType and item type recordObj and add to parent container
            TNRCountedArray_ptr counted(new TNRCountedArray(containerName, countType, recordObj));
            counted->setFormat(output_format);
            c->Add(counted);

            if (addToOM)
            {
                // Add parent object to dictionary, i.e. c with name found earlier
                tnr_baseData_ptr t = std::dynamic_pointer_cast<tnr_baseData>( counted );
                t->setDescription(ObjectName);
                result = m_om.AddObject(t);
            }
        }
    }

    return result;
}

/**
 * This method is called from ParseJSONToTNR when a JSON object type is encountered.
 * Three types of objects are catered for:
 * 1.    Fixed Array
 * 2.    Counted Array
 * 3.    A composite of other JSON types
 *
 * In all cases a new object is created and added to the parent container that is passed in
 */
bool BasicJSONParser::parseTNRObject(const char * containerName, TNRContainer_ptr c, const char * input_json, int depth, tnr_format &output_format)
{
    bool result = true;
    // In the grammar of this system, an object that has the attribute ObjectName will be
    // added to the ObjectMap. Because adding to the map clones the object, we fully populate
    // the object before adding it. This flag is set to indicate that the object must be
    // added after the object is complete and just before we return
    bool addToOM = false;
    std::string objectName;

    // Copy the current parent format - it may be changed and then passed to child objects
    tnr_format child_format = output_format;

    rapidjson::Document document;

    if ( document.Parse<0>( input_json ).HasParseError() )
    {
        std::cout << "Error parsing" << std::endl;
        result = false;
    }
    else
    {
        // ////////////////////////////////////////////////////////
        // Try and add formatting to the party - TBC - experimental

        if (document.HasMember("NewLine"))
        {
            Value &NewLine = document["NewLine"];            // Make this object print on one line

            // Check if any formatting changes have been specified
            // Look for "NewLine" : "off"
            if (NewLine.IsString() && (strcmp(NewLine.GetString(), "off") == 0))
            {
                printf("New Line turned off in %s\n", containerName);
                child_format.setOutputNewline(false);
            }
        }

        if (document.HasMember("Description"))
        {
            Value &Description = document["Description"];// Print items within object without description

            // Look for "Description" : "off"
            if (Description.IsString()
                    && (strcmp(Description.GetString(), "off") == 0))
            {
                printf("Description turned off in %s\n", containerName);
                child_format.setOutputDescription(false);
            }
        }
        // ////////////////////////////////////////////////////////

        // Is this object an array? Identified in our grammar by the fields type, count and record
        if (document.HasMember("type") && document.HasMember("record") && document.HasMember("count") )
        {
            Value &type = document["type"];
            Value &count = document["count"];
            Value &recordType = document["record"];

            if (document.HasMember("ObjectName"))
            {
                Value &ObjectName = document["ObjectName"];     // Optionally add this array type to ObjectMap

                // Check if the object being created should also be added to the Object Map
                if (ObjectName.IsString())
                {
                    objectName = ObjectName.GetString();
                    addToOM = true;
                }
            }

            if (type.IsString())
            {
                // Check for Fixed array which has a fixed count and either a built-in type or an object
                if ((strcmp(type.GetString(), "FixedArray") == 0) && count.IsUint() && (recordType.IsString() || recordType.IsObject()))
                {
                    //                    printf("%sType of object is <%s> with size %u\n", padding(depth).c_str(), type.GetString(), count.GetUint());
                    result = AddFixedArrayToContainer(containerName, c, count.GetUint(), recordType, depth + 4, addToOM, objectName, child_format);
                }
                // Check for Counted array which has a variable count (with a known type) and either a built-in type or an object
                else if ((strcmp(type.GetString(), "CountedArray") == 0) && count.IsString() && (recordType.IsString() || recordType.IsObject()))
                {
                    //                    printf("%sType of object is <%s>\n", padding(depth).c_str(), type.GetString());
                    result = AddCountedArrayToContainer(containerName, c, count, recordType, depth + 4, addToOM, objectName, child_format);
                }
                else
                {
                    // type must be one of the values above, either FixedArray or CountedArray
                    result = false;
                }
            }
            else
            {
                // type must be string and isn't
                result = false;
            }
        }
        else    // Not an array so create a local object and populate it
        {
//            TNRContainer_ptr local_c(new TNRContainer("composite"));
            // Don't need a local container, just add it to the parent
            TNRContainer_ptr local_c(c);
            local_c->setFormat(child_format);    // Set format of this record

            // Iterate over members
            for (auto itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
            {
                if ( itr->value.IsObject() )
                {
                    // Case where JSON is like
                    // "My Record" : { ... }
                    // so defines a structure which is parsed recursively
                    //                    printf("%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), kTypeNames[itr->value.GetType()]);
                    rapidjson::StringBuffer sb;
                    rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
                    itr->value.Accept( writer );
                    result = parseTNRObject(itr->name.GetString(), local_c, sb.GetString(), depth + 4, child_format);        // Should this be parseJSONToTNR?
                }
                else if ( itr->value.IsString() )
                {
                    if (strcmp("ObjectName", itr->name.GetString()) == 0)
                    {
                        // Case where JSON is like
                        // "ObjectName" : "someName"
                        // Special case of a definition called ObjectName - it means put this object into the objectMap with the name given
                        // But after the object and all sub-objects have been built so set flag and name for later
                        printf("ObjectName defines object %s\n", itr->value.GetString());
                        addToOM = true;
                        objectName = itr->value.GetString();
                    }
                    else if (strcmp("NewLine", itr->name.GetString()) == 0)
                    {
                        // Do nothing as we dealt with this outside at top of function
                    }
                    else if (strcmp("Description", itr->name.GetString()) == 0)
                    {
                        // Do nothing as we dealt with this outside at top of function
                    }
                    else
                    {
                        // Case where the JSON is like
                        // "MyFieldName" : "U8"
                        // So the value part should already be in the Object Map (checked in called function)
                        result = AddItemToContainer(local_c, itr->name.GetString(), itr->value.GetString(), child_format);
                    }
                }
                else
                {
                    // Not part of our grammar  - error
                    result = false;
                }
            }

            // If the parsing was successful and an object name was supplied, add to Object Map
            if (result && addToOM)
            {
                // Add parent object to dictionary, i.e. c with name found earlier
                tnr_baseData_ptr t = std::dynamic_pointer_cast<tnr_baseData>( local_c );
                t->setDescription(objectName);
                result = m_om.AddObject(t);
            }
        }
    }    // End of Parse was OK


    return result;
}

/**
 * This is the top-level parses that whole JSON document
 * The top level document cannot be an array (currently)
 */
bool BasicJSONParser::parseJSONToTNR(const char * containerName, TNRContainer_ptr c, const char * input_json, int depth)
{
    bool result = true;
    tnr_format output_format;

    // In the grammar of this system, an object that has the attribute ObjectName will be
    // added to the ObjectMap. Because adding to the map clones the object, we fully populate
    // the object before adding it. This flag is set to indicate that the object must be
    // added after the object is complete and just before we return
    bool addToOM = false;
    std::string objectName;

    rapidjson::Document document;

    if ( document.Parse<0>( input_json ).HasParseError() )
    {
        std::cout << "Error parsing" << std::endl;
        result = false;
    }
    else
    {
        // Iterate over members
        for (auto itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
        {
            if ( itr->value.IsObject() )
            {
                rapidjson::StringBuffer sb;
                rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
                itr->value.Accept( writer );
                result = parseTNRObject(itr->name.GetString(), c, sb.GetString(), depth + 4, output_format);
            }
            else if ( itr->value.IsString() )
            {
                // Special case of a definition called ObjectName - it means put this object into the objectMap with the name given
                if (strcmp("ObjectName", itr->name.GetString()) == 0)
                {
                    // This is a definition of an object for the library
                    printf("ObjectName defines object %s\n", itr->value.GetString());
                    addToOM = true;
                    objectName = itr->value.GetString();
                }
                else
                {
                    // If this is a name value pair, the value must be a known type
                    // (in a final parser, we will check an object for known types, for now check for U8, etc.)
                    result = AddItemToContainer(c, itr->name.GetString(), itr->value.GetString(), output_format);
                }
            }
            else
            {
                // Not part of our grammar  - error
                result = false;
            }
        }
    }

    // If the parsing was successful and an object name was supplied, add to Object Map
    if (result && addToOM)
    {
        // Add parent object to dictionary, i.e. c with name found earlier
        tnr_baseData_ptr t = std::dynamic_pointer_cast<tnr_baseData>( c );
        t->setDescription(objectName);
        result = m_om.AddObject(t);
    }

    return result;
}

} /* namespace tnr */

