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
};

