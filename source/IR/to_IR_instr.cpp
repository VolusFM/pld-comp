#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

#include "../AST/CInstrExpression.h"
#include "../AST/CInstrVariable.h"
#include "../AST/CInstrVariableMulti.h"
#include "../AST/CInstrReturn.h"

void CInstrVariableMulti::to_IR(CFG* cfg) const {
    for (auto it = varDefs.begin(); it != varDefs.end(); ++it) {
        (*it)->to_IR(cfg);
    }
}

void CInstrExpression::to_IR(CFG* cfg) const {
    expr->to_IR(cfg);
}

void CInstrVariable::to_IR(CFG* cfg) const {
    if (expr != nullptr) expr->to_IR(cfg);
}

void CInstrReturn::to_IR(CFG* cfg) const {
    if (expr != nullptr) expr->to_IR(cfg);
    
    // to do
}

