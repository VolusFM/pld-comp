#pragma once

#include <iostream>
using std::ostream;
#include <vector>
using std::vector;

#include "IR.h"

class IProg {
public:
    ~IProg();
    
    void optimize();
    void gen_asm_x86(ostream &o) const;
    
    vector<CFG*> functions;
};

