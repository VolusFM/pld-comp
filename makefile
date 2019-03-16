
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

OSNAME = LINUX
ifeq ($(OS),Windows_NT)
	OSNAME = WINDOWS
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OSNAME = MAC
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

$(EXE):
	$(ECHO) "building binary"
	$(CPPC) $(COMPFLAGS) $(SOURCEDIR)/*.cpp $(SOURCE_AST)/*.cpp $(OBJS_ANTLR)/*.o $(ANTLRLIBRUNTIME) -o $(BINARY)

$(CLEAN) :
	$(ECHO) "cleaning"
	$(RM) $(RMFLAGS) $(SOURCE_ANTLR)
	$(RM) $(RMFLAGS) $(OBJSDIR)
	$(RM) $(RMFLAGS) $(BINARY)

