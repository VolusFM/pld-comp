#pragma once

#include <string>
using std::string;

class CFunction {
public:
  string to_asm() const;
  
  string name;
  int returnvalue;
};
