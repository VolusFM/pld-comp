#include "CFunction.h"

#include "CInstrVariable.h"
#include "CInstrExpression.h"
#include "CExpression.h"

string CFunction::to_asm() const {
  string code;
  code += name + ":\n";
  
  code += "  ## prologue\n";
  code += "  pushq %rbp # save %rbp on the stack\n";
  code += "  movq %rsp, %rbp # define %rbp for the current function\n";
  
  for (const string& i : tos) {
    code += "  # variable " + tosType.at(i) + " " + i + "\n";
  }
  
  code += "  ## contenu\n";
  
  for (const CInstruction* i : bloc.instructions) {
    code += i->to_asm();
  }
  
  code += "  ## epilogue\n";
  code += "  popq %rbp # restore %rbp from the stack\n";
  code += "  ret\n";
  
  return code;
}

void CFunction::fill_tos() {
  fill_tos(bloc);
}
void CFunction::fill_tos(CInstructions& bloc) {
  for (auto it = bloc.instructions.begin(); it != bloc.instructions.end(); ++it) {
    const CInstruction* i = *it;
    const CInstrVariable* instrVar = dynamic_cast<const CInstrVariable*>(i);
    if (instrVar != nullptr) {
      string variable = instrVar->name;
      tos.push_back(variable);
      tosType[variable] = "int";
      
      CExpressionVar * exprVar = new CExpressionVar(variable);
      CExpressionComposed * affectation = new CExpressionComposed(exprVar, '=', instrVar->expr);
      CInstrExpression* instrExpr = new CInstrExpression();
      instrExpr->expr = affectation;
      *it = instrExpr;
    }
  }
}

