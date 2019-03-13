#pragma once

#include <string>
#include "CInstruction.h"
#include "CType.h"
#include "CExpression.h"
using std::string;

class CVarDefinition: public CInstruction {
	public:
  		string to_asm() const;
  		
  		/*forcement un int*/
  		//CType type;
  		string name;
  		CExpression * expression;
};

