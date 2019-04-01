grammar CodeC;

prog: function*;

function: functionheader instructionsblock;

functionheader: type IDENT parameters;

instructionsblock: '{' instructions '}';
instructions: instruction*;

instruction: instrreturn ';' #return
	| vardefinition ';' #instr_def
	| expression ';' #instr_expr;

vardefinition: type vardefinitionmult (','vardefinitionmult)*;

vardefinitionmult : IDENT #def_var
    | IDENT '=' expression	#def_var_with_expr;

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

type: 'int' | 'char' ;

parameters: '(' (singleparameter (',' singleparameter)*)? ')';

singleparameter : type IDENT;


INTDEC : [1-9][0-9]*;
INTHEX : '0x'[0-9A-F]+;
INTBIN : '0b'[01]+;
INTOCT :'0'[0-7]+;
IDENT : [a-zA-Z][a-zA-Z0-9_]*;

OPMULT : [*/];
OPADD : [+-];
OPAFF : '=';

COMMENTMULT : '/*' .* '*/' -> skip;
COMMENT: '//' ~('\n')* '\n' -> skip;

WS: [ \n\t\r] -> skip; 

INCLUDE : '#' ~[\n]* -> skip;


