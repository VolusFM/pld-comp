GRAM = Grammar
EXE = Compil
CLEAN = clean

INT = CodeC.g4
TOKEN = $(INT:.g4=.tokens) $(INT:.g4=Lexer.tokens)
FIC = $(INT:.g4=Lexer.h) $(INT:.g4=Parser.h) $(INT:.g4=Visitor.h) $(INT:.g4=BaseVisitor.h)
REAL = $(FIC:.h=.cpp)

RM = rm
RMFLAGS = -f
LIBS = core
ECHO = echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp
COMPFLAGS = clang++ -DTRACE -g -std=c++11 -I

ANTLR=/shares/public/tp/ANTLR4-CPP/bin/antlr4
ANTLRRUNTIME=/shares/public/tp/ANTLR4-CPP
ANTLRLIBRUNTIME=ANTLR4-CPP/lib/libantlr4-runtime.a

.PHONY : $(CLEAN)

all : $(GRAM) $(EXE)

$(GRAM) : $(OBJ)
	$(ECHO) "ANLTR4"
	$(ANTLR) $(GRAMFLAGS) $(INT)

$(EXE):
	$(COMPFLAGS) $(ANTLRRUNTIME)/ *.cpp -o exe $(ANTLRLIBRUNTIME)

$(CLEAN) :
	$(ECHO) "Effacement"
	$(RM) $(RMFLAGS) $(EXE) $(FIC) $(LIBS)
	$(RM) $(RMFLAGS) $(EXE) $(REAL) $(LIBS)
	$(RM) $(RMFLAGS) $(EXE) $(TOKEN) $(LIBS)