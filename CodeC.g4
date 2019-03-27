grammar CodeC;

prog: function*;

function: functionheader instructionsbloc;

functionheader: type IDENT parameters;

instructionsbloc: '{' instructions '}';
instructions: instruction*;

instruction: instrreturn ';' #return
	| vardefinition ';' #instr_def
	| expression ';' #instr_expr;

vardefinition: type IDENT #def_var
	| type IDENT '=' expression #def_var_with_expr;

expression: expression OPMULT expression #mult_expr
	| expression OPADD expression #add_expr
	//| '-' expression #neg_expr
	| IDENT OPAFF expression #affect_expr
	| '('expression')' #parenth_expr
	| INTVAL #const
	| IDENT #variable;

instrreturn: 'return' expression #return_expr
	| 'return' #return_void;

type: 'int';

parameters: '(' ')' ;


INTVAL : [0-9]+;
IDENT : [a-zA-Z][a-zA-Z0-9_]*;

OPMULT : [*/];
OPADD : [+-];
OPAFF : [=];

WS: [ \n\t\r] -> skip; 

