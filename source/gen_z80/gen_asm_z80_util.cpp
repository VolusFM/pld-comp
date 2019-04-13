#include "gen_asm_z80_util.h"

#include "../TOS.h"

Info_z80 z80_additionnal;

Info_z80::Info_z80()
: use_MUL(false), use_DIV(false), use_MOD(false),
  use_CMP_LT(false), use_CMP_LE(false),
  use_CMP_GT(false), use_CMP_GE(false)
{
}

void Info_z80::gen_asm_z80(ostream& o)
{
    if (use_MUL) {
    }
    if (use_DIV) {
    }
    if (use_MOD) {
    }
    
    // Le code assembleur généré pour les opérateur de comparaison
    // proviennent du fichier "Commands.inc" de l'archive suivante :
    // https://www.ticalc.org/archives/files/fileinfo/456/45659.html
    // Ils ont été mis par son auteur dans le domaine public.
    
    if (use_CMP_LT) {
        o << "_op_cmp_lt:\n";
        o << "  xor   a\n  ld      b, h\n  sbc   hl, de\n";
        o << "  ld    h, a\n  rra\n  xor   b\n  xor   d\n";
        o << "  rlca\n  and   1\n  ld    l, a\n";
        o << "  ret\n";
    }
    if (use_CMP_LE) {
        o << "_op_cmp_le:\n";
        o << "  ld    a, e\n  sub     l\n  ld    a, d\n  sbc a, h\n";
        o << "  rra\n  xor   d\n  xor   h\n  rla\n";
        o << "  sbc   hl, hl\n  inc   hl\n";
        o << "  ret\n";
    }
    if (use_CMP_GT) {
        o << "_op_cmp_gt:\n";
        o << "  ld    a, l\n  scf\n  sbc   a, e\n";
        o << "  ld    a, h\n  sbc   a, d\n  rra\n";
        o << "  xor   d\n  xor   h\n  rla\n";
        o << "  sbc   hl, hl\n  inc   hl\n";
        o << "  ret\n";
    }
    if (use_CMP_GE) {
        o << "_op_cmp_ge:\n";
        o << "  ld    a, l\n  sub   e\n  ld    a, h\n  sbc   a, d\n";
        o << "  rra\n  xor   d\n  xor   h\n  rla\n";
        o << "  sbc   hl, hl\n  inc hl\n";
        o << "  ret\n";
    }
}

void ld_hl_var(ostream& o, const TOS& tos, const string& param) {
    if (param.at(0) == '$') {
        o << "  ld    hl, " << param.c_str()+1 << "\n";
        return;
    }
    
    int address = tos.get_address_z80(param);
    o << "  ld    l, (ix+" << address << ")\n";
    o << "  ld    h, (ix+" << address+1 << ")\n";
}

void ld_de_var(ostream& o, const TOS& tos, const string& param) {
    if (param.at(0) == '$') {
        o << "  ld    de, " << param.c_str()+1 << "\n";
        return;
    }
    
    int address = tos.get_address_z80(param);
    o << "  ld    e, (ix+" << address << ")\n";
    o << "  ld    d, (ix+" << address+1 << ")\n";
}

void ld_a_nibble(ostream& o, const TOS& tos, const string& param, int which) {
    if (param.at(0) == '$') {
        o << "  ld    a, " << param.c_str()+1 << (which > 0 ? "/256" : "") << "\n";
        return;
    }
    
    int address = tos.get_address_z80(param);
    o << "  ld    a, (ix+" << address+which << ")\n";
}

void ld_var_hl(ostream& o, const TOS& tos, const string& param) {
    int address = tos.get_address_z80(param);
    o << "  ld    (ix+" << address << "), l\n";
    o << "  ld    (ix+" << address+1 << "), h\n";
}

void ld_var_de(ostream& o, const TOS& tos, const string& param) {
    int address = tos.get_address_z80(param);
    o << "  ld    (ix+" << address << "), e\n";
    o << "  ld    (ix+" << address+1 << "), d\n";
}

