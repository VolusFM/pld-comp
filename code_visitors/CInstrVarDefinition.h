#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"
typedef string CType;

class CInstrVarDefinition: public CInstruction {
public:
  CInstrVarDefinition();
  string to_asm() const;
  
  CType type;
  string name;
  CExpression* expr;
};

