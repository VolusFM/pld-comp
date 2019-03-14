#Télécharger Clang!!! (brew install llvm)

GRAM = grammar
EXE = compil
BINARY = yottacompilatron9001
CLEAN = clean
OUTPUT_FOLDERS = output_folders
TARGET_FOLDER = code_visitors
ANTLR_TARGET_FOLDER = code_antlr
OUTPUT = output
FILE_CHECKED = $(ANTLR_TARGET_FOLDER)/CodeCBaseVisitor.h

JAVA=/usr/bin/java
INT = CodeC.g4
FIC = $(INT:.g4=Lexer.h) $(INT:.g4=Parser.h) $(INT:.g4=Visitor.h) $(INT:.g4=BaseVisitor.h)

RM = rm
RMFLAGS = -f
ECHO = echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp
COMPFLAGS = -DTRACE -g -std=c++11 -I $(ANTLRRUNTIME)
CPPC = clang++

OSNAME = LINUX

ifeq ($(OS),Windows_NT)
	#Windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		#Mac
		OSNAME = MAC
	endif
endif

ANTLRDIR=ANTLR/$(OSNAME)-CPP
ANTLR = $(ANTLRDIR)/bin/antlr4
ANTLRRUNTIME = $(ANTLRDIR)/antlr4-runtime
ANTLRLIBRUNTIME = $(ANTLRDIR)/lib/libantlr4-runtime.a

#make USE="g++"
#pour compiler sur les ordis du départ n'ayant pas clang++
ifeq ($(USE),g++)
CPPC = g++-6 -Wno-attributes
ANTLRRUNTIME = /shares/public/tp/antlr/antlr4-runtime
ANTLRLIBRUNTIME = /shares/public/tp/antlr/lib/libantlr4-runtime.a
endif

.PHONY : $(CLEAN) $(OUTPUT_FOLDERS)

all : $(OUTPUT_FOLDERS) $(GRAM) $(EXE)

$(GRAM) : $(FILE_CHECKED)

$(FILE_CHECKED) : $(INT)
	$(ECHO) "ANLTR4"
	$(ANTLR) $(GRAMFLAGS) -o $(ANTLR_TARGET_FOLDER) $(INT)
	$(CPPC) $(COMPFLAGS) $(ANTLR_TARGET_FOLDER)/*.cpp -c
	mv *.o $(OUTPUT)

$(EXE):
	$(CPPC) $(COMPFLAGS) $(TARGET_FOLDER)/*.cpp $(OUTPUT)/*.o *.cpp $(ANTLRLIBRUNTIME) -o $(BINARY)

$(OUTPUT_FOLDERS):
	$(ECHO) "Making directory"
	mkdir -p $(ANTLR_TARGET_FOLDER)
	mkdir -p $(OUTPUT)

$(CLEAN) :
	$(ECHO) "Effacement"
	$(RM) $(RMFLAGS) -r $(ANTLR_TARGET_FOLDER)
	$(RM) $(RMFLAGS) -r $(OUTPUT)
	$(RM) $(RMFLAGS) $(BINARY)

