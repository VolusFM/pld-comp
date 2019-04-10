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

CInstrVariable::CInstrVariable(string name, CType type)
: name(name), type(type), expr(nullptr)
{
}

CInstrVariable::CInstrVariable(string name, CType type, CExpression* expr_)
: name(name), type(type)
{
    CExpressionVar* exprVar = new CExpressionVar(name);
    expr = new CExpressionComposed(exprVar, "=", expr_);
}

CInstrVariable::~CInstrVariable() {
    if (expr != nullptr) {
        delete expr;
    }
}

