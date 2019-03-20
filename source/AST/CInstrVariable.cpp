#include "CInstrVariable.h"

CInstrVariable::CInstrVariable(CType type, string name) :
        type(type), name(name), expr(nullptr) {
}

CInstrVariable::CInstrVariable(CType type, string name, CExpression* expr_) :
        type(type), name(name) {
    CExpressionVar* exprVar = new CExpressionVar(name);
    expr = new CExpressionComposed(exprVar, "=", expr_);
}

CInstrVariable::~CInstrVariable() {
    if (expr != nullptr) {
        delete expr;
    }
}

string CInstrVariable::to_asm(const CFunction* f) const {
    if (expr == nullptr) {
        return "";
    } else {
        return expr->to_asm(f).first;
    }
}

