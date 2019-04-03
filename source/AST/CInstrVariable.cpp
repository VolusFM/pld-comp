#include "CInstrVariable.h"

#include "CExpression.h"

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

