#pragma once

using namespace std;

#include <string>
#include <vector>

#include "antlr4-runtime.h"
#include "../code_antlr/CodeCBaseVisitor.h"
#include "CProg.h"
#include "CFunction.h"

class Visitor : public CodeCBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
    CProg * prog = new CProg();
    prog->functions.push_back(*((CFunction*) visit(ctx->function())));
    return (CProg*) prog;
  }
  
  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx) override {
    CFunction* func = new CFunction();
    func->name = *((string *) visit(ctx->functionheader()));
    func->returnvalue = (int) visit(ctx->functionbody());
    return (CFunction*) func;
  }

  virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *ctx) override {
    return visit(ctx->name());
  }

  virtual antlrcpp::Any visitFunctionbody(CodeCParser::FunctionbodyContext *ctx) override {
    return (int) stoi(ctx->INTVAL()->getText());
  }

  virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(CodeCParser::NameContext *ctx) override {
    return new string(ctx->IDENT()->getText());
  }

  virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

};
