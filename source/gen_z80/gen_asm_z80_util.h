#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;

class TOS;

class Info_z80 {
public:
    Info_z80();
    void gen_asm_z80(ostream& o);
    
    bool use_MUL;
    bool use_DIV;
    bool use_MOD;
    
    bool use_CMP_LT;
    bool use_CMP_LE;
    bool use_CMP_GT;
    bool use_CMP_GE;
};

void ld_hl_adr(ostream& o, const TOS& tos, const string& param, int index = 0);

void ld_hl_var(ostream& o, const TOS& tos, const string& param);
void ld_de_var(ostream& o, const TOS& tos, const string& param);
void ld_bc_var(ostream& o, const TOS& tos, const string& param);

void ld_a_nibble(ostream& o, const TOS& tos, const string& param, int which);

void ld_var_hl(ostream& o, const TOS& tos, const string& param);
void ld_var_de(ostream& o, const TOS& tos, const string& param);
void ld_var_bc(ostream& o, const TOS& tos, const string& param);

