
BINARY=yottacompilatron9001

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
SOURCE_X86=source/gen_x86
SOURCE_Z80=source/gen_z80

SOURCEDIRS=$(SOURCEDIR) $(SOURCE_ANTLR) $(SOURCE_AST) $(SOURCE_IR) $(SOURCE_X86) $(SOURCE_Z80)

OBJSDIR=objects
OBJS_ANTLR=objects/antlr
#OBJS_AST=objects/AST
#OBJS_IR=objects/IR
#OBJS_X86=objects/gen_x86
#OBJS_Z80=objects/gen_z80

OBJSDIRS=$(OBJSDIR) $(OBJS_ANTLR)# $(OBJS_AST) $(OBJS_IR) $(OBJS_X86) $(OBJS_Z80)

# tools and paths

JAVA=/usr/bin/java

GRAM_FILE=CodeC.g4
GRAM_FILECHECK=$(SOURCE_ANTLR)/CodeCBaseVisitor.h
OBJS_FILECHECK=$(OBJS_ANTLR)/CodeCBaseVisitor.o

RM=rm
RMFLAGS=-rf
ECHO=@echo
GRAMFLAGS=-visitor -no-listener -Dlanguage=Cpp
COMPFLAGS=-g -std=c++11
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
POSTTREATMENT:=
endif
ifeq ($(FOR),dev)
POSTTREATMENT:=
endif


ANTLRDIR=/shares/public/tp/ANTLR4-CPP
ANTLR=$(ANTLRDIR)/bin/antlr4
ANTLRRUNTIME=$(ANTLRDIR)/antlr4-runtime
ANTLRLIBRUNTIME=$(ANTLRDIR)/lib/libantlr4-runtime.a

# ANTLR path chosen by default:
# - on linux: /shares/public/tp/ANTLR4-CPP
# - on mac: ./ANTLR/

# ANTLR path chosen if arguments specified:
# - with USE="local": ./ANTLR
# - with USE="shares": /shares/public/tp/ANTLR4-CPP
# - with USE="alt": local binary with shared libraries

ifeq ($(OSNAME),MAC)
ANTLRDIR=ANTLR/$(OSNAME)-CPP
endif
ifeq ($(USE),local)
ANTLRDIR=ANTLR/$(OSNAME)-CPP
endif
ifeq ($(USE),shares)
ANTLRDIR=/shares/public/tp/ANTLR4-CPP
endif
ifeq ($(USE),alt)
ANTLR=ANTLR/$(OSNAME)-CPP/bin/antlr4
ANTLRDIR=/shares/public/tp/antlr
endif


CPPC=clang++
# if clang++ isn't found, use g++ instead
# useful for some IF computers without clang++
ifeq (,$(shell which $(CPPC)))
CPPC=g++-6 -Wno-attributes
endif

.PHONY : $(GRAM) $(OBJECTS) $(EXE) $(CLEAN)

srcfiles=$(wildcard $(SOURCE_AST)/*.cpp $(SOURCE_IR)/*.cpp $(SOURCE_X86)/*.cpp $(SOURCE_Z80)/*.cpp)
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

WORKDIRS=$(SOURCE_AST) $(SOURCE_IR) $(SOURCE_X86) $(SOURCE_Z80)

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

