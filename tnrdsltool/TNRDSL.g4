grammar TNRDSL;

//startRuleName  : (definition)* main EOF ;
startRuleName  : (definition)* EOF ;

definition : 'define' new_type_name '=' expression ;
new_type_name : ID;
//main : 'main' '=' expression ;

expression : compound_start (expression)+ compound_end
           | variable ;
//expression : compound_start (expression)+ compound_end
//           | variable ';';
compound_start : '{';
compound_end : '}';

variable : simple_variable ';'
            | fixed_array
            | counted_array
            | variant ;

simple_variable : existing_type simple_start optional_parameters simple_end ;
simple_start : '(' ;
simple_end : ')' ;
existing_type : ID;
fixed_array : 'FixedArray' '(' fixed_array_count optional_parameters ')' ':' array_element ;
fixed_array_count : NUMBER;
counted_array : 'CountedArray' '(' simple_variable optional_parameters ')' ':' array_element ;
array_element : (expression | variable) ;
variant : 'Union' '(' simple_variable ',' optional_parameters ')' ':' '{' union_parameters '}';

union_parameters : (union_param)* ;
union_param : expression
            | 'case' NUMBER ':';

optional_parameters : // nothing
                    | parameter (',' parameter)*
                    | ',' parameter (',' parameter)*;

parameter : object_description
            | 'format' '=' format_string
            | 'description' '=' (descriptionon|descriptionoff)
            | 'newline' '=' (newlineon|newlineoff)
            | enum_definition  ;
object_description : STRING;
format_string : STRING;
newlineon : 'on';
newlineoff : 'off';
descriptionon : 'on';
descriptionoff : 'off';

enum_definition : 'enum' '(' enum_param (',' enum_param)* ')' ;

enum_param : STRING
            | STRING '=' NUMBER ;

ID : [A-Za-z][A-Za-z0-9_-]* ;     // identifiers start with alpha and then alpha or number or dash or underline
STRING : '"' (.)*? '"' ;
NUMBER : [0-9]+ ;
WS : [ \t\r\n]+ -> channel(HIDDEN) ;
COMMENT
    : '/*' .*? '*/' -> skip ;
LINE_COMMENT
    : '//' ~[\r\n]* -> skip ;
