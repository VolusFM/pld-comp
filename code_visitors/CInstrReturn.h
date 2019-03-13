#pragma once

#include <string>
#include "CInstruction.h"

using namespace std;

class CInstrReturn : public CInstruction {
public:
  string to_asm() const;
  
  int* returnValue;
};
