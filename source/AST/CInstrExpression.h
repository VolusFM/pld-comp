#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"

class CInstrExpression: public CInstruction {
public:
    CInstrExpression(CExpression* expr);
    ~CInstrExpression();
    string to_asm(const CFunction* f) const;
    
    CExpression* expr;
    
private: // no copy wanted
    CInstrExpression(const CInstrExpression&); // no implementation
    CInstrExpression& operator=(const CInstrExpression&); // no implementation
};

