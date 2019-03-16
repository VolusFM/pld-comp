#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"

class CInstrReturn : public CInstruction {
public:
  CInstrReturn();
  string to_asm() const;
  
  CExpression* expr;
};

