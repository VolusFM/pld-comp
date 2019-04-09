#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
class CExpression;

class CInstrReturn: public CInstruction {
public:
    CInstrReturn();
    CInstrReturn(CExpression* expr);
    ~CInstrReturn();
    
    void optimize();
    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;

    CExpression* expr;

private:
    // no copy wanted
    CInstrReturn(const CInstrReturn&); // no implementation
    CInstrReturn& operator=(const CInstrReturn&); // no implementation
};

