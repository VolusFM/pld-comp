#pragma once

#include <string>
using std::string;

class CFunction;

class CInstruction {
public:
    virtual ~CInstruction();
    virtual string to_asm(const CFunction* f) const = 0;
};

#include <vector>
using std::vector;

/**
 * Wrapper for a vector of instructions
 */
class CInstructions {
public:
    CInstructions();
    CInstructions(vector<CInstruction*>& instructions);
    ~CInstructions();

    vector<CInstruction*> instructions;
    
public: // enable move semantics
    CInstructions(CInstructions&&) = default;
    CInstructions& operator=(CInstructions&&) = default;
private: // no copy wanted
    CInstructions(const CInstructions&); // no implementation
    CInstructions& operator=(const CInstructions&); // no implementation
};

