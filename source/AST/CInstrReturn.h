#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;
#include "CInstruction.h"
class CExpressionPart;

class CInstrReturn: public CInstruction {
public:
	CInstrReturn();
	CInstrReturn(CExpressionPart* expr);
	~CInstrReturn();

	void explore_tos(TOS& tos) const;
	void optimize();
	void to_IR(CFG* cfg) const;

	CExpressionPart* expr;

private:
	// no copy wanted
	CInstrReturn(const CInstrReturn&); // no implementation
	CInstrReturn& operator=(const CInstrReturn&); // no implementation
};

