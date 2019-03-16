#include "CInstrReturn.h"

#include <string>
using std::to_string;

CInstrReturn::CInstrReturn()
: expr(nullptr)
{
}

string CInstrReturn::to_asm() const
{
  string code;
  
  int* returnValue = nullptr;
  if (dynamic_cast<CExpressionInt*>(expr) != nullptr) {
    returnValue = &dynamic_cast<CExpressionInt*>(expr)->valeur;
  }
  
  if (returnValue != nullptr)
  {
    code += "  movl $" + to_string(* returnValue) + ", %eax\n"; 
  }
  code += "  popq %rbp\n";
  code += "  ret\n";
  return code;
}

