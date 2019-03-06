#pragma once

#include "antlr4-runtime.h"
#include "../code_antlr/CodeCBaseVisitor.h"


class  Visiteur : public CodeCBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
    return visitChildren(ctx->function());
  }

  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx) override {
    return visitChildren(ctx->functionbody());
  }

  virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionbody(CodeCParser::FunctionbodyContext *ctx) override {
    return (int) stoi(ctx->INTVAL()->getText());
  }

  virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(CodeCParser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }


};
