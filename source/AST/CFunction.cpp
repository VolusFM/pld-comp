#include "CFunction.h"

#include "CInstrVariable.h"
#include "CExpression.h"

string CFunction::to_asm() const {
  string code;
  code += name + ":\n";
  
  code += "  # prologue\n";
  code += "  pushq %rbp # save %rbp on the stack\n";
  code += "  movq %rsp, %rbp # define %rbp for the current function\n";
  
  for (const string& i : tos) {
    code += "  # variable " + tosType.at(i) + " " + i + "\n";
  }
  
  code += "  # contenu\n";
  
  for (const CInstruction* i : instructions) {
    code += i->to_asm();
  }
  
  code += "  # epilogue\n";
  code += "  popq %rbp # restore %rbp from the stack\n";
  code += "  ret\n";
  
  return code;
}

void CFunction::fill_tos() {
  for (auto it = instructions.begin(); it != instructions.end(); ++it) {
    const auto& i = **it;
    const CInstrVariable* instrvar = dynamic_cast<const CInstrVariable*>(&i);
    if (instrvar != nullptr) {
      string variable = instrvar->name;
      tos.push_back(variable);
      tosType[variable] = "int";
      
      CExpressionCompose* affectation = new CExpressionCompose();
      CExpressionVar* exprvar = new CExpressionVar();
      exprvar->variable = variable;
      affectation->lhs = exprvar;
      affectation->op = '=';
      affectation->rhs = instrvar->expr;
      *it = affectation;
    }
  }
}

