grammar CodeC;


prog: function*;

function: functionheader instructionsblock;

functionheader: (type|VOID) IDENT parameters;


anyinstruction: instructionsblock // some instructions
	| instruction // one instruction
	| ';'; // no instructions

instructionsblock: '{' instruction* '}';


instruction: instrreturn ';' #return
	| definition ';' #instr_def
	| rvalue ';' #instr_expr
	| ifblock #if_block
	| whileblock #while_block
    | forblock #for_block
	| dowhileblock #do_while_block;

ifblock: 'if' '(' rvalue ')' anyinstruction elseblock?;
elseblock: 'else' anyinstruction;

whileblock: 'while' '(' rvalue ')' anyinstruction;

//TODO : implement and compile for 
forblock: 'for' '(' forcondition ')' anyinstruction;
forcondition: forstartcondition? ';' forstopcondition? ';' forevolution?;
forstartcondition: rvalue;
forstopcondition: rvalue;
forevolution: rvalue;

// TODO: implement and compile do...while
dowhileblock: 'do' anyinstruction 'while' '(' rvalue ')' ';';

definition: type (vardefinition|arraydefinition) (','(vardefinition|arraydefinition))*;

vardefinition : IDENT #def_var
    | IDENT '=' rvalue	#def_var_with_expr;

arraydefinition : IDENT'['intval']'	#def_array
	| IDENT'['intval']' '=' '{'(rvalue (',' rvalue)*)?'}' #def_array_with_expr;


rvalue: (OPNOT|OPADD|OPSUB) rvalue #unary_expr
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

lvalue : IDENT #simple_variable
	| IDENT'['rvalue']' #variable_in_array;

intval : INTDEC #intval_dec
        | INTHEX #intval_hex
        | INTBIN #intval_bin
        | INTOCT #intval_oct;

instrreturn: 'return' rvalue #return_expr
	| 'return' #return_void;

type: 'int' | 'char' ;

parameters: '(' (singleparameter (',' singleparameter)*)? ')';
singleparameter : type IDENT;
parametercall : rvalue;

VOID : 'void';

INTDEC : [1-9][0-9]*|'0';
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
OPNOT : '!';
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
