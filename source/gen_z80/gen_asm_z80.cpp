#include "../IR/IR.h"
#include "../IR/IProg.h"

#include "../AST/CFunction.h"
#include "../AST/CInstruction.h"
#include "../AST/CExpression.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
#include <string>
using std::to_string;

#include "gen_asm_z80_util.h"
extern Info_z80 z80_additionnal;

void IProg::gen_asm_z80(ostream& o) const {
 /* o << ".nolist\n";
 // o << "#include \"ti83plusOS.inc\"";
    o << "#define _stack_start $9872\n"
 // o << ".org $9D93\n";
 // o << ".db $BB,$6D\n";
    o << "\n";
 */ o << ".list";
    o << "\n";
    
    o << "  ld    ix, _stack_start\n";
    o << "  jp    main\n";
    o << "\n";
    
    try {
        for (const CFG* f : functions) {
            TOS* tos = const_cast<TOS*>(&f->tos);
            tos->clear_address();
            tos->fill_address_z80();
            f->gen_asm_z80(o);
        }
        z80_additionnal.gen_asm_z80(o);
    } catch (...) {
        cerr << "ERROR: couldn't generate assembly code" << endl;
    }
}

void CFG::gen_asm_z80_prologue(ostream& o) const {
    o << name << ":\n";
    
    o << "  push  ix\n";
    int shift = tos.tosOffset;
    if (shift != 0) {
        o << "  lb    bc, " << shift << "\n";
        o << "  add   ix, bc\n";
    }
    o << "  pop   de\n";
    
    int index = 0;
    for (auto it = ast->parameters.cbegin(); it != ast->parameters.cend() ; ++it) {
        o << "  pop   hl\n";
        ld_hl_var(o,tos, it->name);
    }
    
    o << "  push  de\n";
    o << "  ## contenu\n";
}

void CFG::gen_asm_z80(ostream& o) const {
    gen_asm_z80_prologue(o);
    
    // merge all basic blocks at the end that are empty and terminating
    
    auto nullbbs = bbs.cbegin();
    for (auto it = bbs.cbegin(); it != bbs.cend(); ++it) {
	    const BasicBlock* b = (*it);
        if (b->exit_true != nullptr || b->exit_false != nullptr || !b->instrs.empty()) {
            nullbbs = it+1;
        }
    }
    
    // remove unnecessary basic block jumps
    
	for (auto it = bbs.cbegin(); it != nullbbs; ++it) {
	    const BasicBlock* b = (*it);
        
	    auto itn = it+1;
	    const BasicBlock* bn = nullptr;
	    if (itn != bbs.cend() && !(*it)->instrs.empty()) bn = (*itn);
	    
        // generate basic block code and necessary jumps
        
        b->gen_asm_z80(o);
        
        if (b->exit_false != nullptr) {
            o << "  ld    a, h\n";
            o << "  or    l\n";
            o << "  jp z, " << b->exit_false->label << "\n";
        }
        if (b->exit_true != nullptr) {
            if (bn != b->exit_true)
            o << "  jp    " << b->exit_true->label << "\n";
        }
        if (b->exit_true == nullptr && b->exit_false == nullptr) {
            if (itn != nullbbs)
            o << "  jp    " << name << "_end\n";
        }
	}
    
    for (auto it = nullbbs; it != bbs.cend(); ++it) {
        o << (*it)->label << ":\n";
    }
    
    gen_asm_z80_epilogue(o);
}

void CFG::gen_asm_z80_epilogue(ostream& o) const {
    o << name << "_end:\n"
      << "  ## epilogue\n"
      << "  pop   ix\n"
      << "  ret\n";
}

void BasicBlock::gen_asm_z80(ostream& o) const {
    o << label << ":\n";
    
    for (auto it = instrs.cbegin(); it != instrs.cend(); ++it) {
        (*it)->gen_asm_z80(o);
    }
}

