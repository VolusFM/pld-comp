#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;
#include "CInstruction.h"
class CExpression;

class CInstrExpression: public CInstruction {
public:
	CInstrExpression(CExpression* expr);
	~CInstrExpression();

	void explore_tos(TOS& tos) const;
	void optimize();
	void to_IR(CFG* cfg) const;
	void gen_asm_z80(ostream& o, const CFunction* f) const;

	CExpression* expr;

private:
	// no copy wanted
	CInstrExpression(const CInstrExpression&); // no implementation
	CInstrExpression& operator=(const CInstrExpression&); // no implementation
};

