grammar TNRDSL;

//startRuleName  : (definition)* main EOF ;
startRuleName  : (definition)* EOF ;

definition : 'define' new_type_name '=' variable define_end;
new_type_name : ID;
define_end : ';';

variable :    compound_variable
            | simple_variable
            | fixed_array
            | counted_array
            | variant ;             // Leaves object on stack

compound_variable : compound_start (variable compound_member_end)+ compound_end;
compound_start : '{';
compound_end : '}';
compound_member_end : ';';      // Add variable on stack to parent compound object

simple_variable : existing_type simple_start optional_parameters simple_end ;
existing_type : ID;             // Create variable on stack
simple_start : '(' ;
simple_end : ')' ;

fixed_array : fixed_array_type '(' fixed_array_count optional_parameters ')' fixed_array_element ;
fixed_array_type: 'FixedArray';     // Create fixed array object on stack
fixed_array_count : NUMBER;         // Set size of fixed_array on stack

fixed_array_element : fixed_array_element_start variable fixed_array_element_end;
fixed_array_element_start : '<';
fixed_array_element_end : '>';      // Set top of stack object as element of fixed_array under it on stack

counted_array : counted_array_type '(' optional_parameters ',' simple_variable ')' counted_array_element ;
counted_array_type: 'CountedArray';     // Create counted array on stack

counted_array_element : counted_array_element_start variable counted_array_element_end;
counted_array_element_start : '<';
counted_array_element_end : '>';        // Set counted array count and element from top of stack

variant : variant_type '(' optional_parameters ',' simple_variable ')' ':' '<' variant_elements '>';

variant_type : 'Variant';
variant_elements_start : '<';
variant_elements_end : '>';
variant_elements : (variant_param)* ;
variant_param : variable variant_param_end
            | 'case' variant_selector_value ':';
variant_selector_value : NUMBER;
variant_param_end : ';';

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
