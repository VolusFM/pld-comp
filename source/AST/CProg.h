#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "../TOS.h"
class CFunction;

class IProg;

class CProg {
public:
    void optimize();
    IProg* to_IR() const;
    string to_asm() const;
    
    TOS tos;
    vector<CFunction> functions;
};

