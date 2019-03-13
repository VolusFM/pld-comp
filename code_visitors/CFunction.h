#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "CInstruction.h"

typedef string CType;

class CFunction {
public:
  string to_asm() const;
  
  string name;
  
  // map<string, pair<CType, int>> tos;
  
  vector<CInstruction> instructions;
};

