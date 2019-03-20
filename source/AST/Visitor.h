#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "antlr4-runtime.h"
#include "../antlr/CodeCBaseVisitor.h"

#include "CProg.h"
#include "CFunction.h"
#include "CExpression.h"
#include "CInstrReturn.h"
#include "CInstrVariable.h"
#include "CInstrExpression.h"

class Visitor : public CodeCBaseVisitor
{
public:
  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override
  {
    CProg prog;

    for (auto ctx_func : ctx->function())
    {
      prog.functions.push_back(*((CFunction *)visit(ctx_func)));
    }

/*<<<<<<< HEAD
    virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx)
            override {
        string name = visit(ctx->functionheader());
        CInstructions * block = (CInstructions *) visit(
                ctx->instructionsbloc());
        CFunction * func = new CFunction(name, block);
        func->fill_tos();
        return func;
    }

    virtual antlrcpp::Any visitFunctionheader(
            CodeCParser::FunctionheaderContext *ctx) override {
        string s(ctx->IDENT()->getText());
        // Return directly as a string to avoid memory leaks.
        return s;
    }

    virtual antlrcpp::Any visitInstructionsbloc(
            CodeCParser::InstructionsblocContext *ctx) override {
        vector<CInstruction*> * instructions = (vector<CInstruction*>*) visit(
                ctx->instructions());
        CInstructions* block = new CInstructions(*instructions);
        // This pointer has been used, we may delete it to avoid memory leaks.
        // delete instructions;
        /*bloc->instructions = (vector<CInstruction*>) visit(
                        ctx->instructions()));*/
        /*return block;
    }

    virtual antlrcpp::Any visitInstructions(
            CodeCParser::InstructionsContext *ctx) override {
        vector<CInstruction*> instructions;

        for (auto ctx_instr : ctx->instruction()) {
            instructions.push_back((CInstruction*) visit(ctx_instr));
        }

        //vector<CInstruction *> answer(instructions);

        return new vector<CInstruction*>(instructions);
        //return answer;
    }

    virtual antlrcpp::Any visitReturn(CodeCParser::ReturnContext *ctx)
            override {
        return (CInstruction*) ((CInstrReturn*) visit(ctx->instrreturn()));
    }

    virtual antlrcpp::Any visitReturn_expr(CodeCParser::Return_exprContext *ctx)
            override {
        CInstrReturn * instr = new CInstrReturn();
        instr->expr = (CExpression*) visit(ctx->expression());
        return instr;
    }

    virtual antlrcpp::Any visitReturn_void(CodeCParser::Return_voidContext *ctx)
            override {
        return new CInstrReturn();
    }

    virtual antlrcpp::Any visitInstr_def(CodeCParser::Instr_defContext *ctx)
            override {
        return (CInstruction*) ((CInstrVariable*) visit(ctx->vardefinition()));
    }
=======
    return new CProg(prog);
  }
>>>>>>> fd94b1d06a7a7a583d10142bb1bf0fc4cfa2a0bd*/

  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx)
      override
  {
    string name = *((string *)visit(ctx->functionheader()));
    CInstructions * block = (CInstructions *) visit(
                ctx->instructionsbloc());
    CFunction *func = new CFunction(name, block);
    func->fill_tos();
    return func;
  }

  virtual antlrcpp::Any visitFunctionheader(
      CodeCParser::FunctionheaderContext *ctx) override
  {
    return new string(ctx->IDENT()->getText());
  }

  virtual antlrcpp::Any visitInstructionsbloc(
      CodeCParser::InstructionsblocContext *ctx) override
  {
    CInstructions *bloc = new CInstructions();
    bloc->instructions = *((vector<CInstruction *> *)visit(
        ctx->instructions()));
    return bloc;
  }

  virtual antlrcpp::Any visitInstructions(
      CodeCParser::InstructionsContext *ctx) override
  {
    vector<CInstruction *> instructions;

    for (auto ctx_instr : ctx->instruction())
    {
      instructions.push_back((CInstruction *)visit(ctx_instr));
    }

    return new vector<CInstruction *>(instructions);
  }

