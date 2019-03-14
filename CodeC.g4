grammar CodeC;

prog: function*;

function: functionheader instructionsbloc;

functionheader: type IDENT parameters;

instructionsbloc: '{' instructions '}';
instructions: instruction*;

instruction: instrreturn ';' #return
	| vardefinition ';' #def_variable
	| expression ';' #instru_expr;

vardefinition: type IDENT #var_without_expr
	| type IDENT '=' expression #var_with_expr;

expression: INTVAL #const
	| IDENT #variable
	| (IDENT '=' INTVAL) #affectation;

instrreturn: 'return' expression #return_expr
	| 'return' #return_void;

type: 'int';

parameters: '(' ')' ;

INTVAL : [0-9]+;
IDENT : [a-zA-Z][a-zA-Z0-9]*;

WS: [ \n\t\r] -> skip; 

