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
#include "../AST/CInstrIf.h"

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
    if (expr != nullptr)
        expr->to_IR(cfg);
}

void CInstrReturn::to_IR(CFG* cfg) const {
    if (expr != nullptr)
        expr->to_IR(cfg);

    // to do
}

void CInstrIf::to_IR(CFG* cfg) const {
    //TODO : make two basic blocks : one true one false. Add those to cfg's vector of basic block
    // if there is no else statement, the basicblock exit_false will be nullptr (very important to check it later)
    // run to_ir on condition
    // run to_ir on the two blocks (check if the second is nullptr here)
}

