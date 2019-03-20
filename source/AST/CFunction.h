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
  
  string name;
  
  vector<string> tos;
  map<string, CType> tosType;
  map<string, int> tosAddress;
  
  CInstructions bloc;
  
  void fill_tos();
private:
  void fill_tos(CInstructions& bloc);
};

