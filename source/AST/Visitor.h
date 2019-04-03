#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "antlr4-runtime.h"
#include "../antlr/CodeCBaseVisitor.h"

#include "CProg.h"
#include "CFunction.h"
#include "CFunctionHeader.h"
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
        CFunctionHeader* functionHeader = visit(ctx->functionheader());
        CInstructions* block = (CInstructions*) visit(ctx->instructionsblock());
        CFunction* func = new CFunction(functionHeader->name,
                functionHeader->parameters, *block);
        delete functionHeader;
        delete block;
        func->fill_tos();
        return func;
    }

    virtual antlrcpp::Any visitFunctionheader(
            CodeCParser::FunctionheaderContext *ctx) override {
        string s = ctx->IDENT()->getText();
        vector<CParameter>* parameters = (vector<CParameter>*) visit(
                ctx->parameters());
        CFunctionHeader* functionHeader = new CFunctionHeader(s, *parameters);
        delete parameters;
        return functionHeader;
    }

    virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx)
            override {
        vector<CParameter>* parameters = new vector<CParameter>;
        
        for (auto ctx_param : ctx->singleparameter()) {
            parameters->push_back(*((CParameter*) visit(ctx_param)));
        }
        
        return parameters;
    }

    virtual antlrcpp::Any visitSingleparameter(
            CodeCParser::SingleparameterContext *ctx) override {
        CParameter* param = new CParameter(ctx->IDENT()->getText(),
                ctx->type()->getText());
        return param;
    }

    virtual antlrcpp::Any visitInstructionsblock(
            CodeCParser::InstructionsblockContext *ctx) override {
        vector<CInstruction*> instructionsBlock;
        
        for (auto ctx_instr : ctx->instruction()) {
            instructionsBlock.push_back((CInstruction*) visit(ctx_instr));
        }
        
        CInstructions* block = new CInstructions(instructionsBlock);
        
        return block;
    }

    virtual antlrcpp::Any visitReturn(CodeCParser::ReturnContext *ctx)
            override {
        return (CInstruction*) ((CInstrReturn*) visit(ctx->instrreturn()));
    }

    virtual antlrcpp::Any visitReturn_expr(CodeCParser::Return_exprContext *ctx)
            override {
        CExpression* expr = (CExpression*) visit(ctx->rvalue());
        CInstrReturn* instr = new CInstrReturn(expr);
        return instr;
    }

    virtual antlrcpp::Any visitReturn_void(CodeCParser::Return_voidContext *ctx)
            override {
        return new CInstrReturn();
    }

    virtual antlrcpp::Any visitInstr_def(CodeCParser::Instr_defContext *ctx)
            override {
        return (CInstruction*) ((CInstructions*) visit(
                ctx->vardefinition()));
    }

    virtual antlrcpp::Any visitVardefinition(
            CodeCParser::VardefinitionContext *ctx) override {
        string type = ctx->type()->getText();
        vector<CInstruction*> instructionsVariables;
        
        for (auto ctx_varDef : ctx->vardefinitionmult()) {
            CInstrVariable* instrvar = (CInstrVariable*) visit(ctx_varDef);
            instrvar->type = type;
            instructionsVariables.push_back(instrvar);
        }
        
        return new CInstructions(instructionsVariables);
    }
    virtual antlrcpp::Any visitDef_var(CodeCParser::Def_varContext *ctx)
            override {
        string name = ctx->IDENT()->getText();
        return new CInstrVariable(name);
    }

    virtual antlrcpp::Any visitDef_var_with_expr(
            CodeCParser::Def_var_with_exprContext *ctx) override {
        string name = ctx->IDENT()->getText();
        CExpression* expr = (CExpression*) visit(ctx->rvalue());
        return new CInstrVariable(name, expr);
    }
    virtual antlrcpp::Any visitInstr_expr(CodeCParser::Instr_exprContext *ctx)
            override
            {
        CExpression* expr = (CExpression*) visit(ctx->rvalue());
        CInstrExpression* instr = new CInstrExpression(expr);
        return (CInstruction*) instr;
    }

    virtual antlrcpp::Any visitVariable(CodeCParser::VariableContext *ctx)
            override
            {
        return (CExpression *) visit(ctx->lvalue());
    }

    virtual antlrcpp::Any visitConst(CodeCParser::ConstContext *ctx) override
    {
        CExpressionInt *expr = new CExpressionInt(
                (int) (long) visit(ctx->intval()));
        return (CExpression *) expr;
    }

    virtual antlrcpp::Any visitIntval_dec(CodeCParser::Intval_decContext *ctx)
            override
            {
        return (long) (int) std::stoi(ctx->INTDEC()->getText());
    }

    virtual antlrcpp::Any visitIntval_hex(CodeCParser::Intval_hexContext *ctx)
            override
            {
        return (long) (int) std::stoi(ctx->INTHEX()->getText().c_str() + 2, 0,
                16);
    }

    virtual antlrcpp::Any visitIntval_bin(CodeCParser::Intval_binContext *ctx)
            override
            {
        return (long) (int) std::stoi(ctx->INTBIN()->getText().c_str() + 2, 0,
                2);
    }

    virtual antlrcpp::Any visitIntval_oct(CodeCParser::Intval_octContext *ctx)
            override
            {
        return (long) (int) std::stoi(ctx->INTOCT()->getText().c_str() + 1, 0,
                8);
    }

    virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAffect_expr(CodeCParser::Affect_exprContext *ctx)
            override {
        CExpression* lhs = (CExpressionVar*) visit(ctx->lvalue());
        CExpression* rhs = (CExpression*) visit(ctx->rvalue());

        string op = ctx->OPAFF()->getText();
        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitParenth_expr(
            CodeCParser::Parenth_exprContext *ctx) override
            {
        return visit(ctx->rvalue());
    }

    virtual antlrcpp::Any visitAdd_expr(CodeCParser::Add_exprContext *ctx)
            override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op;

        if (ctx->OPADD() != nullptr)
            op = '+';
        else if (ctx->OPSUB() != nullptr)
            op = '-';

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitMult_expr(CodeCParser::Mult_exprContext *ctx)
            override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op;

        if (ctx->OPMULT() != nullptr) {
            op = '*';
        } else if (ctx->OPDIV() != nullptr) {
            op = '/';
        } else if (ctx->OPMOD() != nullptr) {
            op = '%';
        }

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitUnary_expr(CodeCParser::Unary_exprContext *ctx)
            override {
        CExpression *rhs = (CExpression*) visit(ctx->rvalue());
        CExpression *lhs = new CExpressionInt(0);
        string op;

        if (ctx->OPADD() != nullptr)
            op = '+';
        else if (ctx->OPSUB() != nullptr)
            op = '-';

        CExpressionComposed *expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitRelational_expr(
            CodeCParser::Relational_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op;

        if (ctx->OPRELATIONINF() != nullptr)
            op = '<';
        else if (ctx->OPRELATIONINFEQUAL() != nullptr)
            op = "<=";
        else if (ctx->OPRELATIONSUP() != nullptr)
            op = '>';
        else if (ctx->OPRELATIONSUPEQUAL() != nullptr)
            op = ">=";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitEquality_expr(
            CodeCParser::Equality_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op;

        if (ctx->OPEQUALITY() != nullptr)
            op = "==";
        else if (ctx->OPINEQUALITY() != nullptr)
            op = "!=";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitBinary_and_expr(
            CodeCParser::Binary_and_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op = "&";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitBinary_exclusive_or_expr(
            CodeCParser::Binary_exclusive_or_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op = "^";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitBinary_or_expr(
            CodeCParser::Binary_or_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op = "|";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitLogical_and_expr(
            CodeCParser::Logical_and_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op = "&&";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitLogical_or_expr(
            CodeCParser::Logical_or_exprContext *ctx) override {
        CExpression* lhs = (CExpression*) visit(ctx->rvalue()[0]);
        CExpression* rhs = (CExpression*) visit(ctx->rvalue()[1]);
        string op = "||";

        CExpressionComposed* expr = new CExpressionComposed(lhs, op, rhs);
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitLvalue(CodeCParser::LvalueContext *ctx) override {
        CExpressionVar* expr = new CExpressionVar(ctx->IDENT()->getText());
        return (CExpression*) expr;
    }

};

