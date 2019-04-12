#include "../AST/CInstruction.h"
#include "../AST/CInstrExpression.h"
#include "../AST/CInstrReturn.h"
#include "../AST/CInstrVariable.h"
#include "../AST/CInstrArray.h"
#include "../AST/CInstrIf.h"
#include "../AST/CInstrFor.h"
#include "../AST/CInstrDoWhile.h"
#include "../AST/CInstrWhile.h"

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::to_string;
#include <utility>
using std::pair;

#include "../AST/CFunction.h"
#include "../AST/CExpression.h"

void CInstructions::gen_asm_z80(ostream& o, const CFunction* f) const {
	for (CInstruction* instruction : instructions) {
		instruction->gen_asm_z80(o, f);
	}
}

void CInstrExpression::gen_asm_z80(ostream& o, const CFunction* f) const {
	expr->gen_asm_z80_full(o, f);
}

void CInstrArray::gen_asm_z80(ostream& o, const CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for arrays" << endl;
	throw;
}

void CInstrVariable::gen_asm_z80(ostream& o, const CFunction* f) const {
	if (expr != nullptr) {
		expr->gen_asm_z80_full(o, f);
	}
}

void CInstrReturn::gen_asm_z80(ostream& o, const CFunction* f) const {
	if (expr != nullptr) {
		CFunction* fm = const_cast<CFunction*>(f);
		string result = expr->gen_asm_z80(o, fm);

		if (result != "hl" && result != "a") {
			if (result.at(0) != '$') {
				o << "  ld    hl, (" << result << ")\n";
				fm->tos.free_temp(result);
			} else {
				o << "  ld    hl, " << result.c_str() + 1 << "\n";
			}
		}

	}
	// o << "  pop   ix\n";
	o << "  ret\n";
}

void CInstrIf::gen_asm_z80(ostream& o, const CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for control statements" << endl;
	throw;
}

void CInstrDoWhile::gen_asm_z80(ostream& o, const CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for control statements" << endl;
	throw;
}

void CInstrFor::gen_asm_z80(ostream& o, const CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for control statements" << endl;
	throw;
}

void CInstrWhile::gen_asm_z80(ostream& o, const CFunction* f) const {
	cerr << "PROBLEM: gen_asm_z80 unimplemented for control statements" << endl;
	throw;
}

