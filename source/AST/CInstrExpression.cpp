#include "CInstrExpression.h"

#include <string>
using std::to_string;

CInstrExpression::CInstrExpression()
: expr(nullptr)
{
}

#include <iostream>
using std::cout;
using std::endl;

string CInstrExpression::to_asm(const CFunction * f) const
{
  CFunction* fm = const_cast<CFunction*>(f);
  return expr->to_asm(fm).first;
}

