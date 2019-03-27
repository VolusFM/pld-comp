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

class Visitor: public CodeCBaseVisitor {
public:

    virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override
    {
        CProg* prog = new CProg();

        for (auto ctx_func : ctx->function()) {
            CFunction* func = (CFunction*) visit(ctx_func);
            prog->functions.push_back(std::move(*func));
            delete func;
        }

        return prog;
    }

    virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx)
            override {
        string name = visit(ctx->functionheader());
        CInstructions* block = (CInstructions*) visit(ctx->instructionsbloc());
        CFunction* func = new CFunction(name, *block);
        func->fill_tos();
        delete block;
        return func;
    }

    virtual antlrcpp::Any visitFunctionheader(
            CodeCParser::FunctionheaderContext *ctx) override {
        string s(ctx->IDENT()->getText());
        return s;
    }

    virtual antlrcpp::Any visitInstructionsbloc(
            CodeCParser::InstructionsblocContext *ctx) override {
        vector<CInstruction*>* instructions = (vector<CInstruction*>*) visit(
                ctx->instructions());
        CInstructions* block = new CInstructions(*instructions);
        delete instructions;
        return block;
    }

    virtual antlrcpp::Any visitInstructions(
            CodeCParser::InstructionsContext *ctx) override {
        vector<CInstruction*> instructions;

        for (auto ctx_instr : ctx->instruction()) {
            instructions.push_back((CInstruction*) visit(ctx_instr));
        }

        return new vector<CInstruction*>(instructions);
    }

    virtual antlrcpp::Any visitReturn(CodeCParser::ReturnContext *ctx)
            override {
        return (CInstruction*) ((CInstrReturn*) visit(ctx->instrreturn()));
    }

    virtual antlrcpp::Any visitReturn_expr(CodeCParser::Return_exprContext *ctx)
            override {
        CExpression* expr = (CExpression*) visit(ctx->expression());
        CInstrReturn* instr = new CInstrReturn(expr);
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

    virtual antlrcpp::Any visitDef_var(CodeCParser::Def_varContext *ctx)
            override {
        string name = ctx->IDENT()->getText();
        CInstrVariable* var = new CInstrVariable("int", name);
        return var;
    }

    virtual antlrcpp::Any visitDef_var_with_expr(
            CodeCParser::Def_var_with_exprContext *ctx) override {
        string name = ctx->IDENT()->getText();
        CExpression* expr = (CExpression*) visit(ctx->expression());
        CInstrVariable* var = new CInstrVariable("int", name, expr);
        return var;
    }

    virtual antlrcpp::Any visitInstr_expr(CodeCParser::Instr_exprContext *ctx)
            override
            {
        CExpression* expr = (CExpression*) visit(ctx->expression());
        CInstrExpression* instr = new CInstrExpression(expr);
        return (CInstruction*) instr;
    }

    virtual antlrcpp::Any visitVariable(CodeCParser::VariableContext *ctx)
            override
            {
        CExpressionVar* expr = new CExpressionVar(ctx->IDENT()->getText());
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitConst(CodeCParser::ConstContext *ctx) override
  {
    CExpressionInt *expr = new CExpressionInt(
        (int) (long) visit(ctx->intval()));
    return (CExpression *)expr;
  }

  virtual antlrcpp::Any visitIntval_dec(CodeCParser::Intval_decContext *ctx) override
  {
    return (long) (int) std::stoi(ctx->INTDEC()->getText());
  }

  virtual antlrcpp::Any visitIntval_hex(CodeCParser::Intval_hexContext *ctx) override
  {
    return (long) (int) std::stoi(ctx->INTHEX()->getText().c_str()+2,0,16);
  }

  virtual antlrcpp::Any visitIntval_bin(CodeCParser::Intval_binContext *ctx) override
  {
    return (long) (int) std::stoi(ctx->INTBIN()->getText().c_str()+2,0,2);
  }

  virtual antlrcpp::Any visitIntval_oct(CodeCParser::Intval_octContext *ctx) override
  {
    return (long) (int) std::stoi(ctx->INTOCT()->getText().c_str()+1,0,8);
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
        CExpression* lhs = new CExpressionVar(ctx->IDENT()->getText());
        CExpression* rhs = (CExpression*) visit(ctx->expression());

        string op = ctx->OPAFF()->getText();
        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitParenth_expr(
            CodeCParser::Parenth_exprContext *ctx) override
            {
        return visit(ctx->expression());
    }

    virtual antlrcpp::Any visitAdd_expr(CodeCParser::Add_exprContext *ctx)
            override {
        CExpression* lhs = (CExpression*) visit(ctx->expression()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->expression()[1]);

        string op = ctx->OPADD()->getText();
        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitMult_expr(CodeCParser::Mult_exprContext *ctx)
            override {
        CExpression* lhs = (CExpression*) visit(ctx->expression()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->expression()[1]);

        string op = ctx->OPMULT()->getText();
        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    /*
     virtual antlrcpp::Any visitNeg_expr(CodeCParser::Neg_exprContext *ctx) override
     {
     CExpression *rhs = (CExpression*) visit(ctx->expression());
     CExpression *lhs = new CExpressionInt(0);

     CExpressionComposed *expr = new CExpressionComposed(lhs, "-", rhs);
     return (CExpression*) expr;
     }
     */

};

