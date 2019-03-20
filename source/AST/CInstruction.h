#pragma once

#include <string>
using std::string;

class CFunction;

class CInstruction {
public:
  virtual string to_asm(const CFunction* f) const = 0;
  
};

#include <vector>
using std::vector;

class CInstructions {
public:
  vector<CInstruction*> instructions;
};

