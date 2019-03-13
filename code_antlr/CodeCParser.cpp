
// Generated from CodeC.g4 by ANTLR 4.7.1


#include "CodeCVisitor.h"

#include "CodeCParser.h"


using namespace antlrcpp;
using namespace antlr4;

CodeCParser::CodeCParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CodeCParser::~CodeCParser() {
  delete _interpreter;
}

std::string CodeCParser::getGrammarFileName() const {
  return "CodeC.g4";
}

const std::vector<std::string>& CodeCParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CodeCParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

CodeCParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::FunctionContext* CodeCParser::ProgContext::function() {
  return getRuleContext<CodeCParser::FunctionContext>(0);
}


size_t CodeCParser::ProgContext::getRuleIndex() const {
  return CodeCParser::RuleProg;
}

antlrcpp::Any CodeCParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::ProgContext* CodeCParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, CodeCParser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(26);
    function();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

CodeCParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::FunctionheaderContext* CodeCParser::FunctionContext::functionheader() {
  return getRuleContext<CodeCParser::FunctionheaderContext>(0);
}

CodeCParser::FunctionbodyContext* CodeCParser::FunctionContext::functionbody() {
  return getRuleContext<CodeCParser::FunctionbodyContext>(0);
}


size_t CodeCParser::FunctionContext::getRuleIndex() const {
  return CodeCParser::RuleFunction;
}

