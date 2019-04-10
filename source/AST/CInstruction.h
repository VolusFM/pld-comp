#pragma once

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
    virtual string to_asm(const CFunction* f) const = 0;
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
    string to_asm(const CFunction* f) const;
    
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

