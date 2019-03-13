#pragma once

using namespace std;

#include <string>
#include <vector>
#include "CFunction.h"

class CProg {
public:
  string to_asm() const;
  


  vector<CFunction> functions;
};
