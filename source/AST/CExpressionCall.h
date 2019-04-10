#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <vector>
using std::vector;

#include "CExpression.h"

class CFunction;
class CFG;

class CExpressionCall: public CExpressionPart {
public:
    CExpressionCall(string name, vector<CExpressionPart*> parameters);
    CExpressionPart* optimize();
    string to_IR(CFG* cfg) const;
    string gen_asm_z80(ostream& o, CFunction* f) const;
    ~CExpressionCall();
    
    string functionName;
    vector<CExpressionPart*> parameters;
    
private: // no copy wanted
    CExpressionCall(const CExpressionCall&); // no implementation
    CExpressionCall& operator=(const CExpressionCall&); // no implementation
};

