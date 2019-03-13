
// Generated from CodeC.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "CodeCParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CodeCParser.
 */
class  CodeCVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CodeCParser.
   */
    virtual antlrcpp::Any visitProg(CodeCParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitFunction(CodeCParser::FunctionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionheader(CodeCParser::FunctionheaderContext *context) = 0;

    virtual antlrcpp::Any visitFunctionbody(CodeCParser::FunctionbodyContext *context) = 0;

    virtual antlrcpp::Any visitInstructions(CodeCParser::InstructionsContext *context) = 0;

    virtual antlrcpp::Any visitInstruction(CodeCParser::InstructionContext *context) = 0;

    virtual antlrcpp::Any visitVardefinition(CodeCParser::VardefinitionContext *context) = 0;

    virtual antlrcpp::Any visitVardefinitionend(CodeCParser::VardefinitionendContext *context) = 0;

    virtual antlrcpp::Any visitExpression(CodeCParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitInstrreturn(CodeCParser::InstrreturnContext *context) = 0;

    virtual antlrcpp::Any visitType(CodeCParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitName(CodeCParser::NameContext *context) = 0;

    virtual antlrcpp::Any visitParameters(CodeCParser::ParametersContext *context) = 0;


};

