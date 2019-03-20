#include "CInstrReturn.h"

#include <string>
using std::to_string;

CInstrReturn::CInstrReturn() :
        expr(nullptr) {
}

string CInstrReturn::to_asm(const CFunction * f) const
{
  string code;
  
  if (expr != nullptr)
  {
    CFunction* fm = const_cast<CFunction*>(f);
    pair<string,string> res = expr->to_asm(fm);
    code += res.first;
    code += "  movl " + res.second + ", %eax\n";
  }
  code += "  popq %rbp\n";
  code += "  ret\n";
  return code;
}

