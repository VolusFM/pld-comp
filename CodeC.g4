grammar CodeC;

prog: function;

function: functionheader '{' functionbody '}';

functionheader: type name parameters;

functionbody: 'return' INTVAL ';';

type: 'int';

name: 'main';

parameters: '(' ')' ;

INTVAL : [0-9]+;

WS: [ \n\t\r] -> skip; 

