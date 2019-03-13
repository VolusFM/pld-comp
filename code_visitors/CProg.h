#pragma once

#include <string>
#include <vector>
#include "CFunction.h"

using namespace std;

class CProg {
public:
  string to_asm() const;
  


  vector<CFunction> functions;
};
