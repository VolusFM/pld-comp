
# commands

GRAM = grammar
OBJECTS = objs
EXE = compile
CLEAN = clean

# directories

SOURCEDIR = source
SOURCE_ANTLR = source/antlr
SOURCE_AST = source/AST
SOURCE_IR = source/IR

OBJSDIR = objects
OBJS_ANTLR = objects/antlr
#OBJS_AST = objects/AST
#OBJS_IR = objects/IR

BINARY = yottacompilatron9001

# tools and paths

JAVA = /usr/bin/java

GRAM_FILE = CodeC.g4
GRAM_FILECHECK = $(SOURCE_ANTLR)/CodeCBaseVisitor.h
OBJS_FILECHECK = $(OBJS_ANTLR)/CodeCBaseVisitor.o

RM = rm
RMFLAGS = -rf
ECHO = @echo
GRAMFLAGS = -visitor -no-listener -Dlanguage=Cpp
COMPFLAGS = -DTRACE -g -std=c++11 -I $(ANTLRRUNTIME)
CPPC = clang++

OSNAME:=LINUX
ifeq ($(OS),Windows_NT)
	OSNAME:=WINDOWS
else
	UNAME_S:=$(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		OSNAME:=MAC
	endif
endif

POSTTREATMENT=@strip $(BINARY)
ifeq ($(OSNAME),MAC)
    POSTTREATMENT=
endif

ANTLRDIR=ANTLR/$(OSNAME)-CPP
ANTLR=$(ANTLRDIR)/bin/antlr4
ANTLRRUNTIME=$(ANTLRDIR)/antlr4-runtime
ANTLRLIBRUNTIME=$(ANTLRDIR)/lib/libantlr4-runtime.a

# make USE="g++"
# to compile on IF computers
# without clang++ and
# without ANTLR/ folder
ifeq ($(USE),g++)
CPPC=g++-6 -Wno-attributes
ANTLR:=$(ANTLRDIR)/bin/antlr4
ANTLRDIR=/shares/public/tp/antlr
endif

.PHONY : $(GRAM) $(OBJECTS) $(EXE) $(CLEAN)

srcfiles = $(wildcard $(SOURCE_AST)/*.cpp $(SOURCE_IR)/*.cpp)
objfiles:= $(srcfiles:.cpp=.o)
depfiles:= $(srcfiles:.cpp=.d)
gchfiles:= $(srcfiles:.cpp=.gch)

all : $(GRAM) $(OBJECTS) $(depfiles) $(objfiles) $(EXE)

$(GRAM) : $(GRAM_FILECHECK)
$(GRAM_FILECHECK) : $(GRAM_FILE)
	$(ECHO) "BUILDING GRAMMAR"
	$(ECHO) "================"
	@mkdir -p $(SOURCE_ANTLR)
	$(ANTLR) $(GRAMFLAGS) -o $(SOURCE_ANTLR) $(GRAM_FILE)

$(OBJECTS) : $(OBJS_FILECHECK)
$(OBJS_FILECHECK) : $(GRAM_FILECHECK)
	$(ECHO) "BUILDING OBJECTS"
	$(ECHO) "================"
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(OBJS_ANTLR)
	$(CPPC) $(COMPFLAGS) $(SOURCE_ANTLR)/*.cpp -c
	@mv *.o $(OBJS_ANTLR)

$(EXE) : $(depfiles) $(BINARY)
$(BINARY) : $(objfiles) $(OBJS_FILECHECK) $(SOURCEDIR)/*.cpp
	$(ECHO) "BUILDING BINARY"
	$(ECHO) "==============="
	$(CPPC) $(COMPFLAGS) -o $(BINARY) $^ $(OBJS_ANTLR)/*.o $(ANTLRLIBRUNTIME)
	$(POSTTREATMENT)

-include $(depfiles)

%.o: %.cpp
	$(CPPC) $(COMPFLAGS) -c $<
	@mv $(filter %.o,$(subst /, ,$(subst $(SOURCEDIR)/,,$@))) $@

%.d: %.cpp
	@$(CPPC) $(COMPFLAGS) $< -MM -MT $(@:.d=.o) >$@

$(CLEAN) :
	$(ECHO) "CLEANING"
	$(ECHO) "========"
	$(RM) $(RMFLAGS) *.o
	$(RM) $(RMFLAGS) vgcore.*
	$(RM) $(RMFLAGS) $(gchfiles)
	$(RM) $(RMFLAGS) $(objfiles)
	$(RM) $(RMFLAGS) $(depfiles)
	$(RM) $(RMFLAGS) $(OBJSDIR)
	$(RM) $(RMFLAGS) $(SOURCE_ANTLR)
	$(RM) $(RMFLAGS) $(BINARY)

