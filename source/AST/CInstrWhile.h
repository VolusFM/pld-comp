#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;
#include "CExpression.h"
#include "CInstruction.h"

class CInstrWhile: public CInstruction {
public:
    CInstrWhile() = default;
    CInstrWhile(CExpression* condition, CInstructions& blockContent);
    ~CInstrWhile();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    
    CInstructions blockContent;
    CExpression* condition;
    
private:
    // no copy wanted
    CInstrWhile(const CInstrWhile&); // no implementation
    CInstrWhile& operator=(const CInstrWhile&); // no implementation
};

