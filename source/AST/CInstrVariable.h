#pragma once

#include <string>
using std::string;

#include "CInstruction.h"
#include "CExpression.h"
typedef string CType;

class CInstrVariable: public CInstruction {
public:
  CInstrVariable();
  string to_asm() const;
  
  CType type;
  string name;
  CExpression* expr;
};

