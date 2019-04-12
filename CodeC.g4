grammar CodeC;


prog: function*;


function: functionheader instructionsblock;

functionheader: (type|VOID) IDENT parameters;

parameters: '(' (singleparameter (',' singleparameter)*)? ')';
singleparameter : type IDENT;


anyinstruction: instructionsblock #anyinstrs // some instructions
	| instruction #anyinstr // one instruction
	| ';' #noinstr; // no instructions

instructionsblock: '{' instruction* '}';


instruction: instrreturn ';' #return
	| definition ';' #instr_def
	| expression ';' #instr_expr
	| ifblock #if_block
	| whileblock #while_block
	| forblock #for_block
	| dowhileblock #do_while_block;

instrreturn: 'return' expressionpart #return_expr
	| 'return' #return_void;


ifblock: 'if' '(' expression ')' anyinstruction elseblock?;
elseblock: 'else' anyinstruction;

whileblock: 'while' '(' expression ')' anyinstruction;
 
forblock: 'for' '(' forcondition ')' anyinstruction;
forcondition: forstartcondition? ';' forstopcondition? ';' forevolution?;
forstartcondition: expression;
forstopcondition: expression;
forevolution: expression;

dowhileblock: 'do' anyinstruction 'while' '(' expression ')' ';';


definition: type symboldefinition (',' symboldefinition)*;
symboldefinition : vardefinition | arraydefinition;

vardefinition : IDENT #def_var
	| IDENT '=' expressionpart #def_var_with_expr;

arraydefinition : IDENT'['intval']' #def_array
	| IDENT'['intval']' '=' '{'(expressionpart (',' expressionpart)*)?'}' #def_array_with_expr;


// needed for encapsulation
expression: expressionpart;
expressionpart: rvalue;

rvalue: (OPNOT|OPADD|OPSUB) rvalue #unary_expr
	| rvalue (OPMULT|OPDIV|OPMOD) rvalue #mult_expr
	| rvalue (OPADD|OPSUB) rvalue #add_expr
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
	| IDENT '(' (expressionpart (',' expressionpart)*)? ')' #function_call
	| '('rvalue')' #parenth_expr;

lvalue: IDENT #simple_variable
	| IDENT'['rvalue']' #variable_in_array;

intval: INTDEC #intval_dec
        | INTHEX #intval_hex
        | INTBIN #intval_bin
        | INTOCT #intval_oct
        | INTCHAR #intval_char;


type: 'int' | 'char' ;



VOID : 'void';

INTOCT :'0'[0-7]+;
INTHEX : '0x'[0-9A-F]+;
INTBIN : '0b'[01]+;
INTDEC : [1-9][0-9]*|'0';
INTCHAR : ['].['];
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
COMMENT : '//' ~('\n')* -> skip;
INCLUDE : '#' ~('\n')* -> skip;

WS : [ \n\t\r] -> skip; 
