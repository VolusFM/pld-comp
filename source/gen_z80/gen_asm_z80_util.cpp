#include "gen_asm_z80_util.h"

#include "../TOS.h"

Info_z80 z80_additionnal;

Info_z80::Info_z80()
: use_MUL(false), use_DIV(false), use_MOD(false),
  use_CMP_EQ(false), use_CMP_NE(false),
  use_CMP_LT(false), use_CMP_LE(false),
  use_CMP_GT(false), use_CMP_GE(false)
{
}

void Info_z80::gen_asm_z80(ostream& o)
{
    if (use_CMP_EQ) {
        o << "_op_cmp_eq:\n";
        o << "  xor   a\n";
        o << "  sbc   hl, de\n";
        o << "  ld    h, a\n";
        o << "  ld    l, a\n";
        o << "  ret   z\n";
        o << "  inc   l\n";
        o << "  ret\n";
    }
    if (use_CMP_NE) {
        o << "_op_cmp_ne:\n";
        o << "  xor   a\n";
        o << "  sbc   hl, de\n";
        o << "  ret   z\n";
        o << "  ld    h, a\n";
        o << "  ld    l, 1\n";
        o << "  ret\n";
    }
    
    // Les codes assembleurs z80 générés pour les opérations *, /, %
    // proviennent du fichier "Commands.inc" de l'archive suivante :
    // https://www.ticalc.org/archives/files/fileinfo/456/45659.html
    // Ils ont été mis par son auteur dans le domaine public.
    
    if (use_MUL) {
        o << "_op_mul:\n";
        o << "  xor   a\n";
        o << "  cp    h\n";
        o << "  jr    z, _op_mul__step\n";
        o << "  ex    de, hl\n";
        o << "_op_mul__step:\n";
        o << "  ld    c, l\n";
        o << "  ld    l, a\n";
        o << "  add   a, h\n";
        o << "  call  nz, _op_mul__byte\n";
        o << "  ld    a, c\n";
        o << "_op_mul__byte:\n";
        o << "  ld    b, $08\n";
        o << "_op_mul__next:\n";
        o << "  add   hl, hl\n";
        o << "  add   a, a\n";
        o << "  jr    nc, _op_mul__skip\n";
        o << "  add   hl, de\n";
        o << "_op_mul__skip:\n";
        o << "  djnz  _op_mul__next\n";
        o << "  ret\n";
    }
    if (use_DIV) {
        o << "_op_div:\n";
        o << "  ld    a, h\n";
        o << "  xor   d\n";
        o << "  push  af\n";
        o << "  xor   d\n";
        o << "  jp    p, _op_div__skip1\n";
        o << "  xor   a\n";
        o << "  sub   l\n";
        o << "  ld    l, a\n";
        o << "  sbc   a, a\n";
        o << "  sub   h\n";
        o << "  ld    h, a\n";
        o << "_op_div__skip1:\n";
        o << "  bit   7, d\n";
        o << "  jr    z, _op_div__skip2\n";
        o << "  xor   a\n";
        o << "  sub   e\n";
        o << "  ld    e, a\n";
        o << "  sbc   a, a\n";
        o << "  sub   d\n";
        o << "  ld    d, a\n";
        o << "_op_div__skip2:\n";
        o << "  call  _op_udiv\n";
        o << "  pop   af\n";
        o << "  ret   p\n";
        o << "  xor   a\n";
        o << "  sub   l\n";
        o << "  ld    l, a\n";
        o << "  sbc   a, a\n";
        o << "  sub   h\n";
        o << "  ld    h, a\n";
        o << "  ret\n";
        use_MOD = true;
        o << "_op_udiv:\n";
        o << "  ld    b, 16\n";
        o << "  ld    a, d\n";
        o << "  or    a\n";
        o << "  jr    z, _op_udiv__loop\n";
        o << "  call  _op_mod\n";
        o << "  ld    h, a\n";
        o << "  ld    l, c\n";
        o << "  ret\n";
        o << "_op_udiv__loop:\n";
        o << "  add   hl, hl\n";
        o << "  rla\n";
        o << "  jr    c, _op_udiv__overflow\n";
        o << "  cp    e\n";
        o << "  jr    c, _op_udiv__skip\n";
        o << "_op_udiv__overflow:\n";
        o << "  sub   e\n";
        o << "  inc   l\n";
        o << "_op_udiv__skip:\n";
        o << "  djnz	_op_udiv__loop\n";
        o << "  ret\n";
    }
    if (use_MOD) {
        o << "_op_mod:\n";
        o << "  ld b,16\n";
        o << "  ld a,h\n";
        o << "  ld c,l\n";
        o << "  ld hl,0\n";
        o << "_op_mod__loop:\n";
        o << "  scf\n";
        o << "  rl c\n";
        o << "  rla\n";
        o << "  adc hl,hl\n";
        o << "  sbc hl,de\n";
        o << "  jr nc,_op_mod__skip\n";
        o << "  add hl,de\n";
        o << "  dec c\n";
        o << "_op_mod__skip:\n";
        o << "  djnz _op_mod__loop\n";
        o << "  ret\n";
    }
    
    // Les codes assembleurs générés pour les opérateurs de comparaison
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


void ld_hl_adr(ostream& o, const TOS& tos, const string& param, int index) {
    o << "  push  ix\n";
    o << "  pop   hl\n";
    int address = tos.get_address_z80(param);
    o << "  ld    de, " << address+index << "\n";
    o << "  add   hl, de\n";
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
void ld_bc_var(ostream& o, const TOS& tos, const string& param) {
    if (param.at(0) == '$') {
        o << "  ld    bc, " << param.c_str()+1 << "\n";
        return;
    }
    
    int address = tos.get_address_z80(param);
    o << "  ld    c, (ix+" << address << ")\n";
    o << "  ld    b, (ix+" << address+1 << ")\n";
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
void ld_var_bc(ostream& o, const TOS& tos, const string& param) {
    int address = tos.get_address_z80(param);
    o << "  ld    (ix+" << address << "), c\n";
    o << "  ld    (ix+" << address+1 << "), b\n";
}

