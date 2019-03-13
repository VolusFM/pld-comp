grammar CodeC;

prog: function;

function: functionheader '{' functionbody '}';

functionheader: type name parameters;

functionbody: instructions;

instructions: instructions instruction
            | instruction ;

instruction: (instrreturn | vardefinition | expression) ';';

vardefinition: type IDENT vardefinitionend;
vardefinitionend: /*epsilon*/ | ('=' expression);

expression: INTVAL | (IDENT '=' INTVAL);

instrreturn: 'return' INTVAL;

type: 'int';

name: IDENT;

parameters: '(' ')' ;

INTVAL : [0-9]+;
IDENT : [a-zA-Z][a-zA-Z0-9]+;

WS: [ \n\t\r] -> skip; 

