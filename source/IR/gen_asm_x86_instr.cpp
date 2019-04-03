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
        o << "  movl  $" << params[1] << ", " << cfg->tos_get_asm_x86(params[0])
                << "\n";
        break;
    case op_add:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  addl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_sub:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  subl  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_mul:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  imull  " << cfg->tos_get_asm_x86(params[2]) << ", %eax" << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_div:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cltd\n";
        o << "  idivl  " << cfg->tos_get_asm_x86(params[2]) << "\n";
        o << "  movl  %eax, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;
    case op_mod:
        o << "  movl  " << cfg->tos_get_asm_x86(params[1]) << ", %eax" << "\n";
        o << "  cltd\n";
        o << "  idivl  " << cfg->tos_get_asm_x86(params[2]) << "\n";
        o << "  movl  %edx, " << cfg->tos_get_asm_x86(params[0]) << "\n";
        break;

        /*case op_rmem:
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

