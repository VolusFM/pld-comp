GRAM = Grammar
EXE = Compil
CLEAN = clean
ANTLR_TARGET_FOLDER = code_antlr

INT = CodeC.g4
TOKEN = $(ANTLR_TARGET_FOLDER)/$(INT:.g4=.tokens) $(ANTLR_TARGET_FOLDER)/$(INT:.g4=Lexer.tokens)
FIC = $(ANTLR_TARGET_FOLDER)/$(INT:.g4=Lexer.h) $(ANTLR_TARGET_FOLDER)/$(INT:.g4=Parser.h) $(TARGET_FOLDER)/$(INT:.g4=Visitor.h) $(ANTLR_TARGET_FOLDER)/$(INT:.g4=BaseVisitor.h)
INTERP = $(ANTLR_TARGET_FOLDER)/$(INT:.g4=.interp) $(ANTLR_TARGET_FOLDER)/$(INT:.g4=Lexer.interp)
REAL = $(FIC:.h=.cpp)

RM = rm
RMFLAGS = -f
LIBS = core
ECHO = echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp -o $(ANTLR_TARGET_FOLDER)
COMPFLAGS = clang++ -DTRACE -g -std=c++11 -I $(ANTLRRUNTIME)/

ANTLR=/shares/public/tp/ANTLR4-CPP/bin/antlr4
ANTLRRUNTIME=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLRLIBRUNTIME=/shares/public/tp/ANTLR4-CPP/lib/libantlr4-runtime.a

.PHONY : $(CLEAN)

all : $(GRAM) $(EXE)

$(GRAM) : $(OBJ)
	$(ECHO) "ANLTR4"
	$(ANTLR) $(GRAMFLAGS) $(INT)

$(EXE):
	$(COMPFLAGS) *.cpp $(ANTLR_TARGET_FOLDER)/*.cpp -o exe $(ANTLRLIBRUNTIME)

$(CLEAN) :
	$(ECHO) "Effacement"
	$(RM) $(RMFLAGS) $(EXE) $(FIC) $(LIBS)
	$(RM) $(RMFLAGS) $(EXE) $(REAL) $(LIBS)
	$(RM) $(RMFLAGS) $(EXE) $(TOKEN) $(LIBS)
	$(RM) $(RMFLAGS) $(EXE) $(INTERP) $(LIBS)

