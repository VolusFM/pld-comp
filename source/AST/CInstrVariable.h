#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

#include "../CType.h"
class TOS;
#include "CInstruction.h"
class CExpression;

class CInstrVariable : public CInstruction {
public:
    CInstrVariable(string name, CType type);
    CInstrVariable(string name, CType type, CExpression* expr);
    ~CInstrVariable();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    void gen_asm_z80(ostream& o, const CFunction* f) const;
    
    string name;
    CType type;
    CExpression* expr;
    
private:
    // no copy wanted
    CInstrVariable(const CInstrVariable&); // no implementation
    CInstrVariable& operator=(const CInstrVariable&); // no implementation
};

