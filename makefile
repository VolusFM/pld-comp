GRAM = Grammar
EXE = Compil
CLEAN = clean

INT = CodeC.g4
TOKEN = Code_genere/$(INT:.g4=.tokens) Code_genere/$(INT:.g4=Lexer.tokens)
FIC = Code_genere/$(INT:.g4=Lexer.h) Code_genere/$(INT:.g4=Parser.h) Code_genere/$(INT:.g4=Visitor.h) Code_genere/$(INT:.g4=BaseVisitor.h)
INTERP = Code_genere/$(INT:.g4=.interp) Code_genere/$(INT:.g4=Lexer.interp)
REAL = $(FIC:.h=.cpp)

RM = rm
RMFLAGS = -f
LIBS = core
ECHO = echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp -o "Code_genere"
COMPFLAGS = clang++ -DTRACE -g -std=c++11 -I

ANTLR=/shares/public/tp/ANTLR4-CPP/bin/antlr4
ANTLRRUNTIME=/shares/public/tp/ANTLR4-CPP

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
	$(RM) $(RMFLAGS) $(EXE) $(INTERP) $(LIBS)
