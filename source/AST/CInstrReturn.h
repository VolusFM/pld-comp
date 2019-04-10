#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;
#include "CInstruction.h"
class CExpression;

class CInstrReturn: public CInstruction {
public:
    CInstrReturn();
    CInstrReturn(CExpression* expr);
    ~CInstrReturn();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    void gen_asm_z80(ostream& o, const CFunction* f) const;

    CExpression* expr;

private:
    // no copy wanted
    CInstrReturn(const CInstrReturn&); // no implementation
    CInstrReturn& operator=(const CInstrReturn&); // no implementation
};

