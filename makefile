
# commands

GRAM=grammar
OBJECTS=objs
EXE=compile
CLEAN=clean

# directories

SOURCEDIR=source
SOURCE_ANTLR=source/antlr
SOURCE_AST=source/AST
SOURCE_IR=source/IR

SOURCEDIRS=$(SOURCEDIR) $(SOURCE_ANTLR) $(SOURCE_AST) $(SOURCE_IR)

OBJSDIR=objects
OBJS_ANTLR=objects/antlr
#OBJS_AST=objects/AST
#OBJS_IR=objects/IR

OBJSDIRS=$(OBJSDIR) $(OBJS_ANTLR)# $(OBJS_AST) $(OBJS_IR)

BINARY=yottacompilatron9001

# tools and paths

JAVA=/usr/bin/java

GRAM_FILE=CodeC.g4
GRAM_FILECHECK=$(SOURCE_ANTLR)/CodeCBaseVisitor.h
OBJS_FILECHECK=$(OBJS_ANTLR)/CodeCBaseVisitor.o

RM=rm
RMFLAGS=-rf
ECHO=@echo
GRAMFLAGS=-visitor -no-listener -Dlanguage=Cpp
COMPFLAGS=-DTRACE -g -std=c++11
COMPFLAGSALL=$(COMPFLAGS) -I $(ANTLRRUNTIME)
CPPC=clang++

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

CPPC=clang++
# if clang++ isn't found, use g++ instead
# useful for some IF computers without clang++
ifeq (,$(shell which $(CPPC)))
CPPC=g++-6 -Wno-attributes
endif

# make USE="shares" to compile
# without having the ANTLR/ folder
ifeq ($(USE),shares)
ANTLR:=$(ANTLRDIR)/bin/antlr4
ANTLRDIR=/shares/public/tp/antlr
endif

.PHONY : $(GRAM) $(OBJECTS) $(EXE) $(CLEAN)

srcfiles=$(wildcard $(SOURCE_AST)/*.cpp $(SOURCE_IR)/*.cpp)
objfiles:=$(srcfiles:.cpp=.o)
depfiles:=$(srcfiles:.cpp=.d)
gchfiles:=$(srcfiles:.cpp=.gch)

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
	$(CPPC) $(COMPFLAGSALL) $(SOURCE_ANTLR)/*.cpp -c
	@mv *.o $(OBJS_ANTLR)

$(EXE) : $(depfiles) $(BINARY)
$(BINARY) : $(objfiles) $(OBJS_FILECHECK) $(SOURCEDIR)/*.cpp
	$(ECHO) "BUILDING BINARY"
	$(ECHO) "==============="
	$(CPPC) $(COMPFLAGSALL) -o $(BINARY) $^ $(OBJS_ANTLR)/*.o $(ANTLRLIBRUNTIME)
	$(POSTTREATMENT)

-include $(depfiles)

%.o: %.cpp
	$(CPPC) $(COMPFLAGS) -c $<
	@mv $(filter %.o,$(subst /, ,$(subst $(SOURCEDIR)/,,$@))) $@

%.d: %.cpp
	@$(CPPC) $(COMPFLAGS) $< -MM -MT $(@:.d=.o) >$@

WORKDIRS=$(SOURCE_AST) $(SOURCE_IR)

$(CLEAN) :
	$(ECHO) "CLEANING"
	$(ECHO) "========"
	$(RM) $(RMFLAGS) *.o
	$(RM) $(RMFLAGS) vgcore.*
	$(RM) $(RMFLAGS) $(patsubst %,%/*.gch,$(WORKDIRS))
	$(RM) $(RMFLAGS) $(patsubst %,%/*.o,$(WORKDIRS))
	$(RM) $(RMFLAGS) $(patsubst %,%/*.d,$(WORKDIRS))
	$(RM) $(RMFLAGS) $(OBJSDIR)
	$(RM) $(RMFLAGS) $(SOURCE_ANTLR)
	$(RM) $(RMFLAGS) $(BINARY)

