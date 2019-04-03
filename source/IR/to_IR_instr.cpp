#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

#include "../AST/CExpression.h"
#include "../AST/CInstruction.h"
#include "../AST/CInstrExpression.h"
#include "../AST/CInstrVariable.h"
#include "../AST/CInstrReturn.h"
#include "../AST/CInstrArray.h"

void CInstructions::to_IR(CFG* cfg) const {
    for (auto it = instructions.begin(); it != instructions.end(); ++it) {
        (*it)->to_IR(cfg);
    }
}

void CInstrExpression::to_IR(CFG* cfg) const {
    expr->to_IR(cfg);
}

void CInstrArray::to_IR(CFG* cfg) const {
    //to do
}

void CInstrVariable::to_IR(CFG* cfg) const {
    if (expr != nullptr) expr->to_IR(cfg);
}

void CInstrReturn::to_IR(CFG* cfg) const {
    if (expr != nullptr) expr->to_IR(cfg);
    
    // to do
}

