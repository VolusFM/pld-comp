#include "CInstrReturn.h"

#include "CExpression.h"

void CInstrReturn::explore_tos(TOS& tos) const {
}

void CInstrReturn::optimize() {
    if (expr != nullptr) {
        CExpressionPart* opti = expr->optimize();
        if (opti != nullptr) {
            delete expr;
            expr = opti;
        }
    }
}

CInstrReturn::CInstrReturn()
: expr(nullptr)
{
}

CInstrReturn::CInstrReturn(CExpressionPart* expr)
: expr(expr)
{
}

CInstrReturn::~CInstrReturn() {
    if (expr != nullptr) {
        delete expr;
    }
}

