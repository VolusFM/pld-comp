#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "../CType.h"
#include "../TOS.h"
#include "CInstruction.h"
#include "CFunctionHeader.h"

class CProg;

class CFG;



class CFunction {
public:
    CFunction(const CProg* prog, string name, CType type, vector<CParameter>& parameters, CInstructions& block);
    ~CFunction() = default;
    
    void optimize();
    CFG* to_IR() const;
    void gen_asm_z80(ostream& o) const;
    
    const CProg* prog;
    string name;
    CType type;
    
    TOS tos;
    
    vector<CParameter> parameters;
    CInstructions block;
    
    void explore_tos();
    
public:
    // enable move semantics
    CFunction(CFunction&&) = default;
    CFunction& operator=(CFunction&&) = default;
private:
    // no copy wanted
    CFunction(const CFunction&); // no implementation
    CFunction& operator=(const CFunction&); // no implementation
};

