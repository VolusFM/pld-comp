#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;
#include "CExpression.h"
#include "CInstruction.h"

class CInstrFor: public CInstruction {
public:
	CInstrFor() = default;
	CInstrFor(CExpression* start, CExpression* stopCondition,
			CExpression* evolution, CInstructions& blockContent);
	~CInstrFor();

	void explore_tos(TOS& tos) const;
	void optimize();
	void to_IR(CFG* cfg) const;
	void gen_asm_z80(ostream& o, const CFunction* f) const;

	CInstructions blockContent;
	CExpression* start;
	CExpression* stopCondition;
	CExpression* evolution;

private:
	// no copy wanted
	CInstrFor(const CInstrFor&); // no implementation
	CInstrFor& operator=(const CInstrFor&); // no implementation
};
