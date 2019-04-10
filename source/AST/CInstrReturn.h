#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
class CExpression;
class TOS;

class CInstrReturn: public CInstruction {
public:
    CInstrReturn();
    CInstrReturn(CExpression* expr);
    ~CInstrReturn();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;

    CExpression* expr;

private:
    // no copy wanted
    CInstrReturn(const CInstrReturn&); // no implementation
    CInstrReturn& operator=(const CInstrReturn&); // no implementation
};

