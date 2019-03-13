#pragma once

using namespace std;

#include <string>

class CFunction {
public:
  string to_asm() const;
  
  string name;
  int returnvalue;
};
