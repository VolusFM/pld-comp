#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"

class CInstrReturn: public CInstruction {
public:
    CInstrReturn();
    CInstrReturn(CExpression * expr);
    ~CInstrReturn();
    string to_asm(const CFunction * f) const;
    
    CExpression* expr;
    
private: // no copy wanted
    CInstrReturn(const CInstrReturn&); // no implementation
    CInstrReturn& operator=(const CInstrReturn&); // no implementation
};

