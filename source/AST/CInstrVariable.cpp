#include "CInstrVariable.h"

#include "CExpression.h"

#include "../TOS.h"

void CInstrVariable::explore_tos(TOS& tos) const {
    tos.add(name, type);
}

void CInstrVariable::optimize()
{
    if (expr != nullptr) {
        CExpression* opti = expr->optimize();
        if (opti != nullptr) {
            delete expr;
            expr = opti;
        }
    }
}

CInstrVariable::CInstrVariable(string name)
: name(name), expr(nullptr)
{
}

CInstrVariable::CInstrVariable(string name, CExpression* expr_)
: name(name)
{
    CExpressionVar* exprVar = new CExpressionVar(name);
    expr = new CExpressionComposed(exprVar, "=", expr_);
}

CInstrVariable::~CInstrVariable() {
    if (expr != nullptr) {
        delete expr;
    }
}

