grammar TNRDSL;

startRuleName  : (definition)* main EOF ;

definition : 'define' ID '=' expression ;
main : 'main' '=' expression ;

expression : '{' (expression)+ '}'
           | variable ';';

variable : simple_variable
            | fixed_array
            | counted_array
            | variant ;

simple_variable : ID '(' optional_parameters ')' ;
fixed_array : 'FixedArray' '(' NUMBER optional_parameters ')' ':' (expression | variable) ;
counted_array : 'CountedArray' '(' simple_variable optional_parameters ')' ':' (expression | variable) ;
variant : 'Union' '(' simple_variable ',' optional_parameters ')' ':' '{' union_parameters '}';

union_parameters : (union_param)* ;
union_param : expression
            | 'case' NUMBER ':';

optional_parameters : // nothing
                    | parameter (',' parameter)*
                    | ',' parameter (',' parameter)*;

parameter : STRING
            | 'format' '=' STRING
            | 'description' '=' (on|off)
            | 'newline' '=' (on|off)
            | enum_definition  ;
on : 'on';
off : 'off';

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
