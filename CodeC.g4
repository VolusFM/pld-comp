grammar CodeC;

prog: function;

function: functionheader '{' functionbody '}';

functionheader: type name parameters;

functionbody: 'return' INTVAL ';';

type: 'int';

name: IDENT;

parameters: '(' ')' ;

INTVAL : [0-9]+;
IDENT : [a-zA-Z][a-zA-Z0-9]+;

WS: [ \n\t\r] -> skip; 

