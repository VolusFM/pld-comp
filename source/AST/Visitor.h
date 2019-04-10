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
#include "CInstrArray.h"
#include "CInstrExpression.h"
#include "CInstrIf.h"
#include "CInstrWhile.h"
#include "CInstrDoWhile.h"
#include "CInstrFor.h"
#include "CFunctionCall.h"

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
        CFunction* func = new CFunction(functionHeader->name, functionHeader->type,
                functionHeader->parameters, *block);
        delete functionHeader;
        delete block;
        func->fill_tos();
        return func;
    }

    virtual antlrcpp::Any visitFunctionheader(
            CodeCParser::FunctionheaderContext *ctx) override {
        string name = ctx->IDENT()->getText();;
        string type;
        if (ctx->type() != nullptr){
            type = ctx->type()->getText();
        }
        else if (ctx->VOID() != nullptr){
            type = ctx->VOID()->getText();
        }
        vector<CParameter>* parameters = (vector<CParameter>*) visit(
                ctx->parameters());
        CFunctionHeader* functionHeader = new CFunctionHeader(name, type, *parameters);
        delete parameters;
        return functionHeader;
    }

    virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx)
            override {
        vector<CParameter>* parameters = new vector<CParameter>;

        for (auto ctx_param : ctx->singleparameter()) {
            CParameter* param = visit(ctx_param);
            parameters->push_back(std::move(*param));
            delete param;
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
        return (CInstruction*) ((CInstructions*) visit(ctx->definition()));
    }

    virtual antlrcpp::Any visitDefinition(CodeCParser::DefinitionContext *ctx)
            override {
        string type = ctx->type()->getText();
        vector<CInstruction*> instructionsVariables;

        for (auto ctx_varDef : ctx->vardefinition()) {
            CInstrVariable* instrVar = (CInstrVariable*) visit(ctx_varDef);
            instrVar->type = type;
            instructionsVariables.push_back(instrVar);
        }
        for (auto ctx_arrayDef : ctx->arraydefinition()) {
            CInstrArray* instrArray = (CInstrArray*) visit(ctx_arrayDef);
            instrArray->type = type;
            instructionsVariables.push_back(instrArray);
        }

        return new CInstructions(instructionsVariables);
    }

    virtual antlrcpp::Any visitDef_var(CodeCParser::Def_varContext *ctx)
            override {
        string name = ctx->IDENT()->getText();
        return new CInstrVariable(name);
    }

    virtual antlrcpp::Any visitIf_block(CodeCParser::If_blockContext *ctx)
            override {
        CExpression* condition = (CExpression*) visit(ctx->ifblock()->expression());
        CInstructions* blockTrue = (CInstructions*) visit(
                ctx->ifblock()->anyinstruction());
        auto ctxElse = ctx->ifblock()->elseblock();
        CInstructions* blockFalse;
        if (ctxElse != nullptr) {
            blockFalse = (CInstructions*) visit(ctxElse->anyinstruction());
        } else {
            blockFalse = new CInstructions();
        }
        CInstrIf* instr = new CInstrIf(condition, *blockTrue, *blockFalse);
        delete blockTrue;
        delete blockFalse;
        return (CInstruction*) instr;
    }

    virtual antlrcpp::Any visitWhile_block(CodeCParser::While_blockContext *ctx)
            override {
        CExpression* condition = (CExpression*) visit(
                ctx->whileblock()->expression());
        CInstructions* blockContent = (CInstructions*) visit(
                ctx->whileblock()->anyinstruction());
        CInstrWhile* instr = new CInstrWhile(condition, *blockContent);
        delete blockContent;
        return (CInstruction*) instr;
    }

    virtual antlrcpp::Any visitDo_while_block(
            CodeCParser::Do_while_blockContext *ctx) override {
        CExpression* condition = (CExpression*) visit(
                ctx->dowhileblock()->expression());
        CInstructions* blockContent = (CInstructions*) visit(
                ctx->dowhileblock()->anyinstruction());
        CInstrDoWhile* instr = new CInstrDoWhile(condition, *blockContent);
        delete blockContent;
        return (CInstruction*) instr;
    }

    //TODO : check and test it
    virtual antlrcpp::Any visitFor_block(CodeCParser::For_blockContext *ctx)
            override {
        CExpression* forStartCondition = nullptr;
        auto ctxForStartCondition =
                ctx->forblock()->forcondition()->forstartcondition();
        if (ctxForStartCondition != nullptr) {
            forStartCondition = (CExpression*) visit(
                        ctxForStartCondition->expression());
        }
        CExpression* forStopCondition = nullptr;
        auto ctxForStopCondition =
                ctx->forblock()->forcondition()->forstopcondition();
        if (ctxForStopCondition != nullptr) {
            forStopCondition = (CExpression*) visit(
                        ctxForStopCondition->expression());
        }
        CExpression* forEvolution = nullptr;
        auto ctxForEvolution =
                ctx->forblock()->forcondition()->forevolution();
        if (ctxForEvolution != nullptr) {
            forEvolution = (CExpression*) visit(
                        ctxForEvolution->expression());
        }

        CInstructions* blockContent = (CInstructions*) visit(
                ctx->forblock()->anyinstruction());
        CInstrFor* instr = new CInstrFor(forStartCondition, forStopCondition, forEvolution, *blockContent);
        delete blockContent;
        return (CInstruction*) instr;
    }

    virtual antlrcpp::Any visitDef_var_with_expr(
            CodeCParser::Def_var_with_exprContext *ctx) override {
        string name = ctx->IDENT()->getText();
        CExpression* expr = (CExpression*) visit(ctx->expression());
        return new CInstrVariable(name, expr);
    }

    virtual antlrcpp::Any visitDef_array(CodeCParser::Def_arrayContext *ctx)
            override {
        string name = ctx->IDENT()->getText();
        int size = (int) (long) visit(ctx->intval());
        return new CInstrArray(name, size);
    }

    virtual antlrcpp::Any visitDef_array_with_expr(
            CodeCParser::Def_array_with_exprContext *ctx) override {
        string name = ctx->IDENT()->getText();
        int size = (int) (long) visit(ctx->intval());

        list<CExpression *> exprs;
        for (auto expressionCtx : ctx->expression()) {
            exprs.push_back((CExpression*) visit(expressionCtx));
        }

        return new CInstrArray(name, size, exprs);
    }

    virtual antlrcpp::Any visitInstr_expr(CodeCParser::Instr_exprContext *ctx)
            override
            {
        CExpression* expr = (CExpression*) visit(ctx->expression());
        CInstrExpression* instr = new CInstrExpression(expr);
        return (CInstruction*) instr;
    }

    virtual antlrcpp::Any visitAnyinstrs(CodeCParser::AnyinstrsContext *ctx)
            override
            {
        return (CInstructions*) visit(ctx->instructionsblock());
    }
    virtual antlrcpp::Any visitAnyinstr(CodeCParser::AnyinstrContext *ctx)
            override
            {
        vector<CInstruction*> instructionsBlock;
        instructionsBlock.push_back((CInstruction*) visit(ctx->instruction()));
        CInstructions* block = new CInstructions(instructionsBlock);
        return block;
    }
    virtual antlrcpp::Any visitNoinstr(CodeCParser::NoinstrContext *ctx)
            override
            {
        vector<CInstruction*> instructionsBlock;
        CInstructions* block = new CInstructions(instructionsBlock);
        return block;
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
        CExpression* lhs = (CExpression*) visit(ctx->lvalue());
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

    virtual antlrcpp::Any visitFunction_call(
            CodeCParser::Function_callContext *ctx) override {
        string functionName = ctx->IDENT()->getText();
        vector<CExpression*>* parameters = new vector<CExpression*>;

        for (auto ctx_param : ctx->parametercall()) {
            parameters->push_back(((CExpression*) visit(ctx_param)));
        }

        CFunctionCall* function = new CFunctionCall(functionName, *parameters);
        delete parameters;
        return (CExpression*) function;
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
        else if (ctx->OPNOT() != nullptr)
            op = '!';

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

    virtual antlrcpp::Any visitSimple_variable(
            CodeCParser::Simple_variableContext *ctx) override {
        CExpressionVar* expr = new CExpressionVar(ctx->IDENT()->getText());
        return (CExpression*) expr;
    }

    virtual antlrcpp::Any visitVariable_in_array(
            CodeCParser::Variable_in_arrayContext *ctx) override {
        CExpressionVarArray* expr = new CExpressionVarArray(
                ctx->IDENT()->getText(), (CExpression*) visit(ctx->rvalue()));
        return (CExpression*) expr;
    }

};

