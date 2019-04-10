#pragma once

#include <string>
using std::string;

#include "CExpression.h"
#include "CInstruction.h"
class TOS;

class CInstrIf: public CInstruction {
public:
    CInstrIf() = default;
    CInstrIf(CExpression* condition, CInstructions& blockTrue, CInstructions& blockFalse);
    ~CInstrIf();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;
    
    CInstructions blockTrue;
    CInstructions blockFalse;
    CExpression* condition;
    
private:
    // no copy wanted
    CInstrIf(const CInstrIf&); // no implementation
    CInstrIf& operator=(const CInstrIf&); // no implementation
};

