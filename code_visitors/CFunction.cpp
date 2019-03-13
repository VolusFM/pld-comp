#include "CFunction.h"

using namespace std;

string CFunction::to_asm() const {
  string code;
  code += name + ":\n";
  code += "  movl $" + to_string(returnvalue) + ", %eax\n";
  code += "  ret\n";
  return code;
}
