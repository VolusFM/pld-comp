#pragma once

#include <string>

using namespace std;

class CFunction {
public:
  string to_asm() const;
  
  string name;
  int returnvalue;
};