  virtual antlrcpp::Any visitReturn(CodeCParser::ReturnContext *ctx)
      override
  {
    return (CInstruction *)((CInstrReturn *)visit(ctx->instrreturn()));
  }

  virtual antlrcpp::Any visitReturn_expr(CodeCParser::Return_exprContext *ctx)
      override
  {
    CInstrReturn *instr = new CInstrReturn();
    instr->expr = (CExpression *)visit(ctx->expression());
    return instr;
  }

  virtual antlrcpp::Any visitReturn_void(CodeCParser::Return_voidContext *ctx)
      override
  {
    return new CInstrReturn();
  }

  virtual antlrcpp::Any visitInstr_def(CodeCParser::Instr_defContext *ctx)
      override
  {
    return (CInstruction *)((CInstrVariable *)visit(ctx->vardefinition()));
  }

  virtual antlrcpp::Any visitDef_var(CodeCParser::Def_varContext *ctx)
      override {
        string name = ctx->IDENT()->getText();
        CInstrVariable * var = new CInstrVariable("int", name);
        return var;
  }

  virtual antlrcpp::Any visitDef_var_with_expr(
      CodeCParser::Def_var_with_exprContext *ctx) override {
        string name = ctx->IDENT()->getText();
        CExpression * expr = (CExpression*) visit(ctx->expression());
        CInstrVariable * var = new CInstrVariable("int", name, expr);

        return var;
  }

  virtual antlrcpp::Any visitInstr_expr(CodeCParser::Instr_exprContext *ctx)
      override
  {
    CExpression *expr = (CExpression *)visit(ctx->expression());
    CInstrExpression *instr = new CInstrExpression(expr);
    return (CInstruction *)instr;
  }

  virtual antlrcpp::Any visitVariable(CodeCParser::VariableContext *ctx)
      override
  {
    CExpressionVar *expr = new CExpressionVar(ctx->IDENT()->getText());
    return (CExpression *)expr;
  }

  virtual antlrcpp::Any visitConst(CodeCParser::ConstContext *ctx) override
  {
    CExpressionInt *expr = new CExpressionInt(
        (int)stoi(ctx->INTVAL()->getText()));
    return (CExpression *)expr;
  }

  virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override
  {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx)
      override
  {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAffect_expr(CodeCParser::Affect_exprContext *ctx) 
  override {
        CExpression* rhs = (CExpression*) visit(ctx->expression());

        CExpressionVar* lhs = new CExpressionVar(ctx->IDENT()->getText());
        lhs->variable = ctx->IDENT()->getText();

        CExpressionComposed * expr = new CExpressionComposed(
                (CExpression *) lhs, ctx->OPAFF()->getText(),
                (CExpression *) rhs);
        return (CExpression*) expr;
  }

  virtual antlrcpp::Any visitParenth_expr(CodeCParser::Parenth_exprContext *ctx) override
  {
    CExpression *rhs = (CExpression *)visit(ctx->expression());

        return rhs;
    }

    virtual antlrcpp::Any visitAdd_expr(CodeCParser::Add_exprContext *ctx)
            override {
        CExpression* rhs = (CExpression*) visit(ctx->expression()[1]);
        CExpression* lhs = (CExpression*) visit(ctx->expression()[0]);

        CExpressionComposed * expr = new CExpressionComposed(
                (CExpression *) lhs, ctx->OPADD()->getText(),
                (CExpression *) rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitMult_expr(CodeCParser::Mult_exprContext *ctx)
            override {
        CExpression* rhs = (CExpression*) visit(ctx->expression()[1]);
        CExpression* lhs = (CExpression*) visit(ctx->expression()[0]);

        CExpressionComposed * expr = new CExpressionComposed(
                (CExpression *) lhs, ctx->OPMULT()->getText(),
                (CExpression *) rhs);
        return (CExpression*) expr;
    }

  /*  virtual antlrcpp::Any visitNeg_expr(CodeCParser::Neg_exprContext *ctx) override
  {
    CExpression *rhs = (CExpression *)visit(ctx->expression());
    CExpression *lhs = new CExpressionInt(0);

    CExpressionComposed *expr = new CExpressionComposed(
        (CExpression *)lhs, "-", (CExpression *)rhs);
    return (CExpression *)expr;
  }*/
};
