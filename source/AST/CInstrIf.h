








//ifblock: 'if' '(' rvalue ')' anyinstruction elseblock?;

#pragma once

#include <string>
using std::string;

#include "CExpression.h"
#include "CInstruction.h"

class CInstrIf: public CInstruction {
public:
    CInstrIf() = default;
    CInstrIf(CExpression* condition, CInstructions* blockTrue, CInstructions* blockFalse);
    //~CInstrIf(); //TODO : implementation

    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;

    CInstructions* blockTrue;
    CInstructions* blockFalse;  //can be nullptr
    CExpression* condition;

private:
    // no copy wanted
    CInstrIf(const CInstrIf&); // no implementation
    CInstrIf& operator=(const CInstrIf&); // no implementation
};
