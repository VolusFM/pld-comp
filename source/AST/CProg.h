#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "CFunction.h"

class IProg;

class CProg {
public:
    IProg* to_IR() const;
    string to_asm() const;
    
    vector<CFunction> functions;
};

