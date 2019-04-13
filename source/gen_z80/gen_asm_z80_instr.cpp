#include "../IR/IR.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;

#include <string>
using std::stoi;
using std::to_string;

#include "gen_asm_z80_util.h"
extern Info_z80 z80_additionnal;

void IRInstr::gen_asm_z80(ostream& o) const {
    CFG* cfg = bb->cfg;
    TOS& tos = cfg->tos;
    
    /*
        for 3-op instrs: d, x, y;
        for ldconst: d, c;
        for call: label, d, params;
        for wmem and rmem: address, variable;
    */
    switch (op) {
    case op_copy:
        ld_hl_var(o,tos, params[1]);
        ld_var_hl(o,tos, params[0]);
        break;
    case op_ldconst:
        ld_hl_var(o,tos, params[1]);
        // o << "  ld    hl, " << params[1] << "\n";
        ld_var_hl(o,tos, params[0]);
        break;
 /*
    case op_copy_array:
        o << "  ld    "  << tos.get_address_z80(params[1]) << ", de\n";
        o << "  ld    de, " << tos.get_address_z80_array(params[0]) << "\n";
        break;
    case op_ldconst_array:
        o << "  ld    " << params[1] << ", " << tos.get_address_z80_array(params[0])<< "\n";
        break;
    case op_copy_from_array:
        o << "  ld    "  << tos.get_address_z80_array(params[1]) << ", hl\n";
        o << "  ld    hl, " << tos.get_address_z80(params[0]) << "\n";
        break;
    case op_copy_to_array_index: {
        int address = cfg->tos.get_index(params[0]);
        int index = stoi(params[1]);
        string loc = "-" + to_string(address - 4 * index) + "(%rbp)";
        o << "  ld    "  << tos.get_address_z80(params[2]) << ", de\n";
        o << "  ld    de, " << loc << "\n";
        break;
    }
    case op_ldconst_to_array_index: {
        int address = cfg->tos.get_index(params[0]);
        int index = stoi(params[1]);
        string loc = "-" + to_string(address - 4 * index) + "(%rbp)";
        o << "  ld    " << params[2] << ", " << loc << "\n";
        break;
    }
 */
    case op_index:
        ld_hl_var(o,tos, params[0]);
        break;
    case op_index_ldconst:
        o << "  ld    hl, " << params[0] << "\n";
        break;
    case op_add:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        o << "  add   hl, de\n";
        ld_var_hl(o,tos, params[0]);
        break;
    case op_sub:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        o << "  or    a\n";
        o << "  sbc   hl, de\n";
        ld_var_hl(o,tos, params[0]);
        break;
    case op_mul:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_mul\n";
        z80_additionnal.use_MUL = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_div:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_div\n";
        z80_additionnal.use_DIV = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_mod:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_mod\n";
        z80_additionnal.use_MOD = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_binary_and:
        ld_hl_var(o,tos, params[1]);
        ld_a_nibble(o,tos, params[2], 0);
        o << "  and   l\n";
        o << "  ld    l, a\n";
        ld_a_nibble(o,tos, params[2], 1);
        o << "  and   h\n";
        o << "  ld    h, a\n";
        ld_var_hl(o,tos, params[0]);
        break;
    case op_binary_or:
        ld_hl_var(o,tos, params[1]);
        ld_a_nibble(o,tos, params[2], 0);
        o << "  or    l\n";
        o << "  ld    l, a\n";
        ld_a_nibble(o,tos, params[2], 1);
        o << "  or    h\n";
        o << "  ld    h, a\n";
        ld_var_hl(o,tos, params[0]);
        break;
    case op_binary_xor:
        ld_hl_var(o,tos, params[1]);
        ld_a_nibble(o,tos, params[2], 0);
        o << "  xor   l\n";
        o << "  ld    l, a\n";
        ld_a_nibble(o,tos, params[2], 1);
        o << "  xor   h\n";
        o << "  ld    h, a\n";
        ld_var_hl(o,tos, params[0]);
        break;
    case op_not:
        ld_hl_var(o,tos, params[2]);
        o << "  ld    a, l\n";
        o << "  cpl\n";
        o << "  ld    l, a\n";
        o << "  ld    a, h\n";
        o << "  cpl\n";
        o << "  ld    h, a\n";
        ld_var_hl(o,tos, params[0]);
	break;
    case op_cmp_eq:
    case op_cmp_ne:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        o << "  or    a\n";
        o << "  sbc   hl, de\n";
        ld_var_hl(o,tos, params[0]);
        break;
    case op_cmp_lt:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_cmp_lt\n";
        z80_additionnal.use_CMP_LT = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_cmp_le:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_cmp_le\n";
        z80_additionnal.use_CMP_LE = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_cmp_gt:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_cmp_gt\n";
        z80_additionnal.use_CMP_GT = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_cmp_ge:
        ld_hl_var(o,tos, params[1]);
        ld_de_var(o,tos, params[2]);
        
        o << "  call  _op_cmp_ge\n";
        z80_additionnal.use_CMP_GE = true;
        
        ld_var_hl(o,tos, params[0]);
        break;
    case op_call:
        for (auto it = params.rbegin() ; it != params.rend()-2 ; ++it) {
            ld_hl_var(o,tos, *it);
            o << "  push  hl\n";
        }
        o << "  call  " << params[0] << "\n";
        ld_var_hl(o,tos, params[1]);
        break;
    case op_return:
        if (params[0].at(0) == '$') {
            o << "  ld    hl, " << params[0].c_str()+1 << "\n";
        } else {
            ld_hl_var(o,tos, params[0]);
        }
        break;
    
    case op_rmem:
        ld_de_var(o,tos, params[1]);
        o << "  ld    e, (hl)\n";
        o << "  inc   hl\n";
        o << "  ld    d, (hl)\n";
        ld_var_de(o,tos, params[0]);
        break;
    case op_wmem:
        ld_var_de(o,tos, params[1]);
        ld_var_hl(o,tos, params[0]);
        o << "  ld    (hl), e\n";
        o << "  inc   hl\n";
        o << "  ld    (hl), d\n";
        break;
    
    default:
        cerr << "PROBLEM: operator not yet supported" << endl;
        throw;
        break;
    }
}
