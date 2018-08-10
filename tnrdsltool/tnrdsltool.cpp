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

#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>

#include "tnr.h"
#include "ObjectMap.h"
#include "BasicJSONParser.h"

#include "SimpleTextReadWriteIf.h"
#include "FormattedTextReadWriteIf.h"
#include "StreamReadWriteIf.h"

#include <iostream>
#include <sstream>
#include <fstream>


using namespace rapidjson;
using namespace tnr;
using namespace std;

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
            std::stringstream buffer;
            buffer << t.rdbuf();
            s = buffer.str();
        }
        else
        {
            result = false;
        }
    }
    catch (const std::exception &e)
    {
        result = false;
    }

    return result;
}

// Define for experimental extra switches
#define TEST_ARGS

#define COPYRIGHT "TNR Data Manipulation Tool (c) 2013-2016"

int main(int argc, char** argv)
{
    int result = 0;
    bool requiredArg = true;
    bool optionalArg = false;

    // object map and parser will be used for library files and the main object
    ObjectMap om;
    BasicJSONParser parser(om);

    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try
    {
        // The CmdLine object parses the argv array based on the Arg objects that it contains.
        // Argument types are created and added to this object then it is used to parse
        // the command line and either fail with a usage or succed so the program can use the arguments
        TCLAP::CmdLine cmd(COPYRIGHT, ' ', "0.2");

        // Command line parameter: -t --template
        // Define a mandatory parameter to define JSON file with template of the object being decoded
        TCLAP::ValueArg<std::string> mainObject("t","template","Template of object to be processed",requiredArg,"test.json","string");
        cmd.add( mainObject );

#ifdef TEST_ARGS
        // Command line parameter: --of
        // Define a mandatory parameter for the output file --of
        TCLAP::ValueArg<std::string> outputFileObject("","of","Output file",requiredArg,"cout","string");
        cmd.add( outputFileObject );
#else
        // xor option for write to stdout or write to file
        TCLAP::SwitchArg useStdOutSwitch("","stdout","Write to standard output", false);
        TCLAP::ValueArg<std::string> outputFileObject("","of","Output file",false,"[output.bin | output.json | output.txt]","string");
        vector<TCLAP::Arg*>  xorlist1;
        xorlist1.push_back(&useStdOutSwitch);
        xorlist1.push_back(&outputFileObject);
//        cmd.xorAdd( xorlist1 );
        cmd.xorAdd(useStdOutSwitch,  outputFileObject);
#endif

#ifdef TEST_ARGS
        // Command line parameter: --if
        // Define a mandatory parameter for the input file
        TCLAP::ValueArg<std::string> inputFileObject("","if","Input file",requiredArg,"cin","string");
        cmd.add( inputFileObject );
#else
        // xor option for read from stdin of read from file
        TCLAP::SwitchArg useStdInSwitch("","stdin","Read from standard input", true);
        TCLAP::ValueArg<std::string> inputFileObject("","if","Input file",true,"[input.bin | input.json | input.txt]","string");
        vector<TCLAP::Arg*>  xorlist2;
        xorlist2.push_back(&useStdInSwitch);
        xorlist2.push_back(&inputFileObject);
        cmd.xorAdd( xorlist2 );
#endif

        // Command line parameter: -l --library
        // Define a parameter that can have 0 or more instances for json files containing object definitions
        TCLAP::MultiArg<std::string> jsonLibrary("l", "library", "JSON library file", optionalArg, "lib.json");
        cmd.add( jsonLibrary );

        // Command line parameter: -L --library-path
        // Define a parameter that can have 0 or more instances for locations of json files containing object definitions
        TCLAP::MultiArg<std::string> jsonLibraryPath("L", "library-path", "Path to JSON library file", optionalArg, "/home/jsonlib/" );
        cmd.add( jsonLibraryPath );

#ifdef TEST_ARGS
        // Command line parameter: --binary-text
        // Define a parameter to force the conversion from binary file to text file
        // otherwise conversion is text to binary
        TCLAP::SwitchArg binaryToTextSwitch("","binary-text","Convert binary to text", optionalArg);
        cmd.add( binaryToTextSwitch );
#else
        TCLAP::SwitchArg binaryToTextSwitch("","binary-text","Convert binary to text", false);
        TCLAP::SwitchArg textToBinarySwitch("","text-binary","Convert text to binary", false);

        vector<TCLAP::Arg*>  xorlist;
        xorlist.push_back(&binaryToTextSwitch);
        xorlist.push_back(&textToBinarySwitch);
        cmd.xorAdd( xorlist );
#endif

        // Command line parameter: --diag-args
        // Define a parameter to output command line parameters
        TCLAP::SwitchArg diagArgSwitch("","diag-args","Diagnostic on arguments", optionalArg);
        cmd.add( diagArgSwitch );

        // Command line parameter: --diag-om
        // Define a parameter to request printing the contents of the object map
        TCLAP::SwitchArg diagObjectMapSwitch("","diag-om","Diagnostic on Object Map", optionalArg);
        cmd.add( diagObjectMapSwitch );

        // Command line parameter: --dry-run
        // Define a parameter to force the tool to check everything but not produce the output file
        TCLAP::SwitchArg dryRunSwitch("","dry-run","Read and Parse JSON but don't process input", optionalArg);
        cmd.add( dryRunSwitch );

        // Parse the argv array.
        cmd.parse( argc, argv );

        //===============================================================================================
        // Parsing successful so extract data values of arguments

        // Template object
        std::string mainObjectFile = mainObject.getValue();

        // Library files
        vector<string> library = jsonLibrary.getValue();
        vector<string> libraryPaths = jsonLibraryPath.getValue();

        // Whether we are binary=>text or text=>binary (default with no switch)
        bool readBinary = binaryToTextSwitch.isSet();

        // Input and output files
        std::string inputFile = inputFileObject.getValue();;
        std::string outputFile = outputFileObject.getValue();

        //===============================================================================================
        // Print arguments if this switch is set
        if (diagArgSwitch.isSet())
        {
            cout << "Object file is " << mainObjectFile << endl;

            // Output library files and paths
            cout << "library files :";
            for (std::string & s: library)
            {
                cout << " " << s;
            }
            cout << endl;

            // Output arguments
            cout << "library paths :";
            for (std::string & s: libraryPaths)
            {
                cout << " " << s;
            }
            cout << endl;

            cout << "Options:" << endl;
            cout << ((readBinary) ? "Binary to Text Conversion" : "Text to Binary Conversion") << endl;
            cout << "Read from " << inputFile << endl;
            cout << "Write to  " << outputFile << endl;
        }

        //===============================================================================================
        // Parse the libraries (if any)

        // For now we are ignoring the library paths - that will be used when opening the files
        cout << endl << "Parsing library files" << endl;
        for (std::string & libFile: library)
        {
            std::string library_json;
            if (LoadFileToString(libFile.c_str(), library_json))
            {
                TNRContainer_ptr c(new TNRContainer("testContainer"));

                // Make the tnr object from JSON
                if (parser.parseJSONToTNR("Document", c, library_json.c_str(), 0))
                {
                    cout << "Parsed " << libFile << endl;
                }
                else
                {
                    cerr << "Failed to Parse " << libFile << endl;
                }
            }
            else
            {
                cerr << "Failed to load <" << libFile << "> as TNR Object JSON" << endl;
            }
        }
        cout << endl;

        //===============================================================================================
        // Parse the template
        std::string input_json;

        // Process Input to output
        if (LoadFileToString(mainObjectFile.c_str(), input_json))
        {
            TNRContainer_ptr c(new TNRContainer("testContainer"));

            // Make the tnr object from JSON
            if (parser.parseJSONToTNR("Document", c, input_json.c_str(), 0))
            {
                // If this is NOT a dry run, process input to output
                if (!dryRunSwitch.isSet())
                {
                    ios_base::openmode mode_in = ios_base::in;
                    ios_base::openmode mode_out = ios_base::out;
                    
                    if (readBinary)
                    {
                       mode_in |= ios_base::binary;
                    }
                    else
                    {
                       mode_out |= ios_base::binary;
                    }
                    std::shared_ptr<std::ifstream> in_stream(new std::ifstream());
                    std::shared_ptr<std::ofstream> out_stream(new std::ofstream());

                    // try to open the input and output file
                    in_stream->open(inputFile.c_str(), mode_in);
                    out_stream->open(outputFile.c_str(), mode_out);

                    if (in_stream->good() && out_stream->good())
                    {
                        cout << "Opened <" << inputFile << "> as input" << endl;
                        cout << "Opened <" << outputFile << "> as output" << endl;
                        if (readBinary)
                        {
                            StreamReadIf read_if(in_stream);
#if 0
                            SimpleTextWriteIf write_if(out_stream);
#else
                            FormattedTextWriteIf write_if(out_stream);
#endif
                            // Use it to read the input
                            c->read(read_if);        // Read binary data
                            c->write(write_if);    // Write text version
                        }
                        else
                        {
                            // Read text, write binary
#if 0
                            SimpleTextReadIf read_if(in_stream);
#else
                            FormattedTextReadIf read_if(in_stream);
#endif
                            StreamWriteIf write_if(out_stream);

                            // Use it to read the input
                            c->read(read_if);        // Read binary data
                            c->write(write_if);    // Write text version
                        }
                    }
                    else
                    {
                        // TODO can't open files
                        if (!in_stream->good())
                        {
                            cerr << "Failed to open <" << inputFile << "> as input" << endl;
                        }
                        if (!out_stream->good())
                        {
                            cerr << "Failed to open <" << outputFile << "> as output" << endl;
                        }
                    }
                }    // End of dry run is not set, do nothing if it IS set
                else
                {
                    // Nothing to do for a dry run
                }
            }
            else
            {
                cerr << "Failed to parse <" << mainObjectFile << "> as TNR Object JSON" << endl;
            }
        }
        else
        {
            cerr << "Failed to load <" << mainObjectFile << "> as TNR Object JSON" << endl;
        }

        //===============================================================================================
        // This diagnostic allows inspection of the ObjectMap at the end of JSON parsing
        if (diagObjectMapSwitch.isSet())
        {
            cout << "Object Map" << endl;
            // Output Object Map
            om.PrintMap();
        }

    }
    catch (TCLAP::ArgException &e)  // catch any exceptions
    {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        result = -1;
    }

    return result;
}
