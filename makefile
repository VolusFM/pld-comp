#Télécharger Clang!!! (brew install llvm)

GRAM = grammar
EXE = compil
BINARY = yottacompilatron9001
CLEAN = clean
FILE = dirs
TARGET_FOLDER = code_visitors
ANTLR_TARGET_FOLDER = code_antlr
FILE_CHECKED = $(ANTLR_TARGET_FOLDER)/CodeCBaseVisitor.h

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

$(GRAM) : $(FILE_CHECKED)

$(FILE_CHECKED) : $(INT)
	$(ECHO) "ANLTR4"
	$(OSNAME)$(ANTLR) $(GRAMFLAGS) -o $(ANTLR_TARGET_FOLDER) $(INT)
	$(COMPFLAGS) $(OSNAME)$(ANTLRRUNTIME) $(ANTLR_TARGET_FOLDER)/*.cpp -c

$(EXE):
	$(COMPFLAGS) $(OSNAME)$(ANTLRRUNTIME) $(TARGET_FOLDER)/*.cpp *.o *.cpp -o $(BINARY) $(OSNAME)$(ANTLRLIBRUNTIME)

$(FILE):
	$(ECHO) "Making directory"
	mkdir -p $(ANTLR_TARGET_FOLDER)

$(CLEAN) :
	$(ECHO) "Effacement"
	$(RM) $(RMFLAGS) $(ANTLR_TARGET_FOLDER)
	$(RM) $(BINARY)

