#pragma once

#include <string>
using std::string;

#include "CExpression.h"
#include "CInstruction.h"

//whileblock: 'while' '(' rvalue ')' anyinstruction;

class CInstrFor: public CInstruction {
public:
    CInstrFor() = default;
    CInstrFor(CExpression* start,
            CExpression* stopCondition,
            CExpression* evolution, CInstructions& blockContent);
    ~CInstrFor();

    void to_IR(CFG* cfg) const;
    string to_asm(const CFunction* f) const;

    CInstructions blockContent;
    CExpression* start;
    CExpression* stopCondition;
    CExpression* evolution;

private:
    // no copy wanted
    CInstrFor(const CInstrFor&); // no implementation
    CInstrFor& operator=(const CInstrFor&); // no implementation
};
