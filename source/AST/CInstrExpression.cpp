#include "CInstrExpression.h"

#include <string>
using std::to_string;

CInstrExpression::CInstrExpression()
: expr(nullptr)
{
}

string CInstrExpression::to_asm() const
{
  string code;
  code = "  # " + expr->to_asm() + "\n";
  return code;
}

