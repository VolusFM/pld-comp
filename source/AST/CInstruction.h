#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

class CFG;

class CFunction;

class CInstruction {
public:
    virtual ~CInstruction() = default;
    virtual void to_IR(CFG* cfg) const = 0;
    virtual string to_asm(const CFunction* f) const = 0;
};

// Wrapper for a vector of instructions
class CInstructions : public CInstruction {
public:
    CInstructions() = default;
    CInstructions(vector<CInstruction*>& instructions);
    ~CInstructions();
    
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

