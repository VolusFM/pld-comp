#pragma once

#include <string>
using std::string;

class TOS;
#include "CExpression.h"
#include "CInstruction.h"

class CInstrDoWhile: public CInstruction {
public:
    CInstrDoWhile() = default;
    CInstrDoWhile(CExpression* condition, CInstructions& blockContent);
    ~CInstrDoWhile();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;
    
    CInstructions blockContent;
    CExpression* condition;
    
private:
    // no copy wanted
    CInstrDoWhile(const CInstrDoWhile&); // no implementation
    CInstrDoWhile& operator=(const CInstrDoWhile&); // no implementation
};

