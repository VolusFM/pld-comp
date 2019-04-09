#include "CInstrReturn.h"

#include "CExpression.h"

void CInstrReturn::optimize() {
    CExpression* opti = expr->optimize();
    if (opti != nullptr) {
        delete expr;
        expr = opti;
    }
}

CInstrReturn::CInstrReturn()
: expr(nullptr)
{
}

CInstrReturn::CInstrReturn(CExpression* expr)
: expr(expr)
{
}

CInstrReturn::~CInstrReturn() {
    if (expr != nullptr) {
        delete expr;
    }
}

