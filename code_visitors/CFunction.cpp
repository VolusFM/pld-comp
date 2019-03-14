#include "CFunction.h"

using std::to_string;

string CFunction::to_asm() const {
  string code;
  code += name + ":\n";
  
  bool hasvariables = false;
  
  if (hasvariables) {
  code += "  # prologue\n";
  code += "  pushq %rbp # save %rbp on the stack\n";
  code += "  movq %rsp, %rbp # define %rbp for the current function\n";
  code += "  # contenu\n";
  }
  
  for (const CInstruction* i : instructions) {
    code += i->to_asm();
  }
  
  if (hasvariables) {
  code += "  # epilogue\n";
  code += "  popq %rbp # restore %rbp from the stack\n";
  }
  
  code += "  ret\n";
  return code;
  // TODO : remove duplicate instructions based on what is implemented in CInstrReturn
}

  // code += "  movl $" + to_string(returnvalue) + ", %eax\n";

