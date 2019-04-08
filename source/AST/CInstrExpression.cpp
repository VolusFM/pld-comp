#include "CInstrExpression.h"

#include "CExpression.h"

CInstrExpression::CInstrExpression(CExpression* expr)
: expr(expr)
{
}

CInstrExpression::~CInstrExpression() {
    if (expr != nullptr) {
        delete expr;
    }
}

