#pragma once

#include <string>
using std::string;

class CInstruction {
public:
  virtual string to_asm() const = 0;
  
};

