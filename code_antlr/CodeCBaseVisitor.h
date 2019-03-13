
// Generated from CodeC.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "CodeCVisitor.h"


/**
 * This class provides an empty implementation of CodeCVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CodeCBaseVisitor : public CodeCVisitor {
public:

  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionbody(CodeCParser::FunctionbodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstructions(CodeCParser::InstructionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstruction(CodeCParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVardefinition(CodeCParser::VardefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVardefinitionend(CodeCParser::VardefinitionendContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(CodeCParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstrreturn(CodeCParser::InstrreturnContext *ctx) override {
    return visitChildren(ctx);
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

