#pragma once

#include <string>
#include <vector>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"
#include "CInstrVariable.h"
typedef string CType;

class CInstrVariableMulti: public CInstruction {
public:
    CInstrVariableMulti(vector<CInstrVariable*>);
    ~CInstrVariableMulti();
    string to_asm(const CFunction * f) const;
    vector <CInstrVariable*> varDefs;
    
private: // no copy wanted
};

