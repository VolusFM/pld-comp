grammar CodeC;


prog: function*;

function: functionheader instructionsblock;

functionheader: type IDENT parameters;


anyinstruction: instructionsblock // some instructions
	| instruction // one instruction
	| ';'; // no instructions

instructionsblock: '{' instruction* '}';

instruction: instrreturn ';' #return
	| vardefinition ';' #instr_def
	| expression ';' #instr_expr
	| ifblock #if_block
	| whileblock #while_block;


ifblock: 'if' '(' expression ')' anyinstruction elseblock?;
elseblock: 'else' anyinstruction;

whileblock: 'while' '(' expression ')' anyinstruction;


vardefinition: type vardefinitionmult (','vardefinitionmult)*;

vardefinitionmult : IDENT #def_var
    | IDENT '=' expression	#def_var_with_expr;

expression: rvalue;

rvalue: (OPADD|OPSUB) rvalue #unary_expr
	| rvalue (OPMULT|OPDIV|OPMOD) rvalue #mult_expr
	| rvalue (OPADD|OPSUB) rvalue #add_expr
	// In C, boolean type doesn't exist and we use integers instead
	| rvalue (OPRELATIONINF|OPRELATIONINFEQUAL|OPRELATIONSUP|OPRELATIONSUPEQUAL) rvalue #relational_expr
	| rvalue (OPEQUALITY|OPINEQUALITY) rvalue #equality_expr
	| rvalue OPBINARYAND rvalue #binary_and_expr
	| rvalue OPBINARYEXCLUSIVEOR rvalue #binary_exclusive_or_expr
	| rvalue OPBINARYOR rvalue #binary_or_expr 
	| rvalue OPAND rvalue #logical_and_expr
	| rvalue OPOR rvalue #logical_or_expr
	| lvalue OPAFF rvalue #affect_expr
	| lvalue #variable
	| intval #const
	| IDENT '(' (parametercall (',' parametercall)*)? ')' #function_call
	| '('rvalue')' #parenth_expr;

lvalue : IDENT;

intval : INTDEC #intval_dec
        | INTHEX #intval_hex
        | INTBIN #intval_bin
        | INTOCT #intval_oct;

instrreturn: 'return' expression #return_expr
	| 'return' #return_void;

type: 'int' | 'char' ;

parameters: '(' (singleparameter (',' singleparameter)*)? ')';
singleparameter : type IDENT;
parametercall : expression;


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
