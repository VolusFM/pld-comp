#pragma once

#include <string>
using std::string;

// #include "CType.h"
#include "CInstruction.h"
#include "CExpression.h"

class CInstrVarDefinition: public CInstruction {
public:
  string to_asm() const;
  
  /*forcement un int*/
  //CType type;
  string name;
  CExpression* expr;
};

