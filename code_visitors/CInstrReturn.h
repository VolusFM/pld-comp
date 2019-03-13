#pragma once

#include <string>
using std::string;

class CInstrReturn : public CInstruction{
public:
  string to_asm() const;
  
  int* returnValue;
};
