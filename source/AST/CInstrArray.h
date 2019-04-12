#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include <list>
using std::list;

#include "../CType.h"
class TOS;
#include "CInstruction.h"
class CExpressionPart;

class CInstrArray: public CInstruction {
public:
	CInstrArray(string name, CType type, int count);
	CInstrArray(string name, CType type, int count,
			list<CExpressionPart*> exprs);
	~CInstrArray();

	void explore_tos(TOS& tos) const;
	void optimize();
	void to_IR(CFG* cfg) const;
	void gen_asm_z80(ostream& o, const CFunction* f) const;

	string name;
	CType type;
	int count;
	list<CExpressionPart*> exprs;

private:
	// no copy wanted
	CInstrArray(const CInstrArray&); // no implementation
	CInstrArray& operator=(const CInstrArray&); // no implementation
};

