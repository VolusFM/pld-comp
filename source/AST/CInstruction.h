#pragma once

#include <string>
using std::string;

class CInstruction {
public:
    virtual ~CInstruction();
    virtual string to_asm() const = 0;
};

#include <vector>
using std::vector;

/**
 * Wrapper for a vector of instructions
 */
class CInstructions {
public:
    vector<CInstruction *> instructions;
};

