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

string CInstrExpression::to_asm(const CFunction* f) const
{
  CFunction* fm = const_cast<CFunction*>(f);
  return expr->to_asm(fm).first;
}

