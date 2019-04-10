#pragma once

#include <iostream>
using std::ostream;
#include <vector>
using std::vector;
#include <string>
using std::string;

class TOS;
class CFunction;
class CFG;

class CInstruction {
public:
    virtual ~CInstruction() = default;
    virtual void explore_tos(TOS& tos) const = 0;
    virtual void optimize() = 0;
    virtual void to_IR(CFG* cfg) const = 0;
    virtual void gen_asm_z80(ostream& o, const CFunction* f) const = 0;
};

// Wrapper for a vector of instructions
class CInstructions : public CInstruction {
public:
    CInstructions() = default;
    CInstructions(vector<CInstruction*>& instructions);
    ~CInstructions();
    
    void explore_tos(TOS& tos) const;
    void optimize();
    void to_IR(CFG* cfg) const;
    void gen_asm_z80(ostream& o, const CFunction* f) const;
    
    vector<CInstruction*> instructions;
    
public:
    // enable move semantics
    CInstructions(CInstructions&&) = default;
    CInstructions& operator=(CInstructions&&) = default;
private:
    // no copy wanted
    CInstructions(const CInstructions&); // no implementation
    CInstructions& operator=(const CInstructions&); // no implementation
};

