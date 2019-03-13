#include "CFunction.h"

using namespace std;

string CFunction::to_asm() const {
  string code;
  code += "  # prologue\n";
  code += "  pushq %rbp # save %rbp on the stack\n";
  code += "  movq %rsp, %rbp # define %rbp for the current function\n";
  code += name + ":\n";
  code += "  movl $" + to_string(returnvalue) + ", %eax\n";
  code += "  # epilogue\n";
  code += "  popq %rbp # restore %rbp from the stack\n";
  code += "  ret\n";
  return code;
  //TODO : remove duplicate instructions based on what is implemented in CInstrReturn
}
