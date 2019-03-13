#include "CProg.h"

using namespace std;

string CProg::to_asm() const {
  string code;
  code += ".text\n";
  code += ".global main\n";
  for (const CFunction & f : functions) {
    code += f.to_asm();
  }
  return code;
}
