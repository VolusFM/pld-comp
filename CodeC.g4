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
	| intval #const
	| IDENT #variable;

intval : INTDEC #intval_dec
        | INTHEX #intval_hex
        | INTBIN #intval_bin
        | INTOCT #intval_oct;

instrreturn: 'return' expression #return_expr
	| 'return' #return_void;

type: 'int';

parameters: '(' ')' ;


INTDEC : [1-9][0-9]*;
INTHEX : '0x'[0-9A-F]+;
INTBIN : '0b'[01]+;
INTOCT :'0'[0-7]+;
IDENT : [a-zA-Z][a-zA-Z0-9]*;

OPMULT : [*/];
OPADD : [+-];
OPAFF : [=];

WS: [ \n\t\r] -> skip; 