antlrcpp::Any CodeCParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::FunctionContext* CodeCParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 2, CodeCParser::RuleFunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    functionheader();
    setState(29);
    match(CodeCParser::T__0);
    setState(30);
    functionbody();
    setState(31);
    match(CodeCParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionheaderContext ------------------------------------------------------------------

CodeCParser::FunctionheaderContext::FunctionheaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::TypeContext* CodeCParser::FunctionheaderContext::type() {
  return getRuleContext<CodeCParser::TypeContext>(0);
}

CodeCParser::NameContext* CodeCParser::FunctionheaderContext::name() {
  return getRuleContext<CodeCParser::NameContext>(0);
}

CodeCParser::ParametersContext* CodeCParser::FunctionheaderContext::parameters() {
  return getRuleContext<CodeCParser::ParametersContext>(0);
}


size_t CodeCParser::FunctionheaderContext::getRuleIndex() const {
  return CodeCParser::RuleFunctionheader;
}

antlrcpp::Any CodeCParser::FunctionheaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitFunctionheader(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::FunctionheaderContext* CodeCParser::functionheader() {
  FunctionheaderContext *_localctx = _tracker.createInstance<FunctionheaderContext>(_ctx, getState());
  enterRule(_localctx, 4, CodeCParser::RuleFunctionheader);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    type();
    setState(34);
    name();
    setState(35);
    parameters();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionbodyContext ------------------------------------------------------------------

CodeCParser::FunctionbodyContext::FunctionbodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::InstructionsContext* CodeCParser::FunctionbodyContext::instructions() {
  return getRuleContext<CodeCParser::InstructionsContext>(0);
}


size_t CodeCParser::FunctionbodyContext::getRuleIndex() const {
  return CodeCParser::RuleFunctionbody;
}

antlrcpp::Any CodeCParser::FunctionbodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitFunctionbody(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::FunctionbodyContext* CodeCParser::functionbody() {
  FunctionbodyContext *_localctx = _tracker.createInstance<FunctionbodyContext>(_ctx, getState());
  enterRule(_localctx, 6, CodeCParser::RuleFunctionbody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    instructions(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstructionsContext ------------------------------------------------------------------

CodeCParser::InstructionsContext::InstructionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::InstructionContext* CodeCParser::InstructionsContext::instruction() {
  return getRuleContext<CodeCParser::InstructionContext>(0);
}

CodeCParser::InstructionsContext* CodeCParser::InstructionsContext::instructions() {
  return getRuleContext<CodeCParser::InstructionsContext>(0);
}


size_t CodeCParser::InstructionsContext::getRuleIndex() const {
  return CodeCParser::RuleInstructions;
}

antlrcpp::Any CodeCParser::InstructionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitInstructions(this);
  else
    return visitor->visitChildren(this);
}


CodeCParser::InstructionsContext* CodeCParser::instructions() {
   return instructions(0);
}

CodeCParser::InstructionsContext* CodeCParser::instructions(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CodeCParser::InstructionsContext *_localctx = _tracker.createInstance<InstructionsContext>(_ctx, parentState);
  CodeCParser::InstructionsContext *previousContext = _localctx;
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, CodeCParser::RuleInstructions, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(40);
    instruction();
    _ctx->stop = _input->LT(-1);
    setState(46);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<InstructionsContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleInstructions);
        setState(42);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(43);
        instruction(); 
      }
      setState(48);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- InstructionContext ------------------------------------------------------------------

CodeCParser::InstructionContext::InstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::InstrreturnContext* CodeCParser::InstructionContext::instrreturn() {
  return getRuleContext<CodeCParser::InstrreturnContext>(0);
}

CodeCParser::VardefinitionContext* CodeCParser::InstructionContext::vardefinition() {
  return getRuleContext<CodeCParser::VardefinitionContext>(0);
}

CodeCParser::ExpressionContext* CodeCParser::InstructionContext::expression() {
  return getRuleContext<CodeCParser::ExpressionContext>(0);
}


size_t CodeCParser::InstructionContext::getRuleIndex() const {
  return CodeCParser::RuleInstruction;
}

antlrcpp::Any CodeCParser::InstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitInstruction(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::InstructionContext* CodeCParser::instruction() {
  InstructionContext *_localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
  enterRule(_localctx, 10, CodeCParser::RuleInstruction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeCParser::T__4: {
        setState(49);
        instrreturn();
        break;
      }

      case CodeCParser::T__5: {
        setState(50);
        vardefinition();
        break;
      }

      case CodeCParser::INTVAL:
      case CodeCParser::IDENT: {
        setState(51);
        expression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(54);
    match(CodeCParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardefinitionContext ------------------------------------------------------------------

CodeCParser::VardefinitionContext::VardefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::TypeContext* CodeCParser::VardefinitionContext::type() {
  return getRuleContext<CodeCParser::TypeContext>(0);
}

tree::TerminalNode* CodeCParser::VardefinitionContext::IDENT() {
  return getToken(CodeCParser::IDENT, 0);
}

CodeCParser::VardefinitionendContext* CodeCParser::VardefinitionContext::vardefinitionend() {
  return getRuleContext<CodeCParser::VardefinitionendContext>(0);
}


size_t CodeCParser::VardefinitionContext::getRuleIndex() const {
  return CodeCParser::RuleVardefinition;
}

antlrcpp::Any CodeCParser::VardefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitVardefinition(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::VardefinitionContext* CodeCParser::vardefinition() {
  VardefinitionContext *_localctx = _tracker.createInstance<VardefinitionContext>(_ctx, getState());
  enterRule(_localctx, 12, CodeCParser::RuleVardefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    type();
    setState(57);
    match(CodeCParser::IDENT);
    setState(58);
    vardefinitionend();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardefinitionendContext ------------------------------------------------------------------

CodeCParser::VardefinitionendContext::VardefinitionendContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeCParser::ExpressionContext* CodeCParser::VardefinitionendContext::expression() {
  return getRuleContext<CodeCParser::ExpressionContext>(0);
}


size_t CodeCParser::VardefinitionendContext::getRuleIndex() const {
  return CodeCParser::RuleVardefinitionend;
}

antlrcpp::Any CodeCParser::VardefinitionendContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitVardefinitionend(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::VardefinitionendContext* CodeCParser::vardefinitionend() {
  VardefinitionendContext *_localctx = _tracker.createInstance<VardefinitionendContext>(_ctx, getState());
  enterRule(_localctx, 14, CodeCParser::RuleVardefinitionend);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(63);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeCParser::T__2: {
        enterOuterAlt(_localctx, 1);

        break;
      }

      case CodeCParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(61);
        match(CodeCParser::T__3);
        setState(62);
        expression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CodeCParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeCParser::ExpressionContext::INTVAL() {
  return getToken(CodeCParser::INTVAL, 0);
}

tree::TerminalNode* CodeCParser::ExpressionContext::IDENT() {
  return getToken(CodeCParser::IDENT, 0);
}


size_t CodeCParser::ExpressionContext::getRuleIndex() const {
  return CodeCParser::RuleExpression;
}

antlrcpp::Any CodeCParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::ExpressionContext* CodeCParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, CodeCParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(69);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeCParser::INTVAL: {
        enterOuterAlt(_localctx, 1);
        setState(65);
        match(CodeCParser::INTVAL);
        break;
      }

      case CodeCParser::IDENT: {
        enterOuterAlt(_localctx, 2);
        setState(66);
        match(CodeCParser::IDENT);
        setState(67);
        match(CodeCParser::T__3);
        setState(68);
        match(CodeCParser::INTVAL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstrreturnContext ------------------------------------------------------------------

CodeCParser::InstrreturnContext::InstrreturnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeCParser::InstrreturnContext::INTVAL() {
  return getToken(CodeCParser::INTVAL, 0);
}


size_t CodeCParser::InstrreturnContext::getRuleIndex() const {
  return CodeCParser::RuleInstrreturn;
}

antlrcpp::Any CodeCParser::InstrreturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitInstrreturn(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::InstrreturnContext* CodeCParser::instrreturn() {
  InstrreturnContext *_localctx = _tracker.createInstance<InstrreturnContext>(_ctx, getState());
  enterRule(_localctx, 18, CodeCParser::RuleInstrreturn);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(CodeCParser::T__4);
    setState(72);
    match(CodeCParser::INTVAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

CodeCParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CodeCParser::TypeContext::getRuleIndex() const {
  return CodeCParser::RuleType;
}

antlrcpp::Any CodeCParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::TypeContext* CodeCParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 20, CodeCParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(CodeCParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameContext ------------------------------------------------------------------

CodeCParser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeCParser::NameContext::IDENT() {
  return getToken(CodeCParser::IDENT, 0);
}


size_t CodeCParser::NameContext::getRuleIndex() const {
  return CodeCParser::RuleName;
}

antlrcpp::Any CodeCParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::NameContext* CodeCParser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 22, CodeCParser::RuleName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(CodeCParser::IDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

CodeCParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CodeCParser::ParametersContext::getRuleIndex() const {
  return CodeCParser::RuleParameters;
}

antlrcpp::Any CodeCParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeCVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

CodeCParser::ParametersContext* CodeCParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 24, CodeCParser::RuleParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(CodeCParser::T__6);
    setState(79);
    match(CodeCParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CodeCParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 4: return instructionsSempred(dynamic_cast<InstructionsContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CodeCParser::instructionsSempred(InstructionsContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CodeCParser::_decisionToDFA;
atn::PredictionContextCache CodeCParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CodeCParser::_atn;
std::vector<uint16_t> CodeCParser::_serializedATN;

std::vector<std::string> CodeCParser::_ruleNames = {
  "prog", "function", "functionheader", "functionbody", "instructions", 
  "instruction", "vardefinition", "vardefinitionend", "expression", "instrreturn", 
  "type", "name", "parameters"
};

std::vector<std::string> CodeCParser::_literalNames = {
  "", "'{'", "'}'", "';'", "'='", "'return'", "'int'", "'('", "')'"
};

std::vector<std::string> CodeCParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "INTVAL", "IDENT", "WS"
};

dfa::Vocabulary CodeCParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CodeCParser::_tokenNames;

CodeCParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xd, 0x54, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x2f, 0xa, 0x6, 0xc, 0x6, 
    0xe, 0x6, 0x32, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x37, 
    0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x42, 0xa, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x48, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x2, 0x3, 0xa, 0xf, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x2, 0x2, 0x2, 0x4b, 0x2, 0x1c, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x6, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x27, 0x3, 0x2, 0x2, 0x2, 0xa, 0x29, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x36, 0x3, 0x2, 0x2, 0x2, 0xe, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x12, 0x47, 0x3, 0x2, 0x2, 0x2, 0x14, 0x49, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x18, 0x4e, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x50, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x5, 0x4, 
    0x3, 0x2, 0x1d, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x5, 0x6, 0x4, 
    0x2, 0x1f, 0x20, 0x7, 0x3, 0x2, 0x2, 0x20, 0x21, 0x5, 0x8, 0x5, 0x2, 
    0x21, 0x22, 0x7, 0x4, 0x2, 0x2, 0x22, 0x5, 0x3, 0x2, 0x2, 0x2, 0x23, 
    0x24, 0x5, 0x16, 0xc, 0x2, 0x24, 0x25, 0x5, 0x18, 0xd, 0x2, 0x25, 0x26, 
    0x5, 0x1a, 0xe, 0x2, 0x26, 0x7, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x5, 
    0xa, 0x6, 0x2, 0x28, 0x9, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x8, 0x6, 
    0x1, 0x2, 0x2a, 0x2b, 0x5, 0xc, 0x7, 0x2, 0x2b, 0x30, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x2d, 0xc, 0x4, 0x2, 0x2, 0x2d, 0x2f, 0x5, 0xc, 0x7, 0x2, 
    0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x32, 0x3, 0x2, 0x2, 0x2, 0x30, 
    0x2e, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 0x31, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x33, 0x37, 0x5, 
    0x14, 0xb, 0x2, 0x34, 0x37, 0x5, 0xe, 0x8, 0x2, 0x35, 0x37, 0x5, 0x12, 
    0xa, 0x2, 0x36, 0x33, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x39, 0x7, 0x5, 0x2, 0x2, 0x39, 0xd, 0x3, 0x2, 0x2, 0x2, 0x3a, 
    0x3b, 0x5, 0x16, 0xc, 0x2, 0x3b, 0x3c, 0x7, 0xc, 0x2, 0x2, 0x3c, 0x3d, 
    0x5, 0x10, 0x9, 0x2, 0x3d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x42, 0x3, 
    0x2, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x6, 0x2, 0x2, 0x40, 0x42, 0x5, 0x12, 
    0xa, 0x2, 0x41, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x42, 0x11, 0x3, 0x2, 0x2, 0x2, 0x43, 0x48, 0x7, 0xb, 0x2, 0x2, 
    0x44, 0x45, 0x7, 0xc, 0x2, 0x2, 0x45, 0x46, 0x7, 0x6, 0x2, 0x2, 0x46, 
    0x48, 0x7, 0xb, 0x2, 0x2, 0x47, 0x43, 0x3, 0x2, 0x2, 0x2, 0x47, 0x44, 
    0x3, 0x2, 0x2, 0x2, 0x48, 0x13, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x7, 
    0x7, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0xb, 0x2, 0x2, 0x4b, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0x4c, 0x4d, 0x7, 0x8, 0x2, 0x2, 0x4d, 0x17, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x4f, 0x7, 0xc, 0x2, 0x2, 0x4f, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x51, 0x7, 0x9, 0x2, 0x2, 0x51, 0x52, 0x7, 0xa, 0x2, 0x2, 0x52, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0x6, 0x30, 0x36, 0x41, 0x47, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CodeCParser::Initializer CodeCParser::_init;
