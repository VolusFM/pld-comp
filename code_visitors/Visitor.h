#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "antlr4-runtime.h"
#include "../code_antlr/CodeCBaseVisitor.h"

#include "CProg.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CInstrReturn.h"

class Visitor : public CodeCBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
    CProg prog;
    
    for (auto ctx_func : ctx->function()) {
      prog.functions.push_back(*( (CFunction*) visit(ctx_func) ));
    }
    
    return new CProg(prog);
  }
  
  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx) override {
    CFunction func;
    func.name = *( (string*) visit(ctx->functionheader()) );
    func.instructions = *( (vector<CInstruction*>*) visit(ctx->instructionsbloc()) );
    return new CFunction(func);
  }

  virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *ctx) override {
    return new string(ctx->IDENT()->getText());
  }

  virtual antlrcpp::Any visitInstructionsbloc(CodeCParser::InstructionsblocContext *ctx) override {
    return visit(ctx->instructions());
  }
  virtual antlrcpp::Any visitInstructions(CodeCParser::InstructionsContext *ctx) override {
    vector<CInstruction*> instructions;
    
    for (auto ctx_instr : ctx->instruction()) {
      instructions.push_back((CInstruction*) visit(ctx_instr));
    }
    
    return new vector<CInstruction*>(instructions);
  }

  virtual antlrcpp::Any visitReturn(CodeCParser::ReturnContext *ctx) override {
    return (CInstruction*) ((CInstrReturn*) visit(ctx->instrreturn()));
  }
  virtual antlrcpp::Any visitReturn_expr(CodeCParser::Return_exprContext *ctx) override {
    CInstrReturn* instr = new CInstrReturn();
    instr->expr = (CExpression*) visit(ctx->expression());
    return instr;
  }
  virtual antlrcpp::Any visitReturn_void(CodeCParser::Return_voidContext *ctx) override {
    return new CInstrReturn();
  }

/*
  virtual antlrcpp::Any visitVarDefinition(CodeCParser::VardefinitionContext *ctx) override {
    return new string(ctx->IDENT()->getText());
  }
*/

  /* TEMPORAIRE */
  virtual antlrcpp::Any visitDef_variable(CodeCParser::Def_variableContext *ctx) override {
    return (CInstruction*) new CExpressionInt();
  }
  /* TEMPORAIRE */

  virtual antlrcpp::Any visitInstr_expr(CodeCParser::Instr_exprContext *ctx) override {
    return (CInstruction*) ((CExpression*) visit(ctx->expression()));
  }

  virtual antlrcpp::Any visitVariable(CodeCParser::VariableContext *ctx) override {
    CExpressionVar* expr = new CExpressionVar();
    expr->variable = ctx->IDENT()->getText();
    return (CExpression*) expr;
  }
  virtual antlrcpp::Any visitConst(CodeCParser::ConstContext *ctx) override {
    CExpressionInt* expr = new CExpressionInt();
    expr->valeur = (int) stoi(ctx->INTVAL()->getText());
    return (CExpression*) expr;
  }
  virtual antlrcpp::Any visitAffectation(CodeCParser::AffectationContext *ctx) override {
    CExpressionInt* rhs = new CExpressionInt();
    rhs->valeur = (int) stoi(ctx->INTVAL()->getText());
    
    CExpressionVar* lhs = new CExpressionVar();
    lhs->variable = ctx->IDENT()->getText();
    
    CExpressionCompose* expr = new CExpressionCompose();
    expr->lhs = lhs;
    expr->op = '=';
    expr->rhs = rhs;
    return (CExpression*) expr;
  }
  
  virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

};
