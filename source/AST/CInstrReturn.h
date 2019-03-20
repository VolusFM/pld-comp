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
    string to_asm() const;

    CExpression * expr;
};

