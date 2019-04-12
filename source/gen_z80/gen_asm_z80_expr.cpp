#include "../AST/CExpression.h"
#include "../AST/CExpressionCall.h"

#include <string>
using std::to_string;
#include <iostream>
using std::cerr;
using std::endl;

#include "../AST/CFunction.h"

void CExpression::gen_asm_z80_full(ostream& o, const CFunction* f) const {
	CFunction* fm = const_cast<CFunction*>(f);
	expr->gen_asm_z80(o, fm);
}

string CExpressionInt::gen_asm_z80(ostream& o, CFunction* f) const {
	o << "  ld    hl, " << value << "\n";
	return "hl";
}

string CExpressionVar::gen_asm_z80(ostream& o, CFunction* f) const {
	string varaddr = f->tos.get_address_z80(variable);
	o << "  ld    hl, (" << varaddr << ")\n";
	return varaddr;
}

string CExpressionComposed::gen_asm_z80(ostream& o, CFunction* f) const {
	string variable = "hl"; //FIXME or a

	string lhsvar = lhs->gen_asm_z80(o, f);
	string rhsvar = rhs->gen_asm_z80(o, f);

	if (op == "=") {
		o << "  ld    (hl), e\n";
		o << "  inc   hl\n";
		o << "  ld    (hl), d\n";
		// o << "  dec   hl\n";
		o << "  ex    de, hl\n";
	} else {
		/*
		 if (op == "*") {
		 o << "  mul   hl, de\n";
		 }
		 if (op == "/") {
		 o << "  div   hl, de\n";
		 }
		 if (op == "%") {
		 o << "  cltd\n"; // convert values to long double
		 o << "  idivl " << rhsvar << "\n"; // do the division
		 }
		 */
		if (op == "+") {
			o << "  add   hl, de\n";
		}
		if (op == "-") {
			o << "  or    a\n";
			o << "  sbc   hl, de\n";
		}
		if (op == "<" || op == "<=" || op == ">" || op == ">=" || op == "=="
				|| op == "!=") {
			o << "  or    a\n";
			o << "  sbc   hl, de\n";
			/*
			 if (op == "<") {
			 o << "  setl";
			 }
			 if (op == "<=") {
			 o << "  setle";
			 }
			 if (op == ">") {
			 o << "  setg";
			 }
			 if (op == ">=") {
			 o << "  setge";
			 }
			 if (op == "==") {
			 o << "  sete";
			 }
			 if (op == "!=") {
			 o << "  setne";
			 }
			 o << "  %al\n";
			 o << "  movzbl  %al, %eax\n";
			 */
		}
		if (op == "&") {
			o << "  ld    a, h";
			o << "  and   d";
			o << "  ld    h, a";
			o << "  ld    a, l";
			o << "  and   e";
			o << "  ld    l, a";
		}
		if (op == "|") {
			o << "  ld    a, h";
			o << "  or    d";
			o << "  ld    h, a";
			o << "  ld    a, l";
			o << "  or    e";
			o << "  ld    l, a";
		}
		if (op == "^") {
			o << "  ld    a, h";
			o << "  xor   d";
			o << "  ld    h, a";
			o << "  ld    a, l";
			o << "  xor   e";
			o << "  ld    l, a";
		}
	}

	f->tos.free_temp(lhsvar);
	f->tos.free_temp(rhsvar);

	return variable;
}

string CExpressionVarArray::gen_asm_z80(ostream& o, CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for array expressions" << endl;
	throw;
}

string CExpressionCall::gen_asm_z80(ostream& o, CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for control statements" << endl;
	throw;
}

