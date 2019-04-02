#include "CProg.h"

#include <iostream>
using std::cerr;
using std::endl;

string CProg::to_asm() const {
    string code;
    code += ".text\n";
    code += ".global main\n";
    try {
        for (const CFunction& f : functions) {
            code += f.to_asm();
        }
    } catch(...) {
        cerr << "ERROR: couldn't generate assembly code" << endl;
    }
    return code;
}

