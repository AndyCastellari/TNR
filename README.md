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

Use the DSL tool using command lines like

`  tnrdsltool -t testObject.tnr --if temp.txt --of testObject.bin`

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

# TNR DSL Data Description Language
This section describes the elements of the Domain Specific Language
that is used as input to the parsing process.

A description file consists of one or more definitions of elements.

Currently, there must be an element called main that will be used as the
object that parses the data.

The built-in elements are 
- U8, U16, U24, U32 - unsigned integers
- S8, S16, S24, S32 - signed integers
- STRING - Null-terminated string of ASCII 8-bit characters

Define a new element using syntax like

`define colour = U16("colour");`
- defines an unsigned 16-bit variable with description "colour"

`define pixel = 
{
    colour("Red");
    colour("Green");
    colour("Blue");
};`
- defines a structure of three 16-bit colours called pixel using the definition of colour

There are several collection types

`FixedArray(3, "Array of three pixels") < pixel("Pixel") >`
- Array with fixed number of items
- Type pixel could have been a FixedArray of colour

`CountedArray("Variable length Array of pixels", U16("Number of pixels")) < pixel("Pixel"); >`
- Array with a U16 count of the number of pixels followed by that number of pixels

`Variant("My first variant", U32("Selector")) : < U8("First variant");
case 12: STRING("Second Variant"); U24("Third Variant"); >`
- Object that reads a U32 then selects what to read next based on 
the value in that variable
- First variant is read if selector is 0, second variant if it is 12,
third variant if it is 13
- If the value is not 0, 12 or 13, nothing is read after the selector
- Future features may add a 'default' case to this

The contents of containers may be built-in types, 
types previously defined in the file or a collection of items like those in the definition of type pixel, for example

`define RowOfPixels = CountedArray("Variable array of Pixels", U32("U32 Number of pixels")) <
{
    colour("Red");
    colour("Green");
    colour("Blue");
} >;`

Containers can be nested, for example

`define PixelRowArray = CountedArray("Variable array of Pixels", U32("U32 Number of rows")) <
{
    PixelRow("");
} >;`

Types can have attributes for display, for example,

`U16("Length", description=on, newline=off)`
- Shows the description "Length" but prevents a newline after it when generating a text file
- `U8("Type of colour", enum (red, green, blue, magenta=10, cyan, yellow))` adds a descriptive text to the value of a variable
- Adds red if variable is 0, green for 1, blue for 2, magenta for 10, cyan for 11 and yellow for 12
