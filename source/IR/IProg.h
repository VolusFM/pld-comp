#pragma once

#include <iostream>
using std::ostream;
#include <vector>
using std::vector;

#include "../TOS.h"
class CFG;

class IProg {
public:
    ~IProg();
    
    void optimize();
    void gen_asm_x86(ostream &o) const;
    void gen_asm_z80(ostream &o) const;
    
    TOS tos;
    vector<CFG*> functions;
};

