#include "CFunction.h"

string CFunction::to_asm() const {
  string code;
  code += name + ":\n";
  
  code += "  # prologue\n";
  code += "  pushq %rbp # save %rbp on the stack\n";
  code += "  movq %rsp, %rbp # define %rbp for the current function\n";
  code += "  # contenu\n";
  
  for (const CInstruction* i : instructions) {
    code += i->to_asm();
  }
  
  code += "  # epilogue\n";
  code += "  popq %rbp # restore %rbp from the stack\n";
  code += "  ret\n";
  
  return code;
}

