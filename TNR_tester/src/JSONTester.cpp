/*
 * JSONTester.cpp
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

#include "JSONTester.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "rapidjson/prettywriter.h"	// for stringify JSON
//#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include "rapidjson/filereadstream.h"	// wrapper of C stream for prettywriter as output
#include "rapidjson/filewritestream.h"	// wrapper of C stream for prettywriter as output
#include <cstdio>

#include "tnr.h"
#include "TextLogWriteIf.h"
#include "SimpleTextReadWriteIf.h"
#include "StreamReadWriteIf.h"

#include "BasicJSONParser.h"

using namespace rapidjson;
using namespace tnr;
using namespace std;

bool parseJSONToTNR(const char * containerName, TNRContainer_ptr c, const char * input_json, int depth);

JSONTester::JSONTester() {
	// TODO Auto-generated constructor stub

}

JSONTester::~JSONTester() {
	// TODO Auto-generated destructor stub
}

/**
 * This test is to check that rapidjson parsing is working
 */
bool JSONTester::testParsing()
{
	bool result  = true;

	rapidjson::Document document;
	std::string test =  "{\"a\":{\"z\":21}} ";
	if ( document.Parse<0>( test.c_str() ).HasParseError() ) {
	    std::cout << "Error parsing" << std::endl;
	} else {
	    if ( document[ "a" ].IsObject() ) {
	        rapidjson::StringBuffer sb;
	        rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
	        document[ "a" ].Accept( writer );
	        std::cout << sb.GetString() << std::endl;
	    }
	}

	return result;
}

/**
 * Read file into string
 */

bool LoadFileToString(const char * filename, std::string & s)
{
	bool result = true;

	s.clear();

	try
	{
		std::ifstream t(filename, std::ios_base::in);
		if (t.is_open())
		{
			std::cout << "LoadFileToString(" << filename << ") succeeded" << endl;

			std::stringstream buffer;
			buffer << t.rdbuf();
			s = buffer.str();
		}
		else
		{
			std::cout << "LoadFileToString(" << filename << ") failed" << endl;
			result = false;
		}
	}
	catch (const std::exception &e)
	{
		result = false;
	}

	return result;
}

//! Quick print a string of binary values out
void JSONprintString(const char * title, const std::string &s)
{
	printf("%s : ", title);
	BOOST_FOREACH(char c, s)
	{
		printf("%02x", (U8)c);
	}
	printf("\n");
}

//! Helper to indent while developing
std::string padding(int depth)
{
	return std::string(depth, ' ');
}

bool parseJSONObject(const char * input_json, int depth)
{
	bool result = true;

	rapidjson::Document document;

	if ( document.Parse<0>( input_json ).HasParseError() )
	{
		std::cout << "Error parsing" << std::endl;
		result = false;
	}
	else
	{
		// Iterating object members
		static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
		for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
		{
			printf("%sType of member <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), kTypeNames[itr->value.GetType()]);

			if ( itr->value.IsObject() )
			{
				printf("%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), kTypeNames[itr->value.GetType()]);
				rapidjson::StringBuffer sb;
				rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
				itr->value.Accept( writer );
//				std::cout << padding(depth) << sb.GetString() << std::endl;

				parseJSONObject(sb.GetString(), depth + 4);
			}
			else if ( itr->value.IsString() )
			{
				printf("%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetString());
				if (strcmp(itr->value.GetString(), "FixedArray") == 0)
				{
					// Save value for later
					printf("****%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetString());
				}
				if (strcmp(itr->value.GetString(), "CountedArray") == 0)
				{
					// Save value for later
					printf("****%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetString());
				}
				if (strcmp(itr->value.GetString(), "count_type") == 0)
				{
					// Save value for later
					printf("****%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetString());
				}
				if (strcmp(itr->value.GetString(), "record") == 0)
				{
					// Save value for later
					printf("****%sMember <%s> is <%s>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetString());
				}
			}
			else if ( itr->value.IsInt() )
			{
				printf("%sMember <%s> is <%d>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetInt());
				if (strcmp(itr->name.GetString(), "count") == 0)
				{
					// Save value for later
					printf("****%sMember <%s> is <%d>\n", padding(depth).c_str(), itr->name.GetString(), itr->value.GetInt());
				}

			}

		}
	}

	return result;
}

// Array of bytes conforming to pattern of testObject1.json with real arrays and values
const unsigned char testBytes[] = {
		0x07,					// Allowed applications U8
		0x01, 0x00,				// Transaction performance on U16
		0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,	// Application priority U8[8]
		0x1f,					// Physical Card type U8

		0x04, 0x00, 0x00,		// Bin Values: "CountedArray", "count": "U24" = 4,
		0x12, 0x34, 0x56, 0x78,	// "record": "U32"
		0x34, 0x56, 0x78, 0x12, 	// "record": "U32"
		0x56, 0x78, 0x12, 0x34,  	// "record": "U32"
		0xAA, 0xBB, 0xCC, 0xDD,  	// "record": "U32"

		0x02, 0x00, 0x00, 0x00,		// Bin Ranges: "CountedArray", "count": "U32" = 4,
		0x12, 0x34, 0x56, 0x78,	// "record": "U16/U16"
		0x34, 0x56, 0x78, 0x12, 	// "record": "U16/U16"
		0x99						// SALT
};

bool JSONTester::testJSON_to_Container()
{
	bool result  = true;
	TNRContainer_ptr c(new TNRContainer("testContainer"));
	std::string input_json;
	boost::shared_ptr<std::stringstream> wstream1(new std::stringstream());
	boost::shared_ptr<std::stringstream> wstream2(new std::stringstream());
	boost::shared_ptr<std::stringstream> wstream3(new std::stringstream());
	boost::shared_ptr<std::stringstream> wstream4(new std::stringstream());
	ObjectMap om;
	BasicJSONParser parser(om);

	TextLogWriteIf tlwif(wstream1);
	SimpleTextWriteIf stwif(wstream2);
	SimpleTextReadIf strif(wstream3);
	SimpleTextWriteIf stwif2(wstream4);

	if (LoadFileToString("./testobject1.json", input_json))
	{

		// Create input stream to populate the template container just created
		std::string tempString((const char *)testBytes, sizeof(testBytes));

		boost::shared_ptr<std::istream> _rstream(new std::stringstream(tempString));
		StreamReadIf msrif(_rstream);

		JSONprintString("rstream ", boost::dynamic_pointer_cast<std::stringstream>(_rstream)->str());

		// Make the tnr object from JSON
		parser.parseJSONToTNR("Document", c, input_json.c_str(), 0);

		// Use it to read binary data
		c->read(msrif);		// Read binary data

		// Write out the object as text, long version
		c->write(tlwif);
//		cout << "Text Log Output" << endl << wstream1->str() << endl;

		// Write out in more concise text version
		c->write(stwif);	// Write text version
		cout << "Simple Text Output" << endl << wstream2->str() << endl;

		// Now read back from simple text version and then write it out again
		*wstream3 << wstream2->str();		// Copy text output and check it copied OK
//		cout << "wstream3 is " << endl << wstream3->str() << endl;
//		cout << "wstream2 is " << endl << wstream2->str() << endl;

		c->read(strif);

		wstream2->str("");		// Clear the write interface to no data
		cout << "After clearing wstream2 is " << endl << wstream2->str() << endl;
		// Then write it again from the new contents ofthe object
		c->write(stwif2);	// Write text version
		cout << "Simple Text Output after readback" << endl << wstream4->str() << endl;

	}
	else
	{
		result = false;
	}

	return result;
}


