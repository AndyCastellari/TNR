# TNR
Binary data analysis libraries and utilities

This project aims to make analysis of binary data files available to non-programmers by allowing 
them to define the logical structure of binary files and then use a command line utility to convert 
between binary and textual format.

The tools require a template in either JSON or a Domain Specific Language, an input file and an output file; by default the tool converts text to binary but addition of the command line option --binary-text reverses the mode of operation.

For example,

`  tnrtool -t testObject.json --if testObject.bin --of temp.txt --binary-text`

Decodes testObject.bin to temp.txt using the template in testObject.json and,

`  tnrtool -t testObject.json --if temp.txt --of testObject.bin`

Creates a new testObject.bin based on temp3.txt.

It is possible to decode a binary file, edit the text file and recreate a binary file with new values.

- libTNR contains the headers and source for the library
- TNR_tester contains unit tests
- tnrtool contains the source for the JSON command line utility
- tnrdsltool contains the source for the

Build is performed using CMake with the following dependencies

- googletest is used for unit testing
- TCLAP is required for both command line tools
- Rapidjson is required for the JSON tools
- ANTLR4 and antlr C++ runtime are required for DSL tool 

The format of the DSL can be deduced from the files with tnr suffix; a document will be provided shortly giving a fuller description.


