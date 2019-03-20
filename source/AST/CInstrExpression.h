#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"

class CInstrExpression : public CInstruction {
public:
  CInstrExpression();
  string to_asm(const CFunction * f) const;
  
  CExpression* expr;
};

