// Generated from /Users/Martin/Dropbox/cours/4A/PLD_COMP/pld-comp/CodeC.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CodeCParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, INTVAL=9, 
		IDENT=10, OPMULT=11, OPADD=12, OPAFF=13, WS=14;
	public static final int
		RULE_prog = 0, RULE_function = 1, RULE_functionheader = 2, RULE_instructionsbloc = 3, 
		RULE_instructions = 4, RULE_instruction = 5, RULE_vardefinition = 6, RULE_expression = 7, 
		RULE_instrreturn = 8, RULE_type = 9, RULE_parameters = 10;
	public static final String[] ruleNames = {
		"prog", "function", "functionheader", "instructionsbloc", "instructions", 
		"instruction", "vardefinition", "expression", "instrreturn", "type", "parameters"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'{'", "'}'", "';'", "'='", "'('", "')'", "'return'", "'int'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, "INTVAL", "IDENT", 
		"OPMULT", "OPADD", "OPAFF", "WS"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "CodeC.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CodeCParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class ProgContext extends ParserRuleContext {
		public List<FunctionContext> function() {
			return getRuleContexts(FunctionContext.class);
		}
		public FunctionContext function(int i) {
			return getRuleContext(FunctionContext.class,i);
		}
		public ProgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prog; }
	}

	public final ProgContext prog() throws RecognitionException {
		ProgContext _localctx = new ProgContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_prog);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(25);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__7) {
				{
				{
				setState(22);
				function();
				}
				}
				setState(27);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionContext extends ParserRuleContext {
		public FunctionheaderContext functionheader() {
			return getRuleContext(FunctionheaderContext.class,0);
		}
		public InstructionsblocContext instructionsbloc() {
			return getRuleContext(InstructionsblocContext.class,0);
		}
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_function);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(28);
			functionheader();
			setState(29);
			instructionsbloc();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionheaderContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CodeCParser.IDENT, 0); }
		public ParametersContext parameters() {
			return getRuleContext(ParametersContext.class,0);
		}
		public FunctionheaderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionheader; }
	}

	public final FunctionheaderContext functionheader() throws RecognitionException {
		FunctionheaderContext _localctx = new FunctionheaderContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_functionheader);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(31);
			type();
			setState(32);
			match(IDENT);
			setState(33);
			parameters();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InstructionsblocContext extends ParserRuleContext {
		public InstructionsContext instructions() {
			return getRuleContext(InstructionsContext.class,0);
		}
		public InstructionsblocContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_instructionsbloc; }
	}

	public final InstructionsblocContext instructionsbloc() throws RecognitionException {
		InstructionsblocContext _localctx = new InstructionsblocContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_instructionsbloc);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(35);
			match(T__0);
			setState(36);
			instructions();
			setState(37);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InstructionsContext extends ParserRuleContext {
		public List<InstructionContext> instruction() {
			return getRuleContexts(InstructionContext.class);
		}
		public InstructionContext instruction(int i) {
			return getRuleContext(InstructionContext.class,i);
		}
		public InstructionsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_instructions; }
	}

	public final InstructionsContext instructions() throws RecognitionException {
		InstructionsContext _localctx = new InstructionsContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_instructions);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(42);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__4) | (1L << T__6) | (1L << T__7) | (1L << INTVAL) | (1L << IDENT))) != 0)) {
				{
				{
				setState(39);
				instruction();
				}
				}
				setState(44);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InstructionContext extends ParserRuleContext {
		public InstructionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_instruction; }
	 
		public InstructionContext() { }
		public void copyFrom(InstructionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Instr_defContext extends InstructionContext {
		public VardefinitionContext vardefinition() {
			return getRuleContext(VardefinitionContext.class,0);
		}
		public Instr_defContext(InstructionContext ctx) { copyFrom(ctx); }
	}
	public static class Instr_exprContext extends InstructionContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Instr_exprContext(InstructionContext ctx) { copyFrom(ctx); }
	}
	public static class ReturnContext extends InstructionContext {
		public InstrreturnContext instrreturn() {
			return getRuleContext(InstrreturnContext.class,0);
		}
		public ReturnContext(InstructionContext ctx) { copyFrom(ctx); }
	}

	public final InstructionContext instruction() throws RecognitionException {
		InstructionContext _localctx = new InstructionContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_instruction);
		try {
			setState(54);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__6:
				_localctx = new ReturnContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(45);
				instrreturn();
				setState(46);
				match(T__2);
				}
				break;
			case T__7:
				_localctx = new Instr_defContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(48);
				vardefinition();
				setState(49);
				match(T__2);
				}
				break;
			case T__4:
			case INTVAL:
			case IDENT:
				_localctx = new Instr_exprContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(51);
				expression(0);
				setState(52);
				match(T__2);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VardefinitionContext extends ParserRuleContext {
		public VardefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_vardefinition; }
	 
		public VardefinitionContext() { }
		public void copyFrom(VardefinitionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Def_var_with_exprContext extends VardefinitionContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CodeCParser.IDENT, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Def_var_with_exprContext(VardefinitionContext ctx) { copyFrom(ctx); }
	}
	public static class Def_varContext extends VardefinitionContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENT() { return getToken(CodeCParser.IDENT, 0); }
		public Def_varContext(VardefinitionContext ctx) { copyFrom(ctx); }
	}

	public final VardefinitionContext vardefinition() throws RecognitionException {
		VardefinitionContext _localctx = new VardefinitionContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_vardefinition);
		try {
			setState(64);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				_localctx = new Def_varContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(56);
				type();
				setState(57);
				match(IDENT);
				}
				break;
			case 2:
				_localctx = new Def_var_with_exprContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(59);
				type();
				setState(60);
				match(IDENT);
				setState(61);
				match(T__3);
				setState(62);
				expression(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	 
		public ExpressionContext() { }
		public void copyFrom(ExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Add_exprContext extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode OPADD() { return getToken(CodeCParser.OPADD, 0); }
		public Add_exprContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Affect_exprContext extends ExpressionContext {
		public TerminalNode IDENT() { return getToken(CodeCParser.IDENT, 0); }
		public TerminalNode OPAFF() { return getToken(CodeCParser.OPAFF, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Affect_exprContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class ConstContext extends ExpressionContext {
		public TerminalNode INTVAL() { return getToken(CodeCParser.INTVAL, 0); }
		public ConstContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class VariableContext extends ExpressionContext {
		public TerminalNode IDENT() { return getToken(CodeCParser.IDENT, 0); }
		public VariableContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Parenth_exprContext extends ExpressionContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Parenth_exprContext(ExpressionContext ctx) { copyFrom(ctx); }
	}
	public static class Mult_exprContext extends ExpressionContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode OPMULT() { return getToken(CodeCParser.OPMULT, 0); }
		public Mult_exprContext(ExpressionContext ctx) { copyFrom(ctx); }
	}

	public final ExpressionContext expression() throws RecognitionException {
		return expression(0);
	}

	private ExpressionContext expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpressionContext _localctx = new ExpressionContext(_ctx, _parentState);
		ExpressionContext _prevctx = _localctx;
		int _startState = 14;
		enterRecursionRule(_localctx, 14, RULE_expression, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(76);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				_localctx = new Affect_exprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(67);
				match(IDENT);
				setState(68);
				match(OPAFF);
				setState(69);
				expression(4);
				}
				break;
			case 2:
				{
				_localctx = new Parenth_exprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(70);
				match(T__4);
				setState(71);
				expression(0);
				setState(72);
				match(T__5);
				}
				break;
			case 3:
				{
				_localctx = new ConstContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(74);
				match(INTVAL);
				}
				break;
			case 4:
				{
				_localctx = new VariableContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(75);
				match(IDENT);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(86);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(84);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
					case 1:
						{
						_localctx = new Mult_exprContext(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(78);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(79);
						match(OPMULT);
						setState(80);
						expression(7);
						}
						break;
					case 2:
						{
						_localctx = new Add_exprContext(new ExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(81);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(82);
						match(OPADD);
						setState(83);
						expression(6);
						}
						break;
					}
					} 
				}
				setState(88);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class InstrreturnContext extends ParserRuleContext {
		public InstrreturnContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_instrreturn; }
	 
		public InstrreturnContext() { }
		public void copyFrom(InstrreturnContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class Return_exprContext extends InstrreturnContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Return_exprContext(InstrreturnContext ctx) { copyFrom(ctx); }
	}
	public static class Return_voidContext extends InstrreturnContext {
		public Return_voidContext(InstrreturnContext ctx) { copyFrom(ctx); }
	}

	public final InstrreturnContext instrreturn() throws RecognitionException {
		InstrreturnContext _localctx = new InstrreturnContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_instrreturn);
		try {
			setState(92);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				_localctx = new Return_exprContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(89);
				match(T__6);
				setState(90);
				expression(0);
				}
				break;
			case 2:
				_localctx = new Return_voidContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(91);
				match(T__6);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TypeContext extends ParserRuleContext {
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(94);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParametersContext extends ParserRuleContext {
		public ParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameters; }
	}

	public final ParametersContext parameters() throws RecognitionException {
		ParametersContext _localctx = new ParametersContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_parameters);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(96);
			match(T__4);
			setState(97);
			match(T__5);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 7:
			return expression_sempred((ExpressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expression_sempred(ExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 6);
		case 1:
			return precpred(_ctx, 5);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\20f\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t\13\4"+
		"\f\t\f\3\2\7\2\32\n\2\f\2\16\2\35\13\2\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\5"+
		"\3\5\3\5\3\5\3\6\7\6+\n\6\f\6\16\6.\13\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3"+
		"\7\3\7\5\79\n\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\5\bC\n\b\3\t\3\t\3\t\3"+
		"\t\3\t\3\t\3\t\3\t\3\t\3\t\5\tO\n\t\3\t\3\t\3\t\3\t\3\t\3\t\7\tW\n\t\f"+
		"\t\16\tZ\13\t\3\n\3\n\3\n\5\n_\n\n\3\13\3\13\3\f\3\f\3\f\3\f\2\3\20\r"+
		"\2\4\6\b\n\f\16\20\22\24\26\2\2\2e\2\33\3\2\2\2\4\36\3\2\2\2\6!\3\2\2"+
		"\2\b%\3\2\2\2\n,\3\2\2\2\f8\3\2\2\2\16B\3\2\2\2\20N\3\2\2\2\22^\3\2\2"+
		"\2\24`\3\2\2\2\26b\3\2\2\2\30\32\5\4\3\2\31\30\3\2\2\2\32\35\3\2\2\2\33"+
		"\31\3\2\2\2\33\34\3\2\2\2\34\3\3\2\2\2\35\33\3\2\2\2\36\37\5\6\4\2\37"+
		" \5\b\5\2 \5\3\2\2\2!\"\5\24\13\2\"#\7\f\2\2#$\5\26\f\2$\7\3\2\2\2%&\7"+
		"\3\2\2&\'\5\n\6\2\'(\7\4\2\2(\t\3\2\2\2)+\5\f\7\2*)\3\2\2\2+.\3\2\2\2"+
		",*\3\2\2\2,-\3\2\2\2-\13\3\2\2\2.,\3\2\2\2/\60\5\22\n\2\60\61\7\5\2\2"+
		"\619\3\2\2\2\62\63\5\16\b\2\63\64\7\5\2\2\649\3\2\2\2\65\66\5\20\t\2\66"+
		"\67\7\5\2\2\679\3\2\2\28/\3\2\2\28\62\3\2\2\28\65\3\2\2\29\r\3\2\2\2:"+
		";\5\24\13\2;<\7\f\2\2<C\3\2\2\2=>\5\24\13\2>?\7\f\2\2?@\7\6\2\2@A\5\20"+
		"\t\2AC\3\2\2\2B:\3\2\2\2B=\3\2\2\2C\17\3\2\2\2DE\b\t\1\2EF\7\f\2\2FG\7"+
		"\17\2\2GO\5\20\t\6HI\7\7\2\2IJ\5\20\t\2JK\7\b\2\2KO\3\2\2\2LO\7\13\2\2"+
		"MO\7\f\2\2ND\3\2\2\2NH\3\2\2\2NL\3\2\2\2NM\3\2\2\2OX\3\2\2\2PQ\f\b\2\2"+
		"QR\7\r\2\2RW\5\20\t\tST\f\7\2\2TU\7\16\2\2UW\5\20\t\bVP\3\2\2\2VS\3\2"+
		"\2\2WZ\3\2\2\2XV\3\2\2\2XY\3\2\2\2Y\21\3\2\2\2ZX\3\2\2\2[\\\7\t\2\2\\"+
		"_\5\20\t\2]_\7\t\2\2^[\3\2\2\2^]\3\2\2\2_\23\3\2\2\2`a\7\n\2\2a\25\3\2"+
		"\2\2bc\7\7\2\2cd\7\b\2\2d\27\3\2\2\2\n\33,8BNVX^";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}