#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;
#include "CExpression.h"
#include "CInstruction.h"

class CInstrIf: public CInstruction {
public:
	CInstrIf() = default;
	CInstrIf(CExpression* condition, CInstructions& blockTrue,
			CInstructions& blockFalse);
	~CInstrIf();

	void explore_tos(TOS& tos) const;
	void optimize();
	void to_IR(CFG* cfg) const;
	void gen_asm_z80(ostream& o, const CFunction* f) const;

	CInstructions blockTrue;
	CInstructions blockFalse;
	CExpression* condition;

private:
	// no copy wanted
	CInstrIf(const CInstrIf&); // no implementation
	CInstrIf& operator=(const CInstrIf&); // no implementation
};

