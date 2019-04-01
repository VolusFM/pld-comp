grammar CodeC;

prog: function*;

function: functionheader instructionsblock;

functionheader: type IDENT parameters;

anyinstruction: instructionsblock
	| instruction
	| ';'; // Empty instruction

instructionsblock: '{' instruction* '}';
// instructions: instruction*; TODO: why is this here?

instruction: instrreturn ';' #return
	| vardefinition ';' #instr_def
	| expression ';' #instr_expr
	| ifblock #if_block
	| whileblock #while_block;

ifblock: 'if' '(' expression ')' anyinstruction elseblock?;

elseblock: 'else' anyinstruction #else_block;
// No need to handle else if blocks as the first rule already does it

whileblock: 'while' '(' expression ')' anyinstruction;

vardefinition: type vardefinitionmult (','vardefinitionmult)*;

vardefinitionmult : IDENT #def_var
    | IDENT '=' expression	#def_var_with_expr;

expression: (OPADD|OPSUB) expression #unary_expr
	| expression (OPMULT|OPDIV|OPMOD) expression #mult_expr
	| expression (OPADD|OPSUB) expression #add_expr
	// In C, boolean type doesn't exist and we use integers instead
	| expression (OPRELATIONINF|OPRELATIONINFEQUAL|OPRELATIONSUP|OPRELATIONSUPEQUAL) expression #relational_expr
	| expression (OPEQUALITY|OPINEQUALITY) expression #equality_expr
	| expression OPBINARYAND expression #binary_and_expr
	| expression OPBINARYEXCLUSIVEOR expression #binary_exclusive_or_expr
	| expression OPBINARYOR expression #binary_or_expr 
	| expression OPAND expression #logical_and_expr
	| expression OPOR expression #logical_or_expr
	| IDENT OPAFF expression #affect_expr
	| IDENT #variable
	| intval #const
	| '('expression')' #parenth_expr;

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

OPMULT : '*';
OPDIV : '/';
OPMOD : '%';
OPADD : '+';
OPSUB : '-';
OPRELATIONINF : '<';
OPRELATIONINFEQUAL : '<=';
OPRELATIONSUP : '>';
OPRELATIONSUPEQUAL : '>=';
OPEQUALITY : '==';
OPINEQUALITY : '!=';
OPBINARYAND : '&';
OPBINARYEXCLUSIVEOR : '^';
OPBINARYOR : '|';
OPAND : '&&';
OPOR : '||';
OPAFF : '=';

COMMENTMULT : '/*' .*? '*/' -> skip;
COMMENT: '//' ~('\n')* -> skip;
INCLUDE : '#' ~('\n')* -> skip;

WS: [ \n\t\r] -> skip; 
