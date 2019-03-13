#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "antlr4-runtime.h"
#include "../code_antlr/CodeCBaseVisitor.h"

class CFunction {
public:
  string to_asm() const;
  
  string name;
  int returnvalue;
};

string CFunction::to_asm() const {
  string code;
  code += name + ":\n";
  code += "  movl $" + std::to_string(returnvalue) + ", %eax\n";
  code += "  ret\n";
  return code;
}

class CProg {
public:
  string to_asm() const;
  
  vector<CFunction> functions;
};

string CProg::to_asm() const {
  string code;
  code += ".text\n";
  code += ".global main\n";
  for (const CFunction& f : functions) {
    code += f.to_asm();
  }
  return code;
}

class Visitor : public CodeCBaseVisitor {
public:

  virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *ctx) override {
    CProg * prog = new CProg();
    prog->functions.push_back(*((CFunction*) visit(ctx->function())));
    return (CProg*) prog;
  }
  
  virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *ctx) override {
    CFunction* func = new CFunction();
    func->name = "main"; // (string) visit(ctx->functionheader());
    func->returnvalue = (int) visit(ctx->functionbody());
    return (CFunction*) func;
  }

  virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *ctx) override {
    return visitChildren(ctx->name());
  }

  virtual antlrcpp::Any visitFunctionbody(CodeCParser::FunctionbodyContext *ctx) override {
    return (int) stoi(ctx->INTVAL()->getText());
  }

  virtual antlrcpp::Any visitType(CodeCParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(CodeCParser::NameContext *ctx) override {
    return string(ctx->IDENT()->getText());
  }

  virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

};

