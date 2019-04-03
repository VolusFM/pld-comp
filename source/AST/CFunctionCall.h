#pragma once

#include <string>
using std::string;

#include <utility>
using std::pair;
#include <vector>
using std::vector;

#include "CExpression.h"

class CFunction;
class CFG;


class CFunctionCall: public CExpression {
public:
    CFunctionCall(string name, vector<CExpression*> parameters);
    string to_IR(CFG* cfg) const;
    pair<string, string> to_asm(CFunction* f) const;
    ~CFunctionCall();

    string functionName;
    vector<CExpression*> parameters;
    
private: // no copy wanted
    CFunctionCall(const CFunctionCall&); // no implementation
    CFunctionCall& operator=(const CFunctionCall&); // no implementation
};

