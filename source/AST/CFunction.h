#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

#include "CInstruction.h"

typedef string CType;

class CFunction {
public:
  string to_asm() const;
  
  void fill_tos();
  
  string name;
  
  vector<string> tos;
  map<string, CType> tosType;
  
  vector<CInstruction*> instructions;
};

