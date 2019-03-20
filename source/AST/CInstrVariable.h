#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"
typedef string CType;

class CInstrVariable: public CInstruction {
public:
    CInstrVariable(CType type, string name);
    CInstrVariable(CType type, string name, CExpression * expr);
    ~CInstrVariable();
    string to_asm(const CFunction * f) const;
    
    CType type;
    string name;
    CExpression* expr;
};

