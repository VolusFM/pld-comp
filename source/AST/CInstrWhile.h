#pragma once

#include <string>
using std::string;

#include "CExpression.h"
#include "CInstruction.h"

//whileblock: 'while' '(' rvalue ')' anyinstruction;

class CInstrWhile: public CInstruction {
public:
    CInstrWhile() = default;
    CInstrWhile(CExpression* condition, CInstructions& blockContent);
    ~CInstrWhile();

    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;

    CInstructions blockContent;
    CExpression* condition;

private:
    // no copy wanted
    CInstrWhile(const CInstrWhile&); // no implementation
    CInstrWhile& operator=(const CInstrWhile&); // no implementation
};

