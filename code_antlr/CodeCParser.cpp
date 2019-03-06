
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
    setState(14);
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
    setState(16);
    functionheader();
    setState(17);
    match(CodeCParser::T__0);
    setState(18);
    functionbody();
    setState(19);
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
    setState(21);
    type();
    setState(22);
    name();
    setState(23);
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

tree::TerminalNode* CodeCParser::FunctionbodyContext::INTVAL() {
  return getToken(CodeCParser::INTVAL, 0);
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
    setState(25);
    match(CodeCParser::T__2);
    setState(26);
    match(CodeCParser::INTVAL);
    setState(27);
    match(CodeCParser::T__3);
   
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
  enterRule(_localctx, 8, CodeCParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    match(CodeCParser::T__4);
   
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
  enterRule(_localctx, 10, CodeCParser::RuleName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(31);
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
  enterRule(_localctx, 12, CodeCParser::RuleParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    match(CodeCParser::T__5);
    setState(34);
    match(CodeCParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> CodeCParser::_decisionToDFA;
atn::PredictionContextCache CodeCParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CodeCParser::_atn;
std::vector<uint16_t> CodeCParser::_serializedATN;

std::vector<std::string> CodeCParser::_ruleNames = {
  "prog", "function", "functionheader", "functionbody", "type", "name", 
  "parameters"
};

std::vector<std::string> CodeCParser::_literalNames = {
  "", "'{'", "'}'", "'return'", "';'", "'int'", "'('", "')'"
};

std::vector<std::string> CodeCParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "INTVAL", "IDENT", "WS"
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
    0x3, 0xc, 0x27, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x2, 0x2, 0x9, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x2, 0x2, 0x2, 0x1f, 0x2, 0x10, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x12, 0x3, 0x2, 0x2, 0x2, 0x6, 0x17, 0x3, 0x2, 0x2, 0x2, 0x8, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x23, 0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 0x5, 0x4, 0x3, 
    0x2, 0x11, 0x3, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x5, 0x6, 0x4, 0x2, 
    0x13, 0x14, 0x7, 0x3, 0x2, 0x2, 0x14, 0x15, 0x5, 0x8, 0x5, 0x2, 0x15, 
    0x16, 0x7, 0x4, 0x2, 0x2, 0x16, 0x5, 0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 
    0x5, 0xa, 0x6, 0x2, 0x18, 0x19, 0x5, 0xc, 0x7, 0x2, 0x19, 0x1a, 0x5, 
    0xe, 0x8, 0x2, 0x1a, 0x7, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0x7, 0x5, 
    0x2, 0x2, 0x1c, 0x1d, 0x7, 0xa, 0x2, 0x2, 0x1d, 0x1e, 0x7, 0x6, 0x2, 
    0x2, 0x1e, 0x9, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x7, 0x2, 0x2, 
    0x20, 0xb, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x7, 0xb, 0x2, 0x2, 0x22, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x8, 0x2, 0x2, 0x24, 0x25, 
    0x7, 0x9, 0x2, 0x2, 0x25, 0xf, 0x3, 0x2, 0x2, 0x2, 0x2, 
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
