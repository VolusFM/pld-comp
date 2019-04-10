#pragma once

#include <string>
using std::string;

#include "../CType.h"
class TOS;
#include "CInstruction.h"
class CExpression;

class CInstrVariable : public CInstruction {
public:
    CInstrVariable(string name);
    CInstrVariable(string name, CExpression* expr);
    ~CInstrVariable();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;
    
    CType type;
    string name;
    CExpression* expr;
    
private:
    // no copy wanted
    CInstrVariable(const CInstrVariable&); // no implementation
    CInstrVariable& operator=(const CInstrVariable&); // no implementation
};

