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

    virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
        CProg prog;

        for (auto ctx_func : ctx->function()) {
            prog.functions.push_back(*((CFunction*) visit(ctx_func)));
        }

        return new CProg(prog);
    }

    virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx)
            override {
        string name = *((string*) visit(ctx->functionheader()));
        CInstructions * block = (CInstructions *) visit(ctx->instructionsbloc());
        CFunction * func = new CFunction(name, block);
        func->fill_tos();
        return func;
    }

    virtual antlrcpp::Any visitFunctionheader(
            CodeCParser::FunctionheaderContext *ctx) override {
        return new string(ctx->IDENT()->getText());
    }

    virtual antlrcpp::Any visitInstructionsbloc(
            CodeCParser::InstructionsblocContext *ctx) override {
        CInstructions* bloc = new CInstructions();
        bloc->instructions = *((vector<CInstruction*>*) visit(
                ctx->instructions()));
        return bloc;
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
        CInstrReturn* instr = new CInstrReturn();
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
    virtual antlrcpp::Any visitDef_var(CodeCParser::Def_varContext *ctx)
            override {
        CInstrVariable* var = new CInstrVariable();
        var->type = "int";
        var->name = ctx->IDENT()->getText();
        return var;
    }
    virtual antlrcpp::Any visitDef_var_with_expr(
            CodeCParser::Def_var_with_exprContext *ctx) override {
        CInstrVariable* var = new CInstrVariable();
        var->type = "int";
        var->name = ctx->IDENT()->getText();
        var->expr = (CExpression*) visit(ctx->expression());
        return var;
    }

    virtual antlrcpp::Any visitInstr_expr(CodeCParser::Instr_exprContext *ctx)
            override {
        CExpression * expr = (CExpression*) visit(ctx->expression());
        CInstrExpression * instr = new CInstrExpression(expr);
        return (CInstruction *) instr;
    }

    virtual antlrcpp::Any visitVariable(CodeCParser::VariableContext *ctx)
            override {
        CExpressionVar * expr = new CExpressionVar(ctx->IDENT()->getText());
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitConst(CodeCParser::ConstContext *ctx) override {
        CExpressionInt * expr = new CExpressionInt(
                (int) stoi(ctx->INTVAL()->getText()));
        return (CExpression *) expr;
    }

    virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx)
            override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAffect_expr(CodeCParser::Affect_exprContext *ctx) override {
    CExpression* rhs = (CExpression*) visit(ctx->expression());
    
    CExpressionVar* lhs = new CExpressionVar(ctx->IDENT()->getText());
    lhs->variable = ctx->IDENT()->getText();

    CExpressionComposed * expr = new CExpressionComposed(
                (CExpression *) rhs, ctx->OPAFF()->getText(), (CExpression *) lhs);
    return (CExpression*) expr;
  }

  virtual antlrcpp::Any visitParenth_expr(CodeCParser::Parenth_exprContext *ctx) override {
    CExpression* rhs = (CExpression*) visit(ctx->expression());

    return rhs;
  }

  virtual antlrcpp::Any visitAdd_expr(CodeCParser::Add_exprContext *ctx) override {
    CExpression* rhs = (CExpression*) visit(ctx->expression()[1]);
    CExpression* lhs = (CExpression*) visit(ctx->expression()[0]);

    CExpressionComposed * expr = new CExpressionComposed(
                (CExpression *) rhs, ctx->OPADD()->getText(), (CExpression *) lhs);
    return (CExpression*) expr;
  }

   virtual antlrcpp::Any visitMult_expr(CodeCParser::Mult_exprContext *ctx) override {
    CExpression* rhs = (CExpression*) visit(ctx->expression()[1]);
    CExpression* lhs = (CExpression*) visit(ctx->expression()[0]);

    CExpressionComposed * expr = new CExpressionComposed(
                (CExpression *) rhs, ctx->OPMULT()->getText(), (CExpression *) lhs);
    return (CExpression*) expr;
  }

};
