#pragma once

#include <string>
using std::string;

#include "CExpression.h"
#include "CInstruction.h"





//ifblock: 'if' '(' rvalue ')' anyinstruction elseblock?;






class CInstrIf: public CInstruction {
public:
    CInstrIf() = default;
    CInstrIf(CExpression* condition, CInstructions& blockTrue, CInstructions& blockFalse);
    ~CInstrIf();
    
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

