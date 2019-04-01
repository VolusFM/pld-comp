#pragma once

#include <string>
#include <vector>
using std::string;

#include "CInstruction.h"
#include "CInstrVariable.h"

class CInstrVariableMulti: public CInstruction {
public:
    CInstrVariableMulti(vector<CInstrVariable*>);
    ~CInstrVariableMulti();
    string to_asm(const CFunction * f) const;
    vector<CInstrVariable*> varDefs;
    
private: // no copy wanted
    CInstrVariableMulti(const CInstrVariableMulti&); // no implementation
    CInstrVariableMulti& operator=(const CInstrVariableMulti&); // no implementation
};

