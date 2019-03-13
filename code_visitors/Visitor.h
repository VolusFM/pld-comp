#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "antlr4-runtime.h"
#include "../code_antlr/CodeCBaseVisitor.h"

#include "CProg.h"
#include "CFunction.h"

class Visitor : public CodeCBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
    CProg prog;
    prog.functions.push_back(*((CFunction*) visit(ctx->function())));
    return new CProg(prog);
  }
  
  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx) override {
    CFunction func;
    func.name = *( (string*) visit(ctx->functionheader()) );
    func.instructions = *( (vector<CInstruction>*) visit(ctx->instructions()) );
    return new CFunction(func);
  }

  virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *ctx) override {
    return new string(ctx->IDENT()->getText());
  }

  virtual antlrcpp::Any visitInstructions(CodeCParser::InstructionsContext *ctx) override {
    vector<CInstruction> instructions;
    
    for (auto ctx_instr : ctx->instruction()) {
      instructions.push_back(*( (CInstruction*) visit(ctx_instr) ));
    }
    
    return new vector<CInstruction>(instructions);
  }

  /* TEMPORAIRE */
  virtual antlrcpp::Any visitReturn(CodeCParser::ReturnContext *ctx) override {
    return new CInstruction();
  }
  virtual antlrcpp::Any visitDef_variable(CodeCParser::Def_variableContext *ctx) override {
    return new CInstruction();
  }
  virtual antlrcpp::Any visitInstru_expr(CodeCParser::Instru_exprContext *ctx) override {
    return new CInstruction();
  }
  /* TEMPORAIRE */

  //return (int) stoi(ctx->INTVAL()->getText());
  
  virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

};
