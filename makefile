#Télécharger Clang!!! (brew install llvm)

GRAM = Grammar
EXE = Compil
CLEAN = clean
FILE = dirs
TARGET_FOLDER = code_antlr

JAVA=/usr/bin/java
INT = CodeC.g4
FIC = $(INT:.g4=Lexer.h) $(INT:.g4=Parser.h) $(INT:.g4=Visitor.h) $(INT:.g4=BaseVisitor.h)

RM = rm
RMFLAGS = -rf
ECHO = echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp
COMPFLAGS = clang++ -DTRACE -g -std=c++11 -I
CC = g++

ANTLR=ANTLR4-CPP/bin/antlr4
ANTLRRUNTIME=ANTLR4-CPP/antlr4-runtime
ANTLRLIBRUNTIME=ANTLR4-CPP/lib/libantlr4-runtime.a

OSNAME = LINUX_

ifeq ($(OS),Windows_NT)
	#Windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		#Mac
		OSNAME = MAC_
	endif
endif

.PHONY : $(CLEAN)

all : $(FILE) $(GRAM) $(EXE)

$(GRAM) : $(INT)
	$(ECHO) "ANLTR4"
	$(OSNAME)$(ANTLR) $(GRAMFLAGS) -o $(TARGET_FOLDER) $(INT)

$(EXE):
	$(COMPFLAGS) $(OSNAME)$(ANTLRRUNTIME) $(TARGET_FOLDER)/*.cpp -o exe *.cpp $(OSNAME)$(ANTLRLIBRUNTIME)

$(FILE):
	$(ECHO) "Making directory"
	mkdir -p $(TARGET_FOLDER)

$(CLEAN) :
	$(ECHO) "Effacement"
	$(RM) $(RMFLAGS) $(TARGET_FOLDER)