#include "CInstrVariable.h"

CInstrVariable::CInstrVariable(CType type, string name) :
        type(type), name(name), expr(nullptr) {
}

CInstrVariable::CInstrVariable(CType type, string name, CExpression* expr) :
        type(type), name(name), expr(expr) {
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

