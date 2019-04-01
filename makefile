
# commands

GRAM = grammar
EXE = compil
CLEAN = clean
OBJECTS = objs

# directories

SOURCEDIR = source
SOURCE_AST = source/AST
SOURCE_ANTLR = source/antlr

OBJSDIR = objects
OBJS_AST = objects/AST
OBJS_ANTLR = objects/antlr

BINARY = yottacompilatron9001

#files

SRC = CExpression.cpp CFunction.cpp CInstrExpression.cpp CInstrReturn.cpp CInstruction.cpp CInstrVariable.cpp CInstrVariableMulti.cpp CProg.cpp
OBJ = $(addprefix $(OBJS_AST)/,$(SRC:.cpp=.o))

# tools and paths

JAVA = /usr/bin/java

GRAM_FILE = CodeC.g4
GRAM_FILECHECK = $(SOURCE_ANTLR)/CodeCBaseVisitor.h
OBJS_FILECHECK = $(OBJS_ANTLR)/CodeCBaseVisitor.o

RM = rm
RMFLAGS = -rf
ECHO = echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp
COMPFLAGS = -DTRACE -g -std=c++11 -I $(ANTLRRUNTIME)
CPPC = clang++

STRIP = strip $(BINARY)

OSNAME = LINUX
ifeq ($(OS),Windows_NT)
	OSNAME = WINDOWS
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OSNAME = MAC
		STRIP = 
	endif
endif

ANTLRDIR=ANTLR/$(OSNAME)-CPP
ANTLR = $(ANTLRDIR)/bin/antlr4
ANTLRRUNTIME = $(ANTLRDIR)/antlr4-runtime
ANTLRLIBRUNTIME = $(ANTLRDIR)/lib/libantlr4-runtime.a

# make USE="g++"
# to compile on IF computers without clang++
ifeq ($(USE),g++)
	CPPC = g++-6 -Wno-attributes
	ANTLRRUNTIME = /shares/public/tp/antlr/antlr4-runtime
	ANTLRLIBRUNTIME = /shares/public/tp/antlr/lib/libantlr4-runtime.a
endif

.PHONY : $(GRAM) $(OBJECTS) $(EXE) $(CLEAN)

all : $(GRAM) $(OBJECTS) $(EXE)

$(OBJS_AST)/CExpression.o : $(SOURCE_AST)/CExpression.h $(SOURCE_AST)/CFunction.h
$(OBJS_AST)/CFunction.o : $(SOURCE_AST)/CFunction.h $(SOURCE_AST)/CInstrVariableMulti.h
$(OBJS_AST)/CInstrExpression.o : $(SOURCE_AST)/CInstrExpression.h
$(OBJS_AST)/CInstrReturn.o : $(SOURCE_AST)/CInstrReturn.h
$(OBJS_AST)/CInstruction.o : $(SOURCE_AST)/CInstruction.h
$(OBJS_AST)/CInstrVariable.o : $(SOURCE_AST)/CInstrVariable.h
$(OBJS_AST)/CInstrVariableMulti.o : $(SOURCE_AST)/CInstrVariableMulti.h
$(OBJS_AST)/CProg.o : $(SOURCE_AST)/CProg.h

$(OBJS_AST):
	mkdir -p $(OBJS_AST)

$(OBJS_AST)/%.o : $(SOURCE_AST)/%.cpp
	mkdir -p $(OBJS_AST)
	$(ECHO) "making $*.o"
	$(CPPC) $(COMPFLAGS) $< -c
	mv *.o $(OBJS_AST)

$(GRAM) : $(GRAM_FILECHECK)
$(GRAM_FILECHECK) : $(GRAM_FILE)
	$(ECHO) "building grammar"
	mkdir -p $(SOURCE_ANTLR)
	$(ANTLR) $(GRAMFLAGS) -o $(SOURCE_ANTLR) $(GRAM_FILE)

$(OBJECTS) : $(OBJS_FILECHECK)
$(OBJS_FILECHECK) : $(GRAM_FILECHECK)
	$(ECHO) "building objects"
	mkdir -p $(OBJSDIR)
	mkdir -p $(OBJS_ANTLR)
	$(CPPC) $(COMPFLAGS) $(SOURCE_ANTLR)/*.cpp -c
	mv *.o $(OBJS_ANTLR)

$(EXE): $(OBJ)
	$(ECHO) "building binary"
	$(CPPC) $(COMPFLAGS) $(SOURCEDIR)/*.cpp $(OBJS_AST)/*.o $(OBJS_ANTLR)/*.o $(ANTLRLIBRUNTIME) -o $(BINARY)
	$(STRIP)

$(CLEAN) :
	$(ECHO) "cleaning"
	$(RM) $(RMFLAGS) *.o
	$(RM) $(RMFLAGS) vgcore.*
	$(RM) $(RMFLAGS) $(SOURCE_ANTLR)
	$(RM) $(RMFLAGS) $(OBJSDIR)
	$(RM) $(RMFLAGS) $(BINARY)

