#include "CInstrExpression.h"

#include "CExpression.h"

void CInstrExpression::explore_tos(TOS& tos) const {
}

CInstrExpression::CInstrExpression(CExpression* expr)
: expr(expr)
{
}

CInstrExpression::~CInstrExpression() {
    if (expr != nullptr) {
        delete expr;
    }
}

void CInstrExpression::optimize()
{
    if (expr != nullptr) {
        expr->optimize();
    }
}

