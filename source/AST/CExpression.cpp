#include "CExpression.h"

#include <string>
using std::to_string;

string CExpressionVar::to_asm() const {
  string code;
  code = variable;
  return code;
}

string CExpressionInt::to_asm() const {
  string code;
  code = to_string(valeur);
  return code;
}

string CExpressionCompose::to_asm() const {
  string code;
  code = "(" + lhs->to_asm() + op + rhs->to_asm() + ")";
  return code;
}

