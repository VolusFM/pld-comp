#include "../AST/CProg.h"
#include "../AST/CFunction.h"
#include "../AST/CFunctionHeader.h"

#include <string>
using std::to_string;
#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;


void CProg::gen_asm_z80(ostream& o) const {
 /* o << ".nolist\n";
    o << "#include \"ti83plusOS.inc\"";
    o << ".org $9D93";
    o << ".db $BB,$6D";
    o << "\n";
 */ o << ".list";
    o << "\n";
    
 // o << "  ld   ix, $NNNN\n"
    
    try {
        for (const CFunction& f : functions) {
            TOS* tos = const_cast<TOS*>(&f.tos);
            tos->fill_address_z80();
            f.gen_asm_z80(o);
            tos->clear_temp();
        }
    } catch (...) {
        cerr << "ERROR: couldn't generate assembly code" << endl;
    }
}

void CParameter::gen_asm_z80(ostream& o, const CFunction* f, int index) const {
    string variable = f->tos.get_address_z80(name);
    
    o << "  pop   hl\n";
    o << "  ld    (" << variable << "), hl\n";
}

void CFunction::gen_asm_z80(ostream& o) const {
    o << name << ":\n";
    
 // o << "  push  ix\n";
 // o << "  lb    bc, NNNN\n";
 // o << "  add   ix, bc\n";
    
 // o << "  pop   de\n";
    int index = 0;
    for (auto it = parameters.cbegin() ; it != parameters.cend() ; ++it) {
        it->gen_asm_z80(o, this, index);
        index++;
    }
 // o << "  push  de\n";
    
    for (const CInstruction* it : block.instructions) {
        it->gen_asm_z80(o, this);
    }
    
 // o << "  pop   ix\n";
    o << "  ret\n";
}

