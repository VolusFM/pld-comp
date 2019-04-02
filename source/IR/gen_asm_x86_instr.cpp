#include "IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

void IRInstr::gen_asm_x86(ostream& o) const {
    CFG* cfg = bb->cfg;
    
    /*
        for 3-op instrs: d, x, y;
        for ldconst: d, c;
        for call: label, d, params;
        for wmem and rmem: choose yourself
    */
    
    switch (op) {
        case op_ldconst:
            o << "  movl  $" << params[1] << ", " << cfg->tos_get_asm_x86(params[0]) << "\n";
            break;
        
        /*
        case op_add:
            break;
        case op_sub:
            break;
        case op_mul:
            break;
        case op_rmem:
            break;
        case op_wmem:
            break;
        case op_call:
            break;
        case op_cmp_eq:
            break;
        case op_cmp_lt:
            break;
        case op_cmp_le:
            break;
        */
        // to do
        
        default:
            cerr << "PROBLEM: operator not yet supported" << endl;
            throw;
            break;
    }
}

