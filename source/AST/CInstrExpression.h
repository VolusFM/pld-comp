#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
class CExpression;
class TOS;

class CInstrExpression : public CInstruction {
public:
    CInstrExpression(CExpression* expr);
    ~CInstrExpression();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;
    
    CExpression* expr;
    
private: // no copy wanted
    CInstrExpression(const CInstrExpression&); // no implementation
    CInstrExpression& operator=(const CInstrExpression&); // no implementation
};

